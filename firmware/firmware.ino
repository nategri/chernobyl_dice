#define UV_LED_PIN 14

// Address to store whether or not device is in "turbo mode"
// Increment this if it starts acting funny (WOW YOU'VE TOGGLED IT A LOT HUH)
#define EEPROM_ADDR 11

// Pattern used to de-bias bits
#define DEBIAS_PATTERN 0b10101010

#include <EEPROM.h>

#include "RTClib.h"

#include "exixe.h"

#include "nixies.h"
#include "controlpanel.h"
#include "speaker.h"

RTC_DS3231 rtc;

volatile uint8_t didTrigger;
volatile unsigned long prevTrigTime;
volatile unsigned long trigCount;

volatile uint8_t ringBuff[256];

volatile uint8_t ringBuffWriteHead;

// Global variables for state machine
uint8_t turboMode;
uint8_t speakerOn;
uint8_t trigLedsOn;

uint16_t toggleNum;
uint8_t prevToggleNum; // Assists in clock's time-setting logic

// Interfaces to various hardware components
Nixies* nixies;
ControlPanel* controlPanel;
Speaker* speaker;

void geigerEvent() {
  if(trigLedsOn) {
    digitalWrite(UV_LED_PIN, HIGH);
  }

  if(speakerOn) {
    speaker->clickBegin();
  }

  didTrigger = 1;
  prevTrigTime = millis();
  trigCount++;
}

ISR(TIMER0_COMPA_vect) {
  // Turn off UV LEDs if it's been more than 50 ms since last trigger
  // Also a finish a "click" on the piezo speaker if it's been 1 ms or more
  unsigned long now = millis();

  unsigned long dt = now - prevTrigTime;

  if(dt > 50) {
    digitalWrite(UV_LED_PIN, LOW);
  }

  if(dt >= 1) {
    if(speakerOn) {
      speaker->clickEnd();
    }
  }

  // Handle this 1 ms window
  if(didTrigger) {
    ringBuff[ringBuffWriteHead] = 1;
    didTrigger = 0;
  }
  else {
    ringBuff[ringBuffWriteHead] = 0;
  }

  ringBuffWriteHead++;
}

uint8_t getRandByte(unsigned char callingPosition) {
  
  uint8_t randByte = 0;

  uint8_t ringBuffReadHead = ringBuffWriteHead - 2;

  uint8_t currBit = 0;

  uint8_t digits[] = {-1, -1, -1, -1, -1, -1, -1, -1};
  nixies->display(digits);

  while(currBit < 8) {

    uint8_t bitContribution = 0b00000001 << currBit;

    // Debias
    bitContribution = bitContribution ^ (DEBIAS_PATTERN & bitContribution);
    
    while(1) {
      if(controlPanel->switch_state(callingPosition) != LOW) {
        return 0;
      }

      uint8_t diff = ringBuffWriteHead - ringBuffReadHead;
      
      if(diff >= 2) {
        // Generate a bit
        uint8_t idx = ringBuffReadHead;
        ringBuffReadHead += 2;

        if(ringBuff[idx] == ringBuff[idx+1]) {
          continue;
        }
        else if((ringBuff[idx] == 1) && (ringBuff[idx+1] == 0)) {
          randByte += bitContribution;
          currBit++;
          break;
        }
        else if((ringBuff[idx] == 0) && (ringBuff[idx+1] == 1)) {
          randByte += bitContribution;
          currBit++;
          break;
        }
      }
      
    }
    
    uint8_t newBit = (randByte & bitContribution) >> (currBit-1);

    digits[currBit-1] = newBit;

    if(!turboMode) {
      nixies->display(digits);
    }
    else {
      nixies->display_led(digits);
    }
  }

  return randByte;
}

// Read off what number is indicated in the toggles
uint8_t readToggles() {
    uint8_t toggleNum = 0;
    if(controlPanel->switch_state(TOGGLE1) == LOW) {
      toggleNum += 16;
    }
    if(controlPanel->switch_state(TOGGLE2) == LOW) {
      toggleNum += 8;
    }
    if(controlPanel->switch_state(TOGGLE3) == LOW) {
      toggleNum += 4;
    }
    if(controlPanel->switch_state(TOGGLE4) == LOW) {
      toggleNum += 2;
    }

    return toggleNum;
}

void setup() {

  // Init real time clock
  rtc.begin();
  
  // put your setup code here, to run once:
  nixies = new Nixies();
  controlPanel = new ControlPanel();
  speaker = new Speaker();

  ringBuffWriteHead = 0;
  prevTrigTime = 0;
  trigCount = 0;
  ringBuff[ringBuffWriteHead] = 0;

  // Settings for Timer0 interrupt
  OCR0A = 0xAF; // Count at which to insert interrupt
  TIMSK0 |= _BV(OCIE0A);

  // Init LED flash pin
  pinMode(UV_LED_PIN, OUTPUT);

  // Is device in turbo mode?
  if(EEPROM.read(EEPROM_ADDR) == 0xFF) {
    // NOTE: 0xFF is what's stored when the Arduino is factory-fresh
    turboMode = 0;
  }
  else if(EEPROM.read(EEPROM_ADDR) == 0x00) {
    turboMode = 1;
  }

  // Attach geiger counter interrupt
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(0, geigerEvent, FALLING);

  // Initialize prevToggle num to max value so it doesn't trip clock-setting logic
  prevToggleNum = 30;
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned int rotPos1 = controlPanel->switch_state(ROTARYPOSITION1);
  unsigned int rotPos2 = controlPanel->switch_state(ROTARYPOSITION2);
  unsigned int rotPos3 = controlPanel->switch_state(ROTARYPOSITION3);
  toggleNum = readToggles();

  if((!rotPos2 || !rotPos3) && (trigCount < 20)) {
    // Wait to burn in some events
    nixies->clear();
    while(trigCount < 20) {
      char* displayDigits = Nixies::number_to_digits(trigCount, NO_ZERO_PAD);
      nixies->display(displayDigits);
      delay(10);
    }
  }

  if (rotPos1 == LOW) {
    // CLOCK MODE
    DateTime now = rtc.now();

    if(toggleNum > prevToggleNum) {
      uint8_t hour = now.hour();
      uint8_t minute = now.minute();
      uint8_t second = now.second();

      uint8_t toggleFlipped = toggleNum ^ prevToggleNum;

      switch(toggleFlipped) {
        case 16:
          // Increment hour
          hour = (hour + 1) % 24;
          break;
        case 8:
          // Increment 10 minutes
          minute = (minute + 10) % 60;
          break;
        case 4:
          // Increment 1 minute
          minute = (minute + 1) % 60;
          break;
        case 2:
          // Set seconds to zero
          second = 0;
          break;
      }

      // Not using this clock to keep track of days so just always make it 1/1/2000
      DateTime newDateTime = DateTime(2000, 1, 1, hour, minute, second);

      // Set the clock
      rtc.adjust(newDateTime);
    }

    unsigned long int hour_number = 1000000UL * (unsigned long int) now.hour();
    unsigned long int minute_number = 1000UL * (unsigned long int) now.minute();
    unsigned long int second_number = (unsigned long int) now.second();
    unsigned long int time_number = hour_number + minute_number + second_number;
    char* time_digits = Nixies::number_to_digits(time_number, ZERO_PAD);

    time_digits[2] = -1;
    time_digits[5] = -1;
    nixies->display(time_digits);
    delay(10);

    if(controlPanel->switch_state(PUSHBUTTON) == LOW) {
      while(true) {
        if(controlPanel->switch_state(PUSHBUTTON) == HIGH) {
          nixies->clear();
          break;
        }
      }
      delay(200);
      while(true) {
        if(controlPanel->switch_state(ROTARYPOSITION1) != LOW) {
          break;
        }
        if(controlPanel->switch_state(PUSHBUTTON) == LOW) {
          while(true) {
            if(controlPanel->switch_state(PUSHBUTTON) == HIGH) {
              delay(200);
              break;
            }
          }
          break;
        }
      }
    }
    prevToggleNum = toggleNum;
  }
  else if (rotPos2 == LOW) {
    // STREAMING MODE
    trigLedsOn = 1;
    speakerOn = !turboMode;

    nixies->clear();

    uint16_t delayTime;
    if(turboMode) {
      delayTime = 10;
    }
    else {
      delayTime = 1000;
    }

    if(toggleNum == 0) {
      toggleNum = 256;
    }

    uint8_t randByte;

    while(1) {
      randByte = getRandByte(ROTARYPOSITION2);
      if(randByte < (256 - (256 % toggleNum))) {
        break;
      }
    }

    if(controlPanel->switch_state(ROTARYPOSITION2) == LOW) {
      Serial.begin(19200);
      if(toggleNum == 256) {
        Serial.write(randByte);
      }
      else if(toggleNum != 256) {
        Serial.write((randByte % toggleNum) + 1);
      }
      Serial.end();
      delay(delayTime);

      char* displayDigits;

      if(!turboMode) {
        if(toggleNum == 256) {
          displayDigits = Nixies::number_to_digits(randByte, NO_ZERO_PAD);
        }
        else if(toggleNum != 256) {
          displayDigits = Nixies::number_to_digits((randByte % toggleNum) + 1, NO_ZERO_PAD);
        }
        nixies->display(displayDigits);
        delay(delayTime);
      }
    }

    if(controlPanel->switch_state(PUSHBUTTON) == LOW) {
      char all_lit[] = {0, 0, 0, 0, 0, 0, 0, 0};
      char all_off[] = {-1, -1, -1, -1, -1, -1, -1, -1};
      while(1) {
        nixies->display_led(all_lit);
        delay(100);
        nixies->display_led(all_off);
        delay(100);
        if(controlPanel->switch_state(PUSHBUTTON) == HIGH) {
          EEPROM.write(EEPROM_ADDR, ~EEPROM.read(EEPROM_ADDR));
          turboMode = !turboMode;
          break;
        }
      }
    }
  }
  else if(rotPos3 == LOW) {
    // DICE MODE
    trigLedsOn = 0;
    speakerOn = 0;
    nixies->clear();

    if(toggleNum != 0) {
      char* displayDigits = Nixies::number_to_digits(toggleNum, NO_ZERO_PAD);
      nixies->display(displayDigits);
      delay(50);
      nixies->clear();
      delay(50);
    }
    else {
      nixies->clear();
    }

    if((controlPanel->switch_state(PUSHBUTTON) == LOW) && (toggleNum != 0)) {

      uint8_t randByte;
      while(1) {
        trigLedsOn = 1;
        speakerOn = 1;
        randByte = getRandByte(ROTARYPOSITION3);
        if(randByte < (256 - (256 % toggleNum))) {
          trigLedsOn = 0;
          speakerOn = 0;
          break;
        }
      }
      delay(500);
      
      char* displayDigits = Nixies::number_to_digits((randByte % toggleNum) + 1, NO_ZERO_PAD);
      if(controlPanel->switch_state(ROTARYPOSITION3) == LOW) {
        while(1) {
          if(controlPanel->switch_state(ROTARYPOSITION3) != LOW) {
            break;
          }
          nixies->display(displayDigits);
          if(controlPanel->switch_state(PUSHBUTTON) == LOW) {
            break;
          }
        }
        delay(500);
      }
    }
  }
}




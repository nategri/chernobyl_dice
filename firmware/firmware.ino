#include <stdio.h>
#include <EEPROM.h>

#include "exixe.h"
#include <RTClib.h>

#define ROT1 12
#define ROT2 9
#define ROT3 15

#define TOGGLE1 16
#define TOGGLE2 17
#define TOGGLE3 20
#define TOGGLE4 21

#define PUSHBUTTON 10

#define NIX1 0
#define NIX2 1
#define NIX3 3
#define NIX4 4
#define NIX5 5
#define NIX6 6
#define NIX7 7
#define NIX8 8

#define UV_LED_PIN 14

#define ZERO_PAD 1
#define NO_ZERO_PAD 0

// Address to store whether or not device is in "turbo mode"
// Increment this if it starts acting funny (WOW YOU'VE TOGGLED IT A LOT HUH)
#define EEPROM_ADDR 11

class Nixies {
  public:
    static char* number_to_digits(unsigned long, const unsigned char);
    Nixies();
    void display(char*);
    void display_led(char*);
    void clear();
  private:
    exixe* _nixie[8];
};

static char* Nixies::number_to_digits(unsigned long num, const unsigned char zero_pad) {
  static char digits[8];
  for(int i=0; i<8; i++) {
    unsigned long pow10 = pow(10, i) + 0.5;
    digits[i] = (num / pow10) % 10;
  }

  if(!zero_pad) {
    // Clear leading zeros
    for(int i=7; i>=1; i--) {
      if(digits[i] != 0) {
        break;
      }
      else {
        digits[i] = -1;
      }
    }
  }

  return digits;
}

Nixies::Nixies() {
  this->_nixie[0] = new exixe(NIX7);
  this->_nixie[1] = new exixe(NIX8);
  this->_nixie[2] = new exixe(NIX6);
  this->_nixie[3] = new exixe(NIX5);
  this->_nixie[4] = new exixe(NIX4);
  this->_nixie[5] = new exixe(NIX3);
  this->_nixie[6] = new exixe(NIX2);
  this->_nixie[7] = new exixe(NIX1);

  this->_nixie[0]->spi_init();

  for(char i=0; i<8; i++) {
    this->_nixie[i]->clear();
    this->_nixie[i]->set_led(0, 0, 0);
  }

  for(char n=0; n<10; n++) {
    for(char i=0; i<8; i++) {
      this->_nixie[i]->show_digit(n+i, 127, 0);
    }
    delay(20);
  }

  for(char i=0; i<8; i++) {
    this->_nixie[i]->clear();
  }
}

void Nixies::display(char* digit) {
  for(char i=0; i<8; i++) {
    if(digit[i] < 0) {
      this->_nixie[i]->clear();
      this->_nixie[i]->set_led(0, 0, 0);
    }
    else {
      this->_nixie[i]->set_led(0, 0, 0);
      this->_nixie[i]->show_digit(digit[i], 127, 0);
    }
  }
}

void Nixies::display_led(char* digit) {
  for(char i=0; i<8; i++) {
    if(digit[i] < 0) {
      this->_nixie[i]->clear();
      this->_nixie[i]->set_led(0, 0, 0);
    }
    else {
      this->_nixie[i]->clear();
      this->_nixie[i]->set_led(127, 0, 0);
    }
  }
}

void Nixies::clear() {
  for(char i=0; i<8; i++) {
    this->_nixie[i]->clear();
  }
}

RTC_DS3231 rtc;

volatile uint8_t didTrigger;
volatile unsigned long prevTrigTime;
volatile unsigned long trigCount;

volatile unsigned long ringBuff[256];

volatile uint8_t ringBuffWriteHead;

uint8_t turboMode;

Nixies* nixies;

void geigerEvent() {
  digitalWrite(UV_LED_PIN, HIGH);

  didTrigger = 1;
  prevTrigTime = millis();
  trigCount++;
}

ISR(TIMER0_COMPA_vect) {
  // Turn off UV LEDs if it's been more than 50 ms since last trigger
  unsigned long now = millis();

  if((now - prevTrigTime) > 50) {
    digitalWrite(UV_LED_PIN, LOW);
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

// SIMPLE METHOD
uint8_t getRandByte(unsigned char callingPosition) {
  
  uint8_t randByte = 0;

  uint8_t ringBuffReadHead = ringBuffWriteHead - 2;

  uint8_t currBit = 0;

  uint8_t digits[] = {-1, -1, -1, -1, -1, -1, -1, -1};
  nixies->display(digits);

  while(currBit < 8) {

    uint8_t bitContribution = 0b00000001 << currBit;
    
    while(1) {
      if(digitalRead(callingPosition) != LOW) {
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

uint16_t readToggles() {
    uint16_t toggleNum = 0;
    if(digitalRead(TOGGLE1) == LOW) {
      toggleNum += 16;
    }
    if(digitalRead(TOGGLE2) == LOW) {
      toggleNum += 8;
    }
    if(analogRead(TOGGLE3) < 50) {
      toggleNum += 4;
    }
    if(analogRead(TOGGLE4) < 50) {
      toggleNum += 2;
    }

    return toggleNum;
}

void setup() {
  pinMode(ROT1, INPUT_PULLUP);
  pinMode(ROT2, INPUT_PULLUP);
  pinMode(ROT3, INPUT_PULLUP);

  pinMode(TOGGLE1, INPUT_PULLUP);
  pinMode(TOGGLE2, INPUT_PULLUP);
  // NB: Toggles 3 and 4 can only use analogRead(), cool

  pinMode(PUSHBUTTON, INPUT_PULLUP);
  
  rtc.begin();
  
  // put your setup code here, to run once:
  nixies = new Nixies();

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
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned int rotPos1 = digitalRead(ROT1);
  unsigned int rotPos2 = digitalRead(ROT2);
  unsigned int rotPos3 = digitalRead(ROT3);

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
    unsigned long int hour_number = 1000000UL * (unsigned long int) now.hour();
    unsigned long int minute_number = 1000UL * (unsigned long int) now.minute();
    unsigned long int second_number = (unsigned long int) now.second();
    unsigned long int time_number = hour_number + minute_number + second_number;
    char* time_digits = Nixies::number_to_digits(time_number, ZERO_PAD);

    time_digits[2] = -1;
    time_digits[5] = -1;
    nixies->display(time_digits);
    delay(10);

    if(digitalRead(PUSHBUTTON) == LOW) {
      while(true) {
        if(digitalRead(PUSHBUTTON) == HIGH) {
          nixies->clear();
          break;
        }
      }
      delay(200);
      while(true) {
        if(digitalRead(ROT1) != LOW) {
          break;
        }
        if(digitalRead(PUSHBUTTON) == LOW) {
          while(true) {
            if(digitalRead(PUSHBUTTON) == HIGH) {
              delay(200);
              break;
            }
          }
          break;
        }
      }
    }
  }
  else if (rotPos2 == LOW) {
    // STREAMING MODE
    nixies->clear();

    uint16_t delayTime;
    if(turboMode) {
      delayTime = 10;
    }
    else {
      delayTime = 1000;
    }

    uint16_t toggleNum = readToggles();
    if(toggleNum == 0) {
      toggleNum = 256;
    }

    uint8_t randByte;

    while(1) {
      randByte = getRandByte(ROT2);
      if(randByte < (256 - (256 % toggleNum))) {
        break;
      }
    }

    if(digitalRead(ROT2) == LOW) {
      Serial.begin(300);
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

    if(digitalRead(PUSHBUTTON) == LOW) {
      char all_lit[] = {0, 0, 0, 0, 0, 0, 0, 0};
      char all_off[] = {-1, -1, -1, -1, -1, -1, -1, -1};
      while(1) {
        nixies->display_led(all_lit);
        delay(100);
        nixies->display_led(all_off);
        delay(100);
        if(digitalRead(PUSHBUTTON) == HIGH) {
          EEPROM.write(EEPROM_ADDR, ~EEPROM.read(EEPROM_ADDR));
          turboMode = !turboMode;
          break;
        }
      }
    }
  }
  else if(rotPos3 == LOW) {
    nixies->clear();
    
    uint8_t toggleNum = readToggles();

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

    if((digitalRead(PUSHBUTTON) == LOW) && (toggleNum != 0)) {

      uint8_t randByte;
      while(1) {
        randByte = getRandByte(ROT3);
        if(randByte < (256 - (256 % toggleNum))) {
          break;
        }
      }
      delay(500);
      
      char* displayDigits = Nixies::number_to_digits((randByte % toggleNum) + 1, NO_ZERO_PAD);
      if(digitalRead(ROT3) == LOW) {
        while(1) {
          if(digitalRead(ROT3) != LOW) {
            break;
          }
          nixies->display(displayDigits);
          if(digitalRead(PUSHBUTTON) == LOW) {
            break;
          }
        }
        delay(500);
      }
    }
  }
}




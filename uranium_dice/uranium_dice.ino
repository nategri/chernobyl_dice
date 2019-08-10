#define UV_LED_PIN 8

#include <SPI.h>

volatile uint8_t didTrigger;
volatile unsigned long prevTrigTime;
volatile unsigned long trigCount;

volatile unsigned long ringBuff[256];

volatile uint8_t ringBuffWriteHead;

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
uint8_t getRandByte() {
  
  uint8_t randByte = 0;

  uint8_t ringBuffReadHead = ringBuffWriteHead - 2;

  uint8_t currBit = 0;
  while(currBit < 8) {



    uint8_t bitContribution = 0b00000001 << currBit;
    
    while(1) {


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


    
  }

  return randByte;
}

void setup() {
  Serial.begin(19200);
  
  // put your setup code here, to run once:

  ringBuffWriteHead = 0;
  prevTrigTime = 0;
  trigCount = 0;
  ringBuff[ringBuffWriteHead] = 0;

  // Settings for Timer0 interrupt
  OCR0A = 0xAF; // Count at which to insert interrupt
  TIMSK0 |= _BV(OCIE0A);

  // Init LED flash pin
  pinMode(UV_LED_PIN, OUTPUT);

  // Attach geiger counter interrupt
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(0, geigerEvent, FALLING);

  // Wait to burn in some events
  while(trigCount < 20) {
    delay(10);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  uint8_t randByte = getRandByte();
  Serial.write(randByte);
  delay(10);
}

#define UV_LED_PIN 8

#include <SPI.h>

volatile unsigned long prevTrigTime;
volatile unsigned long trigCount;

volatile unsigned long timeRingBuff[256];
volatile uint8_t bitRingBuff[256];

volatile uint8_t timeRingBuffWriteHead;
volatile uint8_t bitRingBuffWriteHead;

void geigerEvent() {
  digitalWrite(UV_LED_PIN, HIGH);
  
  uint8_t timeIdx = timeRingBuffWriteHead;
  uint8_t bitIdx = bitRingBuffWriteHead;
  
  unsigned long trigTime = micros() / 4;
  unsigned long deltaT = trigTime - prevTrigTime;
  
  timeRingBuff[timeIdx] =  deltaT;
  timeRingBuffWriteHead++;

  if(timeRingBuff[timeIdx] > timeRingBuff[timeIdx-2]) {
    bitRingBuff[bitIdx] = 1;
    bitRingBuffWriteHead++;
  }
  else if(timeRingBuff[timeIdx] < timeRingBuff[timeIdx-2]) {
    bitRingBuff[bitIdx] = 0;
    bitRingBuffWriteHead++;
  }

  bitIdx = bitRingBuffWriteHead;
  bitRingBuff[bitIdx] = deltaT % 2;
  bitRingBuffWriteHead++;

  trigCount++;

  prevTrigTime = trigTime;
}

// VON NEUMAN METHOD
uint8_t getRandByte() {
  
  uint8_t randByte = 0;

  uint8_t bitRingBuffReadHead = bitRingBuffWriteHead - 2;

  uint8_t currBit = 0;
  while(currBit < 8) {
    
    while(1) {

      uint8_t diff = bitRingBuffWriteHead - bitRingBuffReadHead;
      
      if(diff >= 2) {
        // Generate a bit
        uint8_t idx = bitRingBuffReadHead;
        bitRingBuffReadHead += 2;

        if((bitRingBuff[idx] ^ bitRingBuff[idx+1]) == 0) {
          // 11 or 00
          continue;
        }
        else if((bitRingBuff[idx] == 1) && (bitRingBuff[idx+1] == 0)) {
          // 10
          randByte += 0b00000001 << currBit;
          currBit++;
          break;
        }
        else {
          // 01 is all that's left
          currBit++;
          break;
        }
        

      }
      
    }
    
  }

  return randByte;
}

/*
// SIMPLE METHOD
uint8_t getRandByte() {
  
  uint8_t randByte = 0;

  uint8_t ringBuffReadHead = ringBuffWriteHead - 1;

  uint8_t currBit = 0;
  while(currBit < 8) {
    
    while(1) {

      uint8_t diff = ringBuffWriteHead - ringBuffReadHead;
      
      if(diff >= 1) {
        // Generate a bit
        uint8_t idx = ringBuffReadHead % 128;
        ringBuffReadHead += 1;

        uint8_t xor_bit;
        if(ringBuff[idx] < ringBuff[idx-2]) {
          xor_bit = 1;
        }
        else if(ringBuff[idx] > ringBuff[idx-2]) {
          xor_bit = 0;
        }
        else {
          continue;
        }

        uint8_t bitContribution = 0b00000001 << currBit;
        if((ringBuff[idx] % 2) == 1) {
          randByte += bitContribution;
        }
        
        randByte = randByte ^ (xor_bit << currBit);

        currBit++;
        break;
        

      }
      
    }
    
  }

  return randByte;
}
*/

void setup() {
  Serial.begin(19200);
  
  // put your setup code here, to run once:

  timeRingBuffWriteHead = 0;
  bitRingBuffWriteHead = 0;
  prevTrigTime = 0;
  trigCount = 0;

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

ISR(TIMER0_COMPA_vect) {
  unsigned long now = micros() / 4;

  if((now - prevTrigTime) > 12500) {
    digitalWrite(UV_LED_PIN, LOW);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  uint8_t randByte = getRandByte();
  Serial.write(randByte);
}

#ifndef SPEAKER_H
#define SPEAKER_H

#include <Arduino.h>

#define SPEAKER_PIN_A 17
#define SPEAKER_PIN_B 12

class Speaker {
  public:
    Speaker();
    void clickBegin();
    void clickEnd();
};

#endif

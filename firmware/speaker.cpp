#include "speaker.h"

Speaker::Speaker() {
  pinMode(SPEAKER_PIN_A, OUTPUT);
  pinMode(SPEAKER_PIN_B, OUTPUT);

  digitalWrite(SPEAKER_PIN_A, LOW);
  digitalWrite(SPEAKER_PIN_B, LOW);
}

void Speaker::clickBegin() {
  digitalWrite(SPEAKER_PIN_A, HIGH);
  digitalWrite(SPEAKER_PIN_B, LOW);
}

void Speaker::clickEnd() {
  digitalWrite(SPEAKER_PIN_A, LOW);
  digitalWrite(SPEAKER_PIN_B, HIGH);
}

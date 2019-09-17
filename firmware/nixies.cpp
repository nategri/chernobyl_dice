#include "nixies.h"

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
      this->_nixie[i]->set_led(127, 4, 0);
    }
  }
}

void Nixies::clear() {
  for(char i=0; i<8; i++) {
    this->_nixie[i]->clear();
  }
}

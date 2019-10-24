#ifndef NIXIES_H
#define NIXIES_H

#define ZERO_PAD 1
#define NO_ZERO_PAD 0

#define NIX1 3
#define NIX2 4
#define NIX3 5
#define NIX4 6
#define NIX5 7
#define NIX6 8
#define NIX7 9
#define NIX8 10

#include "exixe.h"

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

#endif

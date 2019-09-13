#ifndef NIXIES_HPP
#define NIXIES_HPP

#define NIX1 0
#define NIX2 1
#define NIX3 3
#define NIX4 4
#define NIX5 5
#define NIX6 6
#define NIX7 7
#define NIX8 8

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

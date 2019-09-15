#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#define ROTARYPOSITION1 0 
#define ROTARYPOSITION2 1
#define ROTARYPOSITION3 2

#define TOGGLE1 3
#define TOGGLE2 4
#define TOGGLE3 5
#define TOGGLE4 6

#define PUSHBUTTON 7

#include "Adafruit_MCP23008_mod.h"

class ControlPanel {
  public:
    ControlPanel();
    uint8_t switch_state(uint8_t);

  private:
    Adafruit_MCP23008* _mcp;
};

#endif

#include "controlpanel.h"

ControlPanel::ControlPanel() {
  this->_mcp = new Adafruit_MCP23008();
  
  this->_mcp->begin();

  // Everything is a switch on this board
  // Turn on all pull-up resistors
  for(uint8_t i=0; i<8; i++) {
    this->_mcp->pinMode(i, INPUT);
    this->_mcp->pullUp(i, HIGH);
  }
}

uint8_t ControlPanel::switch_state(uint8_t input_pin) {
  return this->_mcp->digitalRead(input_pin);
}

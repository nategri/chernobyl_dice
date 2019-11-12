<p align="center"><img src="/images/chernobyl_dice.jpg"></p>

## Introduction

#### Description

The Chernobyl Dice is a true random number generator that uses nuclear decays from a weakly radioactive sample
as an entropy source. It consists of four primary components:

* An Arduino Nano microcontroller
* A Geiger counter
* Six uranium glass marbles
* Nixie tube display

Geiger counter events ("clicks") are converted into random bits using the following algorithm:

1. In a ring buffer, record either a 0 or a 1, depending on whether or not a Geiger event occurred
2. Debias this 0-dominated stream into an ubiased stream using von Neumann's methode [0]

#### Operation

The device has a three modes of operations, which can be selected via the rotary switch:

*Clock Mode*
Displays the current time, with the Geiger board unpowered. The time can be set by flipping the toggle switches on and off
(the '16' toggle increments the hour, the '8' toggle increments 10 minutes, the '4' toggle increments 1 minute, and the
'1' toggle resets the seconds).

*Streaming Mode*
Repeatedly generates random numbers of a size specified by the toggles (or random bytes from 0-255 if no toggles are set). Numbers
generated in this mode are transmitted over serial via USB. This mode also has a "turbo" setting to facilitate statistical testing,
which can be enabled by holding down the pushbutton. When "turbo" is enabled bit generation will be indicated by LEDs in the
display, and the Geiger "clicks" will be silent.

*Streaming Mode*
In dice mode random number generation is initiated via the pushbotton, and the size of the random number to be generated is set
by the sum of the toggled switches (no switches are set the device will generate random byte in the range 0-255). Press
once to generate the number, and once again to clear the display. The size of the number to be generated is displayed in
blinking digits.

#### Assembly

## References

[0] https://en.wikipedia.org/wiki/Hardware_random_number_generator#Dealing_with_bias

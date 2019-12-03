# Chernobyl Dice

<p align="center"><img src="/images/chernobyl_dice.jpg"></p>

## Introduction

#### Description

The Chernobyl Dice is a quantum random number generator that uses nuclear decays from a weakly radioactive sample
as a source of entropy. It consists of four primary components:

* An Arduino Nano microcontroller
* A Geiger counter
* Six uranium glass marbles
* Nixie tube display

Geiger counter events ("clicks") are converted into random bits by taking the mod2 of the total number of
4 microsecond "ticks" that have passed since the device was switched on (e.g. the device outputs a "0" if the
Geiger tube triggers on an even tick, and output a "1" if it triggers on an odd microsecond). [0]

The uranium glass sample is illuminated by an array of ultraviolet LEDs at each Geiger event, which makes them
fluoresce bright green. This has nothing to do with the radioactivity of the sample, but it does, however, *look
really cool*.

#### Operation

The device has three modes of operations, which can be selected via the rotary switch:

*Clock Mode*

Displays the current time, with the Geiger board unpowered. The time can be set by flipping the toggle switches on and off
(the '16' toggle increments the hour, the '8' toggle increments 10 minutes, the '4' toggle increments 1 minute, and the
'1' toggle resets the seconds).

*Streaming Mode*

Repeatedly generates random numbers of a size specified by the toggles (or random bytes from 0-255 if no toggles are set). Numbers
generated in this mode are transmitted over serial via USB. This mode also has a "turbo" setting to facilitate statistical testing,
which can be enabled by holding down the pushbutton. When "turbo" is enabled bit generation will be indicated by LEDs in the
display, and the Geiger "clicks" will be silent.

*Dice Mode*

In dice mode random number generation is initiated via the pushbotton, and the size of the random number to be generated is set
by the sum of the toggled switches (no switches are set the device will generate random byte in the range 0-255). Press
once to generate the number, and once again to clear the display. The size of the number to be generated is displayed in
blinking digits.

## CAD Drawing

A Fusion 360 CAD drawing of the device can be viewed and downloaded at this URL:

https://a360.co/2OeFT1n

Thanks to the following GrabCAD users for their models:
* [Alex](https://grabcad.com/alex-160) (Nixie tube)
* [Mike Smith](https://grabcad.com/mike.smith-208) (Arduino Nano)
* [Dragos Ionescu](https://grabcad.com/dragos.ionescu-2) (Various pin headers)

## Overview and Parts List

*WARNING: These instructions and resources are not polished and are somewhat untested. This is a project for advanced makers, and
you should fully expect to have a bit of an adventure while building your own Chernobyl Dice! That said: Shoot me a message if
you run into trouble, and I'll try to help you out and improve the instructions as well.*

<p align="center"><img src="/images/parts_list.png"></p>

Here's a rough outline of the steps required for assembly:

1. Print or fabricate the following custom parts from files in the GitHub repository
    * Enclosure (using 3D printer or 3D printing service)
    * Logic, Nixie Display, and Control Panel Custom PCBs (using a board fabrication service such as OSHPark)
    * Stainless steel front panel (using a service such as OSHCut)
    * Acrylic back panel (using a service such as Sculpeo)
2. Order other components (see URLs in the parts list)
3. Embed brass standoffs into enclosure (this is how front and back panels and custom PCBs will be mounted)
    * TIPS
      * A single drop of cyanocrylate (Super Glue) should be placed in the standoff holes in the enclosure before they are pressed
        in (the tip of a Phillips head screw driver workds well for this task)
      * If the tops some holes came out of the printer a bit distorted then they can be widened easily by twisting a largish
        Phillips head scewdriver in them until the top of the hole is wide enough.

4. Assemble custom PCBs and 'exixe' nixie tube driver boards using build photos as a guide
    * TIPS
      * The female headers on the Nixie Display Board for the nixie tube driver PCBs can be assembled using only four long female
        header strips (e.g. there's no need to separately attach sixteen 7-pin female headers---see photos)
      * The "CS" 8-pin male header is a currently a tight fit, so you will probably need to use needle noise pliers to push the pins
        through the board
      * For the control panel PCB you can temporarily mount the toggle switches in the front panel and then press the PCB on top of
        the back of the switches to ensure good alignment---you can then pull the whole board-and-toggle assembly off of the front
        panel to solder it, or even solder it in place and then pull it off
      * The file 'nixie_jig.stl' is a provided as a useful place to rest the nixie tube while soldering them to the 'exixe' driver
        boards
5. Attach the acrylic back panel and panel mount USB cable to the rear of the enclosure
6. Mount custom PCBs inside enclosure and perform wiring (see wiring schematic and build photos)
7. Partially dis-assemble rotary switch to attach it to the "lock plate" (lock_plate.stl)
8. Perform any necessary finishing to the stainless steel front panel
    * TIPS
      * Some mounting holes for toggles and switches may need to be widened (use a round file for this)
      * Surface finish of a lasercut part can be improved by sanding *with the grain* using ~300 grit sandpaper (test on the back
        side first)
9. Mount toggle-and-PCB assembly, LED-with-holder assemblies, rotary-switch-and-lock-plate assembly, and pushbutton on front panel
    * TIP
      * While attaching the LED to the holder, apply a drop of cyanocrylate (SuperGlue) to prevent the LED from falling out of the
        front of the holder
10. Perform wiring of the control panel (see wiring schematic and build photos)
11. Fit the eight nixie display driver boards into the female headers of the Nixie Display Board
12. Wire the Control Panel to the Logic Board
13. Mount the front panel to the enclosure, taking care to insure that the hole in the rotary switch lock plate lines up with the
    upper-left standoff on the front of the radioactive sample holder

**Standoff Size Guide**

| Location | Standoff Length | Type |
| --- | --- | --- |
| Rear of enclosure | 10 mm | Female-Female |
| Front of enclosure | 10 mm | Female-Female |
| Nixie Display Board mount | 40 mm | Female-Female |
| Logic Board mount | 20 mm | Female-Female|
| Logic Board-to-Geiger Board | 30 mm | Male-Female |
| Geiger Board-to-Bottom of Uranium Sample Box | 15 mm | Male-Female |
| Bottom of Uranium Sample Box-to-Top of Uranium Sample Box | 6 mm | Male-Female |
| Top of Uranium Sample Box-to-Front Panel | 6 mm | Male-Female |

NOTE: For large internal standoff distances (e.g. the Nixie Display mount) two standoffs can be stacked to achieve
the desired distance.

## Wiring Diagram

<p align="center"><img src="/images/chernobyl_dice_wiring_schematic.jpg"></p>
<p align="center"><i>How connect the internal wiring of the Chernobyl Dice.</i></p>

## Build Photos

**Enclosure with Standoffs Inserted**
<p align="center"><img src="/images/build/small/1.JPG"></p>
<p align="center"><i>
<a href="https://raw.githubusercontent.com/nategri/chernobyl_dice/master/images/build/large/1.JPG">Click here</a>
for larger photo.
</i></p>

<br><br><br>

**Logic Board Mounted**
<p align="center"><img src="/images/build/small/2.JPG"></p>
<p align="center"><i>
<a href="https://raw.githubusercontent.com/nategri/chernobyl_dice/master/images/build/large/2.JPG">Click here</a>
for larger photo.
</i></p>

<br><br><br>

**Nixie Display Board Wiring**
<p align="center"><img src="/images/build/small/3.JPG"></p>
<p align="center"><i>
<a href="https://raw.githubusercontent.com/nategri/chernobyl_dice/master/images/build/large/3.JPG">Click here</a>
for larger photo.
</i></p>

<br><br><br>

**Nixie Display Board Mounted and Logic Board Wiring**
<p align="center"><img src="/images/build/small/4.JPG"></p>
<p align="center"><i>
<a href="https://raw.githubusercontent.com/nategri/chernobyl_dice/master/images/build/large/4.JPG">Click here</a>
for larger photo.
</i></p>

<br><br><br>

**Geiger Board Mounted**
<p align="center"><img src="/images/build/small/5.JPG"></p>
<p align="center"><i>
<a href="https://raw.githubusercontent.com/nategri/chernobyl_dice/master/images/build/large/5.JPG">Click here</a>
for larger photo.
</i></p>

<br><br><br>

*Uranium Sample Holder Lower Half Detail*
<p align="center"><img src="/images/build/small/6.JPG"></p>
<p align="center"><i>
<a href="https://raw.githubusercontent.com/nategri/chernobyl_dice/master/images/build/large/6.JPG">Click here</a>
for larger photo.
</i></p>

<br><br><br>

*Uranium Sample Holder Lower Half Mounted*
<p align="center"><img src="/images/build/small/7.JPG"></p>
<p align="center"><i>
<a href="https://raw.githubusercontent.com/nategri/chernobyl_dice/master/images/build/large/7.JPG">Click here</a>
for larger photo.
</i></p>

<br><br><br>

*Uranium Sample Holder Top Half Mounted*
<p align="center"><img src="/images/build/small/8.JPG"></p>
<p align="center"><i>
<a href="https://raw.githubusercontent.com/nategri/chernobyl_dice/master/images/build/large/8.JPG">Click here</a>
for larger photo.
</i></p>

<br><br><br>

*Control Panel Board Wired*
<p align="center"><img src="/images/build/small/9.JPG"></p>
<p align="center"><i>
<a href="https://raw.githubusercontent.com/nategri/chernobyl_dice/master/images/build/large/9.JPG">Click here</a>
for larger photo.
</i></p>

<br><br><br>

*Control Panel Board Wiring Detail*
<p align="center"><img src="/images/build/small/10.JPG"></p>
<p align="center"><i>
<a href="https://raw.githubusercontent.com/nategri/chernobyl_dice/master/images/build/large/10.JPG">Click here</a>
for larger photo.
</i></p>

## Acknowledgements

Many thanks to Emily Velasco (@MLE_Online) for advice on stainless surface sanding, and for generally being enthusiastic
as heck about this project.

## References

[0] "Quantum Random Number Generators." M. Herrero-Collantes and J. C. Garcia-Escartin. https://arxiv.org/abs/1604.03304

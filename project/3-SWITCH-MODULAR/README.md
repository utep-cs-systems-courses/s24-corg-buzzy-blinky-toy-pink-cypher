## Description
This program uses interrupts to detect when a switch is pressed or
released.

Press S1, and the green LED is illuminated.  Release it, and the red
LED is illuminated instead.

This implementation separates different domains of control to different files:

* led.c controls the leds based on state vars
* switches.c responds to the switch and sets the values of state vars

I will attempt to have them both on and then do different things once the buttons are pressed
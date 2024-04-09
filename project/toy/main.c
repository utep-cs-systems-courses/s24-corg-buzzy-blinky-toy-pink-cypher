A#include <msp430.h>
#include "libTimer.h"
#include "led.h"

// Alternate LEDs from Off, Green, and Red

int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks();            /* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();        /* enable periodic interrupt */

  or_sr(0x18);                  /* CPU off, GIE on */
}

// global state vars that control blinking
int greenBrightness = 0;  // brightness level for green LED
int redBrightness = 0;  // brightness level for red LED
int greenDirection = 1;  // direction of green brightness change (dim to bright or bright to dim)
int redDirection = 1;  // direction of red brightness change (dim to bright or bright to dim)
int greenSpeed = 5;  // speed of green brightness change
int redSpeed = 3;  // speed of red brightness change
int secondCount = 0; // state var representing repeating time 0…1s

void __interrupt_vec(WDT_VECTOR) WDT() { /* 250 interrupts/sec */
    // handle green LED brightness change
    greenBrightness += greenDirection;
    if (greenBrightness >= greenSpeed || greenBrightness <= 0) {
        greenDirection = -greenDirection;  // change direction when reaching limits
    }
    if (greenBrightness > 0) {
        P1OUT |= LED_GREEN;  // fully on
    } else {
        P1OUT &= ~LED_GREEN;  // fully off
    }

    // handle red LED brightness change
    redBrightness += redDirection;
    if (redBrightness >= redSpeed || redBrightness <= 0) {
        redDirection = -redDirection;  // change direction when reaching limits
    }
    if (redBrightness > 0) {
        P1OUT |= LED_RED;  // fully on
    } else {
        P1OUT &= ~LED_RED;  // fully off
    }

    // update brightness levels
    secondCount++;
    if (secondCount >= 250) {  // once each second
        secondCount = 0;
        greenSpeed++;  // change the speed of green brightness change
        redSpeed++;  // change the speed of red brightness change
    }
}

// blink state machine
static int blinkLimit = 5;   //  state var representing reciprocal of duty cycle 
void blinkUpdate() // called every 1/250s to blink with duty cycle 1/blinkLimit
{
  static int blinkCount = 0; // state var representing blink state
  blinkCount ++;
  if (blinkCount >= blinkLimit) {
    blinkCount = 0;
    ledControl(1);
  } else
    ledControl(0);
}

void oncePerSecond() // repeatedly start bright and gradually lower duty cycle, one step/sec
{
  blinkLimit ++;  // reduce duty cycle
  if (blinkLimit >= 8)  // but don't let duty cycle go below 1/7.
    blinkLimit = 0;
}

void secondUpdate()  // called every 1/250 sec to call oncePerSecond once per second
{
  static int secondCount = 0; // state variable representing repeating time 0…1s
  secondCount ++;
  if (secondCount >= 250) { // once each second
    secondCount = 0;
    oncePerSecond();
  } 
}

void timeAdvStateMachines() // called every 1/250 sec
{
  blinkUpdate();
  secondUpdate();
}

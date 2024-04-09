#include <msp430.h>
#include "led.h"

void ledControl(int on)
{
  if (on) {
    P1OUT |= LED_GREEN;
    P1OUT &= ~LED_RED;
  } else {
    P1OUT &= ~LED_GREEN;
    P1OUT |= LED_RED;
  }

}

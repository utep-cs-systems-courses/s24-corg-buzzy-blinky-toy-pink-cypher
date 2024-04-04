//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  
  or_sr(0x18);			/* CPU off, GIE on */
}

// global state vars that control blinking
int greenBlinkLimit = 5;  // duty cycle = 1/greenBlinkLimit
int greenBlinkCount = 0;  // cycles 0...greenBlinkLimit-1
int redBlinkLimit = 5;  // duty cycle = 1/redBlinkLimit
int redBlinkCount = 0;  // cycles 0...redBlinkLimit-1
int brightness = 0; // brightness level
int secondCount = 0; //state var representing repeating time 0…1s

void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  // handles green LED blinking 
  greenBlinkCount ++;
  if (greenBlinkCount >= greenBlinkLimit) { // on for 1 interrupt period
    greenBlinkCount = 0;
    if (brightness >= greenBlinkLimit)
      P1OUT |= LED_GREEN; //full off
  else
    P1OUT &= ~LED_GREEN; // fully on
  }

   // handle red LED blinking
   redBlinkCount++;
   if (redBlinkCount >= redBlinkLimit) { // on for 1 interrupt period
     redBlinkCount = 0;
     if (brightness >= redBlinkLimit)
       P1OUT |= LED_RED; // fully off
   else
     P1OUT &= ~LED_RED; // fully on
   }
    

    // update brightness level
    brightness++;
    if (brightness >= greenBlinkLimit) {
        brightness = 0;
    }

     // measure a second                                                                                                                                                                                       
  secondCount ++;
  if (secondCount >= 250) {  // once each second                                                                                                                                                            
    secondCount = 0;
    greenBlinkLimit ++;           // reduce duty cycle
    redBlinkLimit ++;
    
    if (greenBlinkLimit >= 8)     // but don't let duty cycle go below 1/7.                                                                                                                                      
      greenBlinkLimit = 0;

    if (redBlinkLimit >= 8)

      redBlinkLimit = 0;
  }
}

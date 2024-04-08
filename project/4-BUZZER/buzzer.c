#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

void buzzer_init()
{
    /* 
       Direct timer A output "TA0.1" to P2.6.  
        According to table 21 from data sheet:
          P2SEL2.6, P2SEL2.7, anmd P2SEL.7 must be zero
          P2SEL.6 must be 1
        Also: P2.6 direction must be output
    */
    timerAUpmode();		/* used to drive speaker */
    P2SEL2 &= ~(BIT6 | BIT7);
    P2SEL &= ~BIT7; 
    P2SEL |= BIT6;
    P2DIR = BIT6;		/* enable output to speaker (P2.6) */
}

void buzzer_set_period(short cycles) /* buzzer clock = 2MHz.  (period of 1k results in 2kHz tone) */
{
  CCR0 = cycles; 
  CCR1 = cycles >> 1;		/* one half cycle */
}

void button_init() {
    P1DIR &= ~BIT0;     // Set P1.0 as input
    P1REN |= BIT0;      // Enable pull-up resistor on P1.0
    P1OUT |= BIT0;      // Set pull-up resistor on P1.0
    P1IE |= BIT0;       // Enable interrupt on P1.0
    P1IES |= BIT0;      // Set interrupt to trigger on falling edge
    P1IFG &= ~BIT0;     // Clear P1.0 interrupt flag
}
    
    
  

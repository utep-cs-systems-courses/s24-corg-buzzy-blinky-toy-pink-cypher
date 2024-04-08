#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

#define SW1 BIT3		/* switch1 is p1.3 */
#define SWITCHES SW1		/* only 1 switch on this board */


int main() {
    configureClocks();
 
    buzzer_init();
    buzzer_set_period(1000);	/* start buzzing!!! 2MHz/1000 = 2kHz*/


    or_sr(0x18);          // CPU off, GIE on
}
// Interrupt service routine for button press
#pragma vector=PORT1_VECTOR
__interrupt void Port_1() {
    if (P1IFG & BIT0) {     // Check if P1.0 interrupt flag is set
        buzzer_set_period(2000);    // Change tone to 2kHz
        P1IFG &= ~BIT0;     // Clear P1.0 interrupt flag
    }
}

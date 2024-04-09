#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h" // Include the switches header file

// Alternate LEDs from Off, Green, and Red

int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks();            /* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();        /* enable periodic interrupt */
  
  switch_init();                // Initialize switches

  or_sr(0x18);                  /* CPU off, GIE on */
}

// Function to handle LED control based on switch state
void switchLEDControl(int sw_state) {
  switch(sw_state) {
    case 1: // SW1 pressed
      P1OUT |= LED_GREEN;  // fully on
      P1OUT &= ~LED_RED;  // fully off
      break;
    case 2: // SW2 pressed
      P1OUT &= ~LED_GREEN;  // fully off
      P1OUT |= LED_RED;  // fully on
      break;
    case 3: // SW3 pressed
      P1OUT |= LED_GREEN;  // fully on
      P1OUT |= LED_RED;  // fully on
      break;
    case 4: // SW4 pressed
      P1OUT &= ~LED_GREEN;  // fully off
      P1OUT &= ~LED_RED;  // fully off
      break;
    default:
      break;
  }
}

// blink state machine
static int blinkLimit = 5;   // state var representing reciprocal of duty cycle 
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

// Interrupt service routine for switches
void __interrupt_vec(PORT2_VECTOR) Port_2() {
  if (P2IFG & SWITCHES) { // Check if any switch caused the interrupt
    P2IFG &= ~SWITCHES;   // Clear the interrupt flags for the switches
    switch_interrupt_handler(); // Handle the switch interrupt
    switchLEDControl(switch_state_down); // Control LEDs based on switch state
  }
}

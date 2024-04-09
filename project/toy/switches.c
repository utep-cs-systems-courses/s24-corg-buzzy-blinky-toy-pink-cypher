#include <msp430.h>
#include "switches.h"
#include "buzzer.h" // Include buzzer header file

char switch_state_down = 0; // Definition of the variable

static char switch_update_interrupt_sense()
{
  char p2val = P2IN;
  // update switch interrupt to detect changes from current buttons
  P2IES |= (p2val & SWITCHES);    // if switch up, sense down
  P2IES &= (p2val | ~SWITCHES);   // if switch down, sense up
  return p2val;
}

void switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();

  // Stop the buzzer when SW0 is pressed
  if ((p2val & SW0) == 0) // Check if SW0 is pressed
  {
    buzzer_stop(); // Stop the buzzer
  }

  switch_state_down = (p2val & SWITCHES); // switch's bit is 1 when button is up
}

void switch_init() // setup switch
{
  P2REN |= SWITCHES;    // enables resistors for switches
  P2IE = SWITCHES;      // enable interrupts from switches
  P2OUT |= SWITCHES;    // pull-ups for switches
  P2DIR &= ~SWITCHES;   // set switches' bits for input
  switch_update_interrupt_sense();
  switch_interrupt_handler();    // to initially call the handler to set the buzzer state
}

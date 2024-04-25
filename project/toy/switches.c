#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "buzzer.h"
#include "stateMachines.h"

char sw1_state, sw2_state, sw3_state, sw4_state; // Variables to track switch states
char sw_state_changed; // Flag to indicate if switch state changed
char switch_state = 0; // Variable to store the current switch state, initialized to 0

static char switch_update_interrupt_sense(){
  char p2val = P2IN;
  P2IES |= (p2val & SWITCHES);
  P2IES &= (p2val | ~SWITCHES);
  return p2val;
}

void switch_init(){
  P2REN |= SWITCHES;
  P2IE = SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
  switch_update_interrupt_sense();
}

void switch_interrupt_handler(){
  char p2val = switch_update_interrupt_sense();

  // Update individual switch states
  sw1_state = (p2val & SW1) ? 0 : 1; // Indicates which button of the 4 was pressed
  sw2_state = (p2val & SW2) ? 0 : 1;
  sw3_state = (p2val & SW3) ? 0 : 1;
  sw4_state = (p2val & SW4) ? 0 : 1;

  // Set switch state based on pressed button
  if (sw1_state)
    switch_state = 1;
  if (sw2_state)
    switch_state = 2;
  if (sw3_state)
    switch_state = 3;
  if (sw4_state)
    switch_state = 4;

  sw_state_changed = 1; // Signal that a button was pressed
}

#include <msp430.h>
#include "switches.h"

char switch_state_down = 0; // Definition of the variable

void switch_interrupt_handler() {
  // Update switch_state_down based on the actual switch state
  switch_state_down = P2IN & SWITCHES;
}

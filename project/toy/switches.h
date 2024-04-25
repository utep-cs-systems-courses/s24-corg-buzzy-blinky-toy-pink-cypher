#ifndef switches_included
#define switches_included

#define SW1 BIT0
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3

#define SWITCHES (SW1 | SW2 | SW3 | SW4)

void switch_init(); // Initializes the switches
void switch_interrupt_handler(); // Handles switch interrupts

extern char sw1_state, sw2_state, sw3_state, sw4_state; // Variables to track switch states
extern char sw_state_changed; // Flag to indicate if switch state changed

#endif

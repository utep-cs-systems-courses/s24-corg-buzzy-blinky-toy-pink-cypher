#include <msp430.h>
#include "led.h"
#include "stateMachines.h"


// variables to track LED states and switch states
unsigned char red_on = 0,green_on = 0;
unsigned char led_switch = 0;
char switch2_state,switch3_state;
char switch_state_changed;

// arrays to map LED values
static char redValue[] = {0,LED_RED},greenValue[] = {0,LED_GREEN};


// function to initialize LEDs
void led_init(){
  P1DIR |= LEDS;
  led_switch = 1;
  switch_state_changed = 1; 
  led_update();
}


// function to update LED states
void led_update(){
  char flags;

   // if LED switch is on and switch state is 1
  if (led_switch && switch_state == 1){
    flags = greenValue[green_on] | redValue[red_on]; //first state for led state machine
    
    P1OUT &= (0xff^LEDS) | flags;
    P1OUT |= flags;
    led_switch = 0;
  }

  // if switch state changed and switch state is 2
  if (switch_state_changed && switch_state == 2){
    flags |= switch2_state ? LED_GREEN : 0; //green then when pressed switch to red
    flags |= switch2_state ? 0 : LED_RED;
    
    P1OUT &= (0xff^LEDS) | flags;
    P1OUT |= flags;
  }

    // if switch state changed and switch state is 3
  if (switch_state_changed && switch_state == 3){
    flags |= switch3_state ? 0 : LED_GREEN; //red and when pressed goes off

    P1OUT &= (0xff^LEDS) | flags;
    P1OUT |= flags;
  }
  // reset switch state change flag
  switch_state_changed = 0;
} 

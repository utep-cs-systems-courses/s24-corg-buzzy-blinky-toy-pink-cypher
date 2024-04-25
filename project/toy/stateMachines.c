#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

char toggle_red(){ // Toggles the state of the red LED
  static char current_state = 0;

  switch (current_state){
  case 0:
    red_on = 1;
    current_state = 1;
    break;
  case 1:
    red_on = 0;
    current_state = 0;
    break;
  }
  return 1;  // LED state always changes
}

char toggle_green(){ // Toggles the state of the green LED if red LED is on
  char state_changed = 0;
  if (red_on){
    green_on ^= 1;
    state_changed = 1;
  }
  return state_changed;
}

void led_state_advance(){
  char state_changed = 0;
  
  static enum {RED=0, GREEN=1} color = GREEN;
  switch (color){      // State machine for LED to blink back and forth
  case RED: state_changed = toggle_red(); color = GREEN; break;
  case GREEN: state_changed = toggle_green(); color = RED; break;
  }
  
  led_changed = state_changed;
  led_update();
}

void switch_state_advance(){
  switch (switch_state){
  case 1:
    buzzer_set_period(1300); // Sets buzzer frequency when a certain button is pressed
    break;
  case 2:
    buzzer_set_period(200);
    break;
  case 3:
    buzzer_set_period(700);
    break;
  case 4:
    buzzer_off();
    break;
  }
  led_update(); // After the state is set, update the LEDs accordingly
}

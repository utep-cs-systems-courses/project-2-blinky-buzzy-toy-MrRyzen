#include <msp430.h>
#include "stateMachines.h"
#include "switches.h"
#include "led.h"

char toggle_led;

void state_advance() {  
  if(switch_state_2 && switch_state_3) {
    state = 5;
  }
  else if(state == 0 && switch_state_1) {
    state = 1;
  }
  else if(state == 1 && switch_state_3) {
    state = 2;
  }
  else if(state == 2 && switch_state_1 && switch_state_3) {
    state = 3;
  }
  else if(state == 1 && switch_state_1 && switch_state_2 && switch_state_3 && switch_state_4) {
    state = 4;
  }
  else {
    //error buzz
    state = 0;
  }
  

  switch (state) {
  case 0:
    toggle_led = (toggle_led & LED_RED) ? LED_GREEN : LED_RED;
    break;
  case 1:
    toggle_led = LED_GREEN;
    break;
  default: break;
  }

  led_update();
}




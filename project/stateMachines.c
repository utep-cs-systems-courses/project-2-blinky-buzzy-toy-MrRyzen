#include <msp430.h>
#include "stateMachines.h"
#include "switches.h"
#include "led.h"

char toggle_led;

void state_advance() {  
  state = switch_state_1 + switch_state_2 + switch_state_3 + switch_state_4;

  switch (state) {
  case 0:
    toggle_led = (toggle_led & LED_RED) ? LED_GREEN : LED_RED;
    break;
  case 1:
    toggle_led = LED_GREEN;
    break;
  case 3:
    toggle_led = LED_RED;
    break;
  case 4:
    toggle_led = LED_GREEN | LED_GREEN;
    break;
  case 10:
    toggle_led = (toggle_led & LED_RED) ? LED_GREEN : LED_RED;
    break;
  default:
    //buzz
    toggle_led = (toggle_led & LED_RED) ? LED_GREEN : LED_RED;
    state = 0;
    break;
  }

  led_update();
}




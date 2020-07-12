#include <msp430.h>
#include "stateMachines.h"
#include "switches.h"
#include "led.h"

char toggle_led;

void state_advance() {  
  state = 0;
  
  switch (state) {
  case 0: toggle_led = (toggle_led & LED_RED) ? LED_GREEN : LED_RED;
    break;
  default: break;
  }

  led_update();
}




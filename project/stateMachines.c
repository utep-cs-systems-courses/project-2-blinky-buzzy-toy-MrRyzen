#include <msp430.h>
#include "stateMachines.h"
#include "switches.h"
#include "led.h"

unsigned char leds_changed;

void state_advance() {  
  state = 0;
  
  switch (state) {
  case 0: leds_changed = LED_GREEN;
    break;
  default: break;
  }

  led_update();
}




#include <msp430.h>
#include "stateMachines.h"
#include "switches.h"
#include "led.h"
#include "timerLib/libTimer.h"

char toggle_led = 0;

void state_advance() {  
  if(sw2_state_down && sw1_state_down) {
    state = 5;
  }
  else if(state == 0 && sw1_state_down) {
    state = 1;
  }
  else if(state == 1 && sw3_state_down && sw1_state_changed) {
    state = 2;
  }
  else if(state == 2 && sw4_state_down && sw3_state_changed && sw1_state_changed) {
    state = 3;
  }
  else if(state == 1 && sw1_state_down && sw2_state_down && sw3_state_down && sw4_state_down) {
    state = 4;
  }
  else {
    //error buzz
    sw1_state_changed = 0;
    sw2_state_changed = 0;
    sw3_state_changed = 0;
    sw4_state_changed = 0;
    state = 0;
  }

  switch (state) {
  case 1:
    toggle_led = LED_GREEN;
    break;
  case 2:
    toggle_led = LED_RED;
    break;
  case 3:
    toggle_led = LED_GREEN | LED_RED;
    //buzz
    break;
  case 4:
    //buzz song
    state = 0;
    enableWDTInterrupts();
  case 0:
    toggle_led = (toggle_led & LED_RED) ? LED_GREEN : LED_RED;
    break;
  default: break;
  }

  led_update();
}

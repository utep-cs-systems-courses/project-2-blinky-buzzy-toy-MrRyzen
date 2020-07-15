#include <msp430.h>
#include "stateMachines.h"
#include "switches.h"
#include "led.h"
#include "buzzer.h"
#include "timerLib/libTimer.h"

char toggle_led = 0;

void state_init() {
  state = 0;
  toggle_led = (toggle_led & LED_RED) ? LED_GREEN : LED_RED;
  led_update();
}

void state_advance() {  
  switch (state) {
  case 1:
    toggle_led = LED_GREEN;
    if(sw1_state_down && sw3_state_down) {
      state = 2;
      state_advance();
    }
    break;
  case 2:
    toggle_led = LED_RED;
    if(sw2_state_down && sw3_state_down) {
      state = 3;
      state_advance();
    }
    break;
  case 3:
    toggle_led = LED_GREEN | LED_RED;
    if(sw1_state_down && sw2_state_down && sw3_state_down) {
      state = 4;
      state_advance();
    }
    //buzz
    break;
  case 4:
    buzzer_set_period(D);
    state = 0;
    enableWDTInterrupts();
  case 0:
    if(sw1_state_down) {
      state = 1;
      state_advance();
    }
    toggle_led = (toggle_led & LED_RED) ? LED_GREEN : LED_RED;
    break;
  default: break;
  }

  led_update();
}

#include <msp430.h>
#include "stateMachines.h"
#include "switches.h"
#include "led.h"
#include "buzzer.h"
#include "timerLib/libTimer.h"

char toggle_led = 0;
static char dim = 0;

void state_init() {
  state = 0;
  toggle_led = (toggle_led & LED_RED) ? LED_GREEN : LED_RED;
  led_update();
}

void reset_states() {
  state = 0;
  toggle_led = 0;
  buzzer_set_period(0);
  led_update();
}

void state_advance() {
  if(sw4_state_down)
    reset_states();
  dim++;
  dim = (dim > 4) 0 : dim;

  switch (state) {
  case 1:
    toggle_led = LED_GREEN;
    if(sw1_state_down && sw3_state_down) {
      state = 2;
    }
    break;
  case 2:
    toggle_led = LED_RED;
    if(sw2_state_down && sw3_state_down) {
      state = 3;
    }
    break;
  case 3:
    if (dim == 0)
      toggle_led = LED_GREEN | LED_RED;
    else
      toggle_led = 0;
    
    if(sw1_state_down && sw2_state_down && sw3_state_down) {
      state = 4;
    }
    break;
  case 4:
    state = 0;
    play_song();
    break;
  case 0:
    if(sw1_state_down) {
      state = 1;
    }
    toggle_led = (toggle_led & LED_RED) ? LED_GREEN : LED_RED;
    break;
  default: break;
  }

  led_update();
}

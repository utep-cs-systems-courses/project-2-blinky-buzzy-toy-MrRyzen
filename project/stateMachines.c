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

void reset_states() {
  state = 0;
  toggle_led = 0;
  buzzer_set_period(0);
  led_update();
  state_advance();
}

void state_advance() {  
  switch (state) {
  case 1:
    if(sw4_state_down)
      reset_states();
    toggle_led = LED_GREEN;
    if(sw1_state_down && sw3_state_down) {
      state = 2;
      state_advance();
    }
    break;
  case 2:
    if(sw4_state_down)
      reset_states();
    toggle_led = LED_RED;
    if(sw2_state_down && sw3_state_down) {
      state = 3;
      state_advance();
    }
    break;
  case 3:
    if(sw4_state_down)
      reset_states();
    toggle_led = LED_GREEN | LED_RED;
    if(sw1_state_down && sw2_state_down && sw3_state_down) {
      state = 4;
      state_advance();
    }
    break;
  case 4:
    play_song();
    state = 0;
    state_advance();
  case 0:
    if(sw4_state_down)
      reset_states();
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

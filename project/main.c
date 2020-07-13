#include <msp430.h>
#include "timerLib/libTimer.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "stateMachines.h"

void main(void) {  
  configureClocks();

  switch_init();
  led_init();
  buzzer_init();

  state_advance();
  
  or_sr(0x18);  // CPU off, GIE on
} 

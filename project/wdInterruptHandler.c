#include <msp430.h>
#include "stateMachines.h"

unsigned char state;

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  if (++blink_count == 125) {
    if (state != 3)
      state_advance();    
    blink_count = 0;
  }
  if (state == 3)
    state_advance();
  
}

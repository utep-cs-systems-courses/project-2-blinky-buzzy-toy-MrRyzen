#include <msp430.h>
#include "stateMachines.h"

unsigned char state;

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  if (++blink_count == 2) {
    if(state == 0)
      state_advance();
    blink_count = 0;
  }
}

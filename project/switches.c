#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "stateMachines.h"

char sw1_state_down, sw2_state_down, sw3_state_down, sw4_state_down, sw1_state_changed, sw2_state_changed, sw3_state_changed, sw4_state_changed; /* effectively boolean */

static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
}

void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  sw1_state_down = (p2val & SW1) ? 0 : 1; /* 0 when SW1 is up */
  sw2_state_down = (p2val & SW2) ? 0 : 1; /* 0 when SW2 is up */
  sw3_state_down = (p2val & SW3) ? 0 : 1; /* 0 when SW3 is up */
  sw4_state_down = (p2val & SW4) ? 0 : 1; /* 0 when SW4 is up */

  if(switch_state_1 || switch_state_2 || switch_state_3 || switch_state_4) {
    sw1_state_changed = sw1_state_down;
    sw2_state_changed = sw2_state_down;
    sw3_state_changed = sw3_state_down;
    sw4_state_changed = sw4_state_down;
    state_advance();
  }
}

#include <msp430.h>
#include "led_control.h"

#define BUTTON1 BIT3		/* of p1 */

/* Switch on P1 (S2) */
__interrupt(PORT1_VECTOR) Port_1(){
  char p1val = P1IES = P1IN;
  
  green_led_state = (p1val & BUTTON1) ? 0 : 1; /* 0 when button is up */
  green_led_changed = 1;
  led_control();
}
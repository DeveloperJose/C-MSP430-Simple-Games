#include <msp430.h>
#include "led_control.h"

void red_machine() /* transition the red state machine */
{
	red_led_state ^= 1;
	red_led_changed = 1;
}

__interrupt(TIMER0_A0_VECTOR) TIMER_A0(){ /* Timer interrupt */
	red_count++;
	if(red_count >= 25){
		red_machine();
		red_count = 0;
	}
	led_control();
}
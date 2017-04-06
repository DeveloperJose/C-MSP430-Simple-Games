#include <msp430.h>

unsigned char leds_changed = 0;

/* zero for off, 1 for on */
unsigned char red_led_state = 0; 
unsigned char green_led_state = 0; 


void led_control(){		/* set leds */
  char ledFlags = 0;
  if (leds_changed) {
    if(green_led_state)
      ledFlags |= BIT6;		/* green led */
    
    if(red_led_state)
      ledFlags |= BIT0;		/* red led */
    
    P1OUT &= (0xff-(BIT6+BIT0)) | ledFlags; // clear bit for off leds
    P1OUT |= ledFlags;        // set bit for on leds
    leds_changed = 0;
  }
}


void red_machine()		/* transition the red state machine */
{
  red_led_state ^= 1;
  leds_changed = 1;
}

void green_machine()		/* transition green state machine */
{
  static int red_count = 0;
  leds_changed = 1;
  green_led_state = 1 - green_led_state;
  red_count = (red_count + 1) & 3;
  if (red_count == 0) {
    red_machine();		/* only transition red_machine on state zero */
  }
}

__interrupt(TIMER0_A0_VECTOR) TIMER_A0(){
  static int count_green = 0;	/* divide by 25 state machine */
  count_green++;
  if(count_green >= 25){
    green_machine();
    count_green = 0;
  }
  led_control();
}


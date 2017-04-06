#include <msp430.h>

unsigned char red_count = 0;

unsigned char red_led_changed = 0;
unsigned char green_led_changed = 0;

/* zero for off, 1 for on */
unsigned char red_led_state = 0; 
unsigned char green_led_state = 0; 


void led_control(){		/* set leds */
  char ledFlags = 0;
  if (red_led_changed || green_led_changed) {
    if(green_led_state)
      ledFlags |= BIT6;		/* green led */
    
    if(red_led_state)
      ledFlags |= BIT0;		/* red led */
    
    P1OUT &= (0xff-(BIT6+BIT0)) | ledFlags; // clear bit for off leds
    P1OUT |= ledFlags;        // set bit for on leds
    green_led_changed = red_led_changed = 0;
  }
}

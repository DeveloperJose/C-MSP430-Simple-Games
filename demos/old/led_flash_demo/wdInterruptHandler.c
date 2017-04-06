#include <msp430.h>
#include "buzzer.h"
#include "led.h"

void decisecond() 
{
  static char cnt = 0;		/* # deciseconds/frequecy change */
  if (++cnt > 2) {		
    buzzer_advance_frequency();
    cnt = 0;
  }
}

__interrupt(WDT_VECTOR) WDT(){	/* 62.5 interrupts/sec */
  static char second_count = 0, decisecond_count = 0;
  if (++second_count == 62) {
    led_toggle();
    second_count = 0;
  }
  if (++decisecond_count == 6) {
    buzzer_advance_frequency();
    decisecond_count = 0;
  }
  led_update();
}

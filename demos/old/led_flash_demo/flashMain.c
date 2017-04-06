#include <msp430.h>

// P1 connections:
//    P1.0 red led (1 = 0N)
//	P1.3 button (zero if down, needs resistor pull up)
//	P1.6 green led (1=ON)

void configure_clock(void) 		/* set master clock to 1MHz */
{ 
  BCSCTL1 = CALBC1_1MHZ;   // Set range 
  DCOCTL = CALDCO_1MHZ;	   
  BCSCTL2 &= ~(DIVS_3);    // SMCLK = DCO / 8 = 1MHz 
} 

void main(void) 
{  
  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable wd timer */
  led_init();
  or_sr(0x18);		/* CPU off, GIE on */
} 

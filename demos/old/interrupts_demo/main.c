#include <msp430.h>

#define P1SwMask BIT3

void configure_clock(void) 		/* set master clock to 1MHz */
{ 
  BCSCTL1 = CALBC1_1MHZ;   // Set range 
  DCOCTL = CALDCO_1MHZ;	   
  BCSCTL2 &= ~(DIVS_3);    // SMCLK = DCO / 8 = 1MHz 
} 

void main(void) 
{  
  WDTCTL = WDTPW + WDTHOLD;	// Stop watchdog timer
  configure_clock();			// set master clock to 1MHz
  CCTL0 = CCIE;		   	// Timer A interrupt enabled
				// Timer A control:
				//  Timer clock source 2: system clock
  TACTL = TASSEL_2 + MC_1;      //  Mode Control 1: continuously 0...CCR0
  CCR0 = 10000;		   	// Interrupt every 10,000 cycles (1MHz/10,000)

  P1DIR = BIT0 + BIT6;	   	// bits attached to leds are for output

  P1REN |= P1SwMask;  /* resistors for switch */
  P1IE = P1SwMask;  /* enable interrupts from switch */
  P1OUT |= P1SwMask; /* pull-ups for switch */
  
  or_sr(0x18);			// CPU off, GIE on
} 
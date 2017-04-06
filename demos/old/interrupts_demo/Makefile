# makfile configuration
COMMON_OBJECTS	= sr.o
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: interrupts.elf 

#additional rules for files
interrupts.elf: ${COMMON_OBJECTS} main.o timer_interrupt.o button_interrupt.o led_control.o
	${CC} -mmcu=${CPU} -o $@ $^

install: interrupts.elf
	mspdebug rf2500 "prog interrupts.elf"

clean:
	rm -f *.o *.elf

#project dependencies
main.o: main.c

timer_interrupt.o: timer_interrupt.c

button_interrupt.o: button_interrupt.c

led_control.o: led_control.c

sr.o: sr.s

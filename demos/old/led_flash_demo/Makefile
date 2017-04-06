# makfile configuration
COMMON_OBJECTS	= sr.o
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: flash.elf 

#additional rules for files
flash.elf: ${COMMON_OBJECTS} flashMain.o stateMachines.o
	${CC} -mmcu=${CPU} -o $@ $^

install: flash.elf
	mspdebug rf2500 "prog flash.elf"

clean:
	rm -f *.o *.elf

#project dependencies
flashMain.o: flashMain.c

stateMachines.o: stateMachines.c

sr.o: sr.s
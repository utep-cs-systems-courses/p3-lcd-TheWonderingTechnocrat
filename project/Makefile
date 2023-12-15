#makefile configuration
COMMON_OBJECTS  = main.o redcontrol-s.o Switch.o lcddraw.o lcdutils.o font-11x16.o font-5x7.o font-8x12.o
CPU		= msp430g2553
CFLAGS		= -mmcu=${CPU} -I../h -I./11-buzzer -I./h
LDFLAGS 	= -L/opt/ti/msp430_gcc/include

#switch the compiler
CC	= msp430-elf-gcc
AS 	= msp430-elf-as

all: main.elf

main.elf: ${COMMON_OBJECTS} ./11-buzzer/buzzer.o 
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ ../lib/libTimer.a

load: main.elf
	msp430loader.sh $^

clean: $^
	rm -f *.o *.elf



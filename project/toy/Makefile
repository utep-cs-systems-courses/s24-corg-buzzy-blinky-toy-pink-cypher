# makfile configuration
COMMON_OBJECTS  = main.o 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		    = -L/opt/ti/msp430_gcc/include 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: led.elf led-c.elf led-s.elf

#additional rules for files
led.elf: ${COMMON_OBJECTS} 
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ ../lib/libTimer.a

led-c.elf: ${COMMON_OBJECTS} ledControl-c.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ ../lib/libTimer.a

led-s.elf: ${COMMON_OBJECTS} ledControl-s.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ ../lib/libTimer.a

load: led.elf
	msp430loader.sh $^

load-c: led-c.elf
	msp430loader.sh $^

load-s: led-s.elf 
	msp430loader.sh $^

clean:
	rm -f *.o *.elf

main.o: led.h
ledControl-c.o: led.h
ledControl-s.o: led.h
wdInterruptHandler.o:  led.h
led-on-c.o: led.h ledControl_c.c

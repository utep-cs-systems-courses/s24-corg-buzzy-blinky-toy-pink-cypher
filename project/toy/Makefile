# Makefile configuration                                                                                                                                                                                    
COMMON_OBJECTS = main.o switches.o
CPU = msp430g2553
CFLAGS = -mmcu=${CPU} -I ../h -L/opt/ti/msp430_gcc/include
CC = msp430-elf-gcc
AS = msp430-elf-as

all: led.elf led-c.elf led-s.elf buzzer.elf

ledControl-c.o: led.h ledControl_c.c
	${CC} ${CFLAGS} -c -o $@ ledControl_c.c

led-on-c.o: led.h ledControl_c.c
	${CC} ${CFLAGS} -c -o $@ ledControl_c.c


led.elf: ${COMMON_OBJECTS} ledControl-c.o
	${CC} ${CFLAGS} -o $@ $^ ../lib/libTimer.a

led-c.elf: ${COMMON_OBJECTS} ledControl-c.o
	${CC} ${CFLAGS} -o $@ $^ ../lib/libTimer.a

led-s.elf: ${COMMON_OBJECTS} ledControl-s.o
	${CC} ${CFLAGS} -o $@ $^ ../lib/libTimer.a

buzzer.elf: ${COMMON_OBJECTS} buzzer.o buzzerMain.o
	${CC} ${CFLAGS} -o $@ $^ ../lib/libTimer.a

load: led.elf
	msp430loader.sh $^

load-c: led-c.elf
	msp430loader.sh $^

load-s: led-s.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf

main.o: led.h switches.h
switches.o: switches.h
ledControl-s.o: led.h
wdInterruptHandler.o: led.h
buzzer.o: buzzer.h
buzzerMain.o: buzzer.h

device = atmega644
programmer = usbtiny

install:
	avr-gcc -O -mmcu=${device} -o serial.o -c serial.c
	avr-gcc -O -mmcu=${device} -o uart.o -c uart.c
	avr-gcc -O -mmcu=${device} uart.o serial.o -o serial
	avr-objcopy -j .text -j .data -O ihex serial serial.hex
	avrdude -c ${programmer} -p atmega644 -U flash:w:serial.hex
	rm serial.hex serial.o serial uart.o


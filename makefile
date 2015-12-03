device = atmega644
programmer = usbtiny
F_CPU = 1000000

install:
	avr-gcc -O -DF_CPU=${F_CPU} -mmcu=${device} blink.c -o blink
	avr-objcopy -j .text -j .data -O ihex blink blink.hex
	avrdude -c ${programmer} -p atmega644 -U flash:w:blink.hex
	rm blink blink.hex


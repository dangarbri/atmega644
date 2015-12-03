all:
	avr-gcc -mmcu=atmega644 -c main.c -o main.o
	avr-gcc -mmcu=atmega644 -c ../WithStdio/uart.c -o uart.o
	avr-gcc -mmcu=atmega644 -c sdcard.c -o sdcard.o
	avr-gcc -mmcu=atmega644 -O uart.o main.o sdcard.o -o main
	rm main.o
	rm uart.o
	rm sdcard.o

install:
	avr-objcopy -j .text -j .data -O ihex main main.hex
	avrdude -c usbtiny -p atmega644 -U flash:w:main.hex


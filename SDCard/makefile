all:
	avr-gcc -mmcu=atmega644 -c main.c -o main.o
	avr-gcc -mmcu=atmega644 -c ../Serial/uart.c -o uart.o
	avr-gcc -mmcu=atmega644 -c sdcard.c -o sdcard.o
	avr-gcc -mmcu=atmega644 uart.o main.o sdcard.o -o main
	rm main.o
	rm uart.o
	rm sdcard.o

install:
	sudo ../avr -i main

all:
	avr-gcc -mmcu=atmega644 -O -c main.c
	avr-gcc -mmcu=atmega644 -O -c timer.c
	avr-gcc -mmcu=atmega644 -O -o timer.elf main.o timer.o
	avr-objcopy -j .text -j .data -O ihex timer.elf timer.hex
	sudo avrdude -c usbtiny -p m644 -U flash:w:timer.hex
	rm timer.elf timer.hex main.o timer.o

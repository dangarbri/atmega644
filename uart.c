#include "uart.h"
// set F_CPU if not set
#ifndef F_CPU
#define F_CPU 1000000
#endif

// set baud if not set
#ifndef BAUD
#define BAUD 4800
#endif
#define BAUDRATE ((F_CPU/(BAUD*16UL))-1)                        // Baud in bits per second
void uart_init(void) 
{
    // enable transmitter and receiver
    UCSR0B |= (1 << TXEN0)|(1<<RXEN0);
    // set 2 stop bits, 8 bit data
    UCSR0C = (1<<USBS0)|(3<<UCSZ00);
    // set baud
    UBRR0H = BAUDRATE >> 8; // Put high 8 bits in H register
    UBRR0L = BAUDRATE;        // Put low 8 bits in L register
    // setup printf
}

int uart_transmit (char data, FILE *stream)
{
    // if newline, also print carriage return
    if(data == '\n') uart_transmit('\r', stream);
    // wait for transmitter
    while(!(UCSR0A & (1 << UDRE0)));
    // send data
    UDR0 = data;
    return 0;
}

void backspace() {
    uart_transmit('\b', stdout);
    uart_transmit(' ', stdout);
    uart_transmit('\b', stdout);
}

int uart_receive(FILE *stream)
{
    // (UCSR0A & (1 << RXC0) equals 0 when there is no data
    // to be read, so busy wait for data to be read
    while ( !(UCSR0A & (1 << RXC0)));
    // echo input
    char in = UDR0; 
    uart_transmit(in, stream);
    // handle backspace
    if(in == 127) {
        backspace();
    }
    return in;
}

void print(char *format, ...) {
    byte len = strlen(format); // get string length
    char newStr[len+2]; // new string buffer with space for \n and \0
    strcpy(newStr, format); // copy old string into buffer
    strcat(newStr, "\n"); // add new line character (\0 added behind the scenes)

    // print
    va_list args;
    va_start(args, format);
    vprintf(newStr, args);
    va_end(args);
}

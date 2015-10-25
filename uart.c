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
}

void uart_transmit (unsigned char data)
{
    // if newline, also print carriage return
    if(data == '\n') uart_transmit('\r');
    // wait for transmitter
    while(!(UCSR0A & (1 << UDRE0)));
    // send data
    UDR0 = data;
}

void backspace() {
    uart_transmit(BACKSPACE_OUT); // move cursor back 1
    uart_transmit(' ');          // clear the typed char
    uart_transmit(BACKSPACE_OUT); // move cursor back again
}

char uart_receive_echo()
{
    char in = uart_receive(); // normal receive
    uart_transmit(in); // echo the input
    if(in == '\r') // if user hit enter, also add new line
        uart_transmit('\n');
    // handle backspace
    if(in == BACKSPACE_IN)  backspace(); 
    return in;
}

char uart_receive()
{
    // (UCSR0A & (1 << RXC0) equals 0 when there is no data
    while ( !(UCSR0A & (1 << RXC0)));
    char in = UDR0; 
    return in;
}

void print(char *output)
{
    char c; // char buffer
    while((c = *(output++)) != '\0') uart_transmit(c); // print until we hit the null terminator
}

void printLine(char *output)
{
    print(output); // print as normal
    print(NEWLINE); // add new line
}

void read(char* buffer)
{
    char c;
    char *tmp = buffer;
    while((c = uart_receive()) != '\r')
    {
        if(c == BACKSPACE_IN) // on backspace, move the pointer back 1 and keep reading
            tmp--;
        else
            *(tmp++) = c;
    }
}


void read_echo(char *buffer)
{
    char c;
    char *tmp = buffer;
    while((c = uart_receive_echo()) != '\r')
    {
        if(c == BACKSPACE_IN) // on backspace, move the pointer back 1 and keep reading
            tmp--;
        else
            *(tmp++) = c;
    }
}

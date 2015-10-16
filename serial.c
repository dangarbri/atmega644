#define F_CPU 1000000
#define BAUD 12                        // Baud in bits per second

#include <avr/io.h>

void uart_init(void) 
{
    UBRR0H = 0; // Put high 8 bits in H register
    UBRR0L = 0;        // Put low 8 bits in L register
    UCSR0B |= (1 << TXEN0)|(1<<RXEN0);
    UCSR0C = 0;
    UBRR0H = (BAUD >> 8); // Put high 8 bits in H register
    UBRR0L = BAUD;        // Put low 8 bits in L register
}


void uart_transmit (unsigned char data)
{
    while(!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}


unsigned char uart_receive()
{
    // (UCSR0A & (1 << RXC0) equals 0 when there is no data
    // to be read, so busy wait for data to be read
    while ( !(UCSR0A & (1 << RXC0)));
    return UDR0;
}

int main()
{
    uart_init(); 
    while(1)
    {
        uart_transmit(uart_receive());
    }
}

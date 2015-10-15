#define F_CPU 1000000
#define BAUD 9600                        // Baud in bits per second
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1) // Calculate relative to CPU freq.

#include <avr/io.h>
#include <util/setbaud.h>

void uart_init(void) 
{
    UBRR0H = (BAUDRATE >> 8); // Put high 8 bits in H register
    UBRR0L = BAUDRATE;        // Put low 8 bits in L register

    UCSR0B |= (1 << TXEN0)|(1<<RXEN0);
    UCSR0C |= (1<<UCSZ00)|(1<<UCSZ01); 
}

void uart_transmit (unsigned char data)
{
    while(!( UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}


unsigned char uart_receive()
{
    while (!(UCSR0A) & (1<<RXC0));
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

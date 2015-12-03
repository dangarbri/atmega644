#include <avr/io.h>
#include <util/delay.h>
int main()
{
    DDRB = 1;
    while(1)
    {
        PORTB ^= 1;
        _delay_ms(500);
    }
}

#define BAUD 4800

#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

int main()
{
    uart_init(); 
    char in[30]; // input buffer
    while(1)
    {
        uart_receive();
        print("this is a test\r\n");
        read_echo(in);
        print("you typed: ");
        printLine(in);
        _delay_ms(1000);
        print(UART_SET_COLOR(31, 42));
        /*
         *command("[2J");
         *command("[H");
         */
        print("Cleared Screen");
    }
}

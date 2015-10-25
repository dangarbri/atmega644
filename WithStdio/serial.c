#define F_CPU 1000000
#define BAUD 4800

#include <stdio.h>
#include <avr/io.h>
#include "uart.h"

int main()
{
    uart_init(); 
    char in[30]; // input buffer
    while(1)
    {
        // read a string (counts space as enter, cus c works that way)
        // hopefully we don't have to read multiple strings but if we do it'll take some googling
        // you can google how to use scanf
        scanf("%s", in);
         
        // echo what the user typed
        // this print function is equivalent to printf("stuff\n", args)
        // it's a shortcut so you don't have to add \n to the end of every printf
        print("\nyou typed %s", in);
        // this is equivalent to printf("\nyou typed %s\n", in);
    }
}

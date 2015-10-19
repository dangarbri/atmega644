#define F_CPU 1000000
#define BAUD 4800

#include <stdio.h>
#include <avr/io.h>
#include "uart.h"

int main()
{
    uart_init(); 
    stdin = stdout = &mystdio;
    char in[30];
    while(1)
    {
        scanf("%s", in);
        print("\nyou typed %s", in);
    }
}

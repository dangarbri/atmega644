#ifndef __UART_H__
#define __UART_H__

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <avr/io.h>
typedef unsigned char byte;

void uart_init(void);
int uart_transmit(char data, FILE *stream);
int uart_receive(FILE *stream);
void print(char*, ...);
static FILE mystdio = FDEV_SETUP_STREAM(uart_transmit, uart_receive, _FDEV_SETUP_RW);
#endif

#ifndef __UART_H__
#define __UART_H__

#include <stdarg.h>
#include <string.h>
#include <avr/io.h>
typedef unsigned char byte;

void uart_init(void);
void uart_transmit(unsigned char t);
char uart_receive();
char uart_receive_echo();
void print(char *);
void printLine(char *);
void printNumber(unsigned int);
void read(char *);
void read_echo(char *);

#define BACKSPACE_OUT '\b'
#define BACKSPACE_IN 127
#define NEWLINE "\r\n"

#endif

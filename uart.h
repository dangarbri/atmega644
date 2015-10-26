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

// UART Commands
#define UART_CLEAR_SCREEN "\x1B[2J" // \x1B is the code for ESC which must precede every command
#define UART_CURSOR_HOME "\x1B[H"
#define UART_SET_CURSOR(line, col) "\x1B[" #line ";" #col "H"
#define UART_SET_COLOR(foreground, background) "\x1B[" #foreground ";" #background "m"
#define UART_F_BLACK 30
#define UART_F_RED 31
#define UART_F_GREEN 32
#define UART_F_YELLOW 33
#define UART_F_BLUE 34
#define UART_F_MAGENTA 35
#define UART_F_CYAN 36
#define UART_F_WHITE 37
#define UART_B_BLACK 40
#define UART_B_RED 41
#define UART_B_GREEN 42
#define UART_B_YELLOW 43
#define UART_B_BLUE 44
#define UART_B_MAGENTA 45
#define UART_B_CYAN 46
#define UART_B_WHITE 47

#endif

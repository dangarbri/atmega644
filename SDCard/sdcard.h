#ifndef __SD_CARD_H_
#define  __SD_CARD_H_
#include "../WithStdio/uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define SS 4
#define MOSI 5
#define SCK 7

int SD_init();
unsigned char spi_rxtx(unsigned char data);
void spi_init();
void send_command(char*, unsigned char cmd, unsigned char byte1, unsigned char byte2, unsigned char byte3, unsigned char byte4, unsigned char crc);
void send_and_receive(char*, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
unsigned char receive_data(unsigned char);
void skip_bytes(int);

#endif

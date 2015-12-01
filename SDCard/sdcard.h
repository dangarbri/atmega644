#ifndef __SD_CARD_H_
#define  __SD_CARD_H_
#include "../Serial/uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define GO_IDLE_STATE() spi_rxtx(0x40);spi_rxtx(0x00);spi_rxtx(0x00);spi_rxtx(0x00);spi_rxtx(0x00);spi_rxtx(0x95);spi_rxtx(0xFF);
#define SEND_CMD8() spi_rxtx(0x48);spi_rxtx(0x00);spi_rxtx(0x00);spi_rxtx(0x01);spi_rxtx(0x55);spi_rxtx(0x87);spi_rxtx(0xFF);

int SD_init();
unsigned char spi_rxtx(unsigned char data);
void spi_init();
unsigned char send_command(unsigned char cmd, unsigned char byte1, unsigned char byte2, unsigned char byte3, unsigned char byte4, unsigned crc);

#endif

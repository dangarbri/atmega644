#include "sdcard.h" 

void spi_init()
{
    DDRB = _BV(4)|_BV(5)|_BV(7); // set mosi and sck as output pins
    SPCR = _BV(SPE)|_BV(MSTR)|_BV(SPR0); // enables spi, set master, FCPU 1/16
    sei();
}

int SD_init()
{
    print("Connecting to SD Card\n");
    unsigned char in;
    print("Syncing clocks\n");
    PORTB |= _BV(4);
    int i;
    for(i = 0; i < 12; i++) {
        in = spi_rxtx(0xFF);
    }
    PORTB ^= _BV(4);
    do {
        printLine("Sending go_idle_state command");
        in = send_command(0, 0, 0, 0, 0, 0x95);
    } while(in != 0x01);
    printLine("Sending CMD8");
    while(1) {
    in = send_command(8, 0, 0, 0, 0, 0x87);
    printNumber(in);
    printNumber(spi_rxtx(0xFF));
    printNumber(spi_rxtx(0xFF));
    printNumber(spi_rxtx(0xFF));
    printNumber(spi_rxtx(0xFF));
    printNumber(spi_rxtx(0xFF));
    printNumber(spi_rxtx(0xFF));
    uart_receive();
    }
    printLine("Card ready");
    return 1;
}

unsigned char send_command(unsigned char cmd, unsigned char byte1, unsigned char byte2, unsigned char byte3, unsigned char byte4, unsigned crc) {
    unsigned char command = cmd | _BV(6);
    printNumber(command);
    spi_rxtx(command);
    spi_rxtx(byte1);
    spi_rxtx(byte2);
    spi_rxtx(byte3);
    spi_rxtx(byte4);
    spi_rxtx(crc);
    spi_rxtx(0xFF);
    return spi_rxtx(0xFF);
}

unsigned char spi_rxtx(unsigned char data)
{
    SPDR = data;
    unsigned char in = 0;
    print("Sending ");
    printNumber(data);
    while(!(SPSR & (1<< SPIF)));
    in = SPDR;
    print("Received: ");
    printNumber(in);
    return in;
}

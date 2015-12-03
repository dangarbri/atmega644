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
    unsigned char success;
    print("Syncing clocks\n");
    PORTB |= _BV(4);
    int i;
    for(i = 0; i < 12; i++) {
        spi_rxtx(0xFF);
    }
    PORTB ^= _BV(4);
    // go idle state
    while(1) {
        puts("Go idle state");
        send_command(0, 0, 0, 0, 0, 0x95);
        success = receive_data(0x01);
        if(success)
            break;
    }
    // command 8
    while(1) {
        puts("Cmd 8");
        send_command(8, 0, 0, 1, 0xAA, 0x87);
        success = receive_data(0x01);
        if(success)
            break;
    }
    
    
    // command 41
    while(1) {
        // command 55
        print("Cmd 55");
        send_command(55, 0, 0, 0, 0, 0x01);
        spi_rxtx(0xFF);
        spi_rxtx(0xFF);
        spi_rxtx(0xFF);
        spi_rxtx(0xFF);

        print("Cmd 41");
        send_command(41, 0x40, 0, 0, 0, 0x01);
        success = receive_data(0);
        if(success)
            break;
    }
    // command 58
    while(1) {
        puts("Command 58");
        send_command(58, 0, 0, 0, 0, 0x01);
        success = receive_data(0x01);
        if(success)
            break;
    }
    print("Card ready");
    return 1;
}

void send_command(unsigned char cmd, unsigned char byte1, unsigned char byte2, unsigned char byte3, unsigned char byte4, unsigned crc) {
    unsigned char command = cmd | 0x40;
    printf("Sending %x %x %x %x %x %x\n", command, byte1, byte2, byte3, byte4, crc);
    spi_rxtx(command);
    spi_rxtx(byte1);
    spi_rxtx(byte2);
    spi_rxtx(byte3);
    spi_rxtx(byte4);
    spi_rxtx(crc);
}

unsigned char receive_data(unsigned char want) {
    unsigned char in1, in2, in3, in4, in5, in6;
    in1 = spi_rxtx(0xFF);
    in2 = spi_rxtx(0xFF);
    in3 = spi_rxtx(0xFF);
    in4 = spi_rxtx(0xFF);
    in5 = spi_rxtx(0xFF);
    in6 = spi_rxtx(0xFF);
    printf("received %x %x %x %x %x %x\n", in1, in2, in3, in4, in5, in6);
    if(in1 == want || in2 == want || in3 == want || in4 == want || in5 == want || in6 == want)
        return 1;
    return 0;

}

unsigned char spi_rxtx(unsigned char data)
{
    SPDR = data;
    unsigned char in = 0;
    while(!(SPSR & (1<< SPIF)));
    in = SPDR;
    return in;
}

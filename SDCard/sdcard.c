#include "sdcard.h" 

void spi_init()
{
    DDRB = _BV(SS)|_BV(MOSI)|_BV(SCK); // set mosi and sck as output pins
    SPCR = _BV(SPE)|_BV(MSTR)|_BV(SPR0); // enables spi, set master, FCPU 1/16
    sei();
}

int SD_init()
{
    unsigned char success;
    puts("Connecting to SD Card");
    puts("Syncing clocks");
    PORTB |= _BV(SS);
    int i;
    for(i = 0; i < 12; i++) { spi_rxtx(0xFF); }
    PORTB ^= _BV(SS);

    // go idle state
    send_and_receive("Sending CMD0", 0, 0, 0, 0, 0, 0x95, 0x01);
    // command 8
    send_and_receive("Sending CMD8", 8, 0, 0, 1, 0xAA, 0x87, 0x01);

    while(1) {
        // command 55
        send_command("Sending CMD55", 55, 0, 0, 0, 0, 0x01);
        skip_bytes(4);

        send_command("Sending CMD41", 41, 0x40, 0, 0, 0, 0x01);
        success = receive_data(0);
        if(success)
            break;
    }
    // command 58
    send_and_receive("Sending CMD58", 58, 0, 0, 0, 0, 0x01, 0x01);
    print("Card ready");
   return 1;
}

void skip_bytes(int j) {
    int i;
    for(i = 0; i < j; i++) {
        spi_rxtx(0xFF);
    }
}

// Sends a command with given arguments, checks for the expected response and repeats
// until the expected response is reseased
void send_and_receive(char *descr, unsigned char cmd, unsigned char byte1, unsigned char byte2, unsigned char byte3, unsigned char byte4, unsigned char crc, unsigned char expected) {
    while(1) {
        send_command(descr, cmd, byte1, byte2, byte3, byte4, crc);
        unsigned char success = receive_data(expected);
        if(success)
            break;
    }
}

// Sends a command to the sd card with supplied arguments
void send_command(char *descr, unsigned char cmd, unsigned char byte1, unsigned char byte2, unsigned char byte3, unsigned char byte4, unsigned char crc) {
    printf("%s\n", descr);
    unsigned char command = cmd | 0x40;
    printf("Sending %x %x %x %x %x %x\n", command, byte1, byte2, byte3, byte4, crc);
    spi_rxtx(command);
    spi_rxtx(byte1);
    spi_rxtx(byte2);
    spi_rxtx(byte3);
    spi_rxtx(byte4);
    spi_rxtx(crc);
}

// receive 6 bytes and check if any match "want", the expected response
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

// Send and receive a byte
unsigned char spi_rxtx(unsigned char data)
{
    SPDR = data;
    unsigned char in = 0;
    while(!(SPSR & (1<< SPIF)));
    in = SPDR;
    return in;
}

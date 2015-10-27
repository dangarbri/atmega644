#define BAUD 4800

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "uart.h"
#define true 1
#define false 0
#define poundLine "###########################################################################"

short gameStarted = false;
unsigned int lowerBound, upperBound;

void intro()
{
    uart_receive();
    printLine(poundLine);
    printLine("Game Objective: ");
    printLine("Think of any number less than or equal to 65,000.");
    printLine("The computer will then guess a number.");
    printLine("You can respond with the following: ");
    printLine("h : Your number is higher than what the computer guessed.");
    printLine("l : Your number is lower than what the computer guessed. ");
    printLine("y : The computer guessed the correct number. ");
    printLine("reset : Reset the game. ");
    printLine(poundLine);
    gameStarted = true;
    lowerBound = 0;
    upperBound = 65000;
}

unsigned int randInt(unsigned int min, unsigned int max) {
    unsigned int n =  min + rand() / (RAND_MAX / (max - min + 1) + 1);
    while(n <= lowerBound || n >= upperBound)
        n = randInt(min, max);
    return n;
}

void guess(unsigned int num)
{
    print("Is your number ");
    printNumber(num);
}

int isReset(char *in)
{
    if(     in[0] == 'r' &&
            in[1] == 'e' &&
            in[2] == 's' &&
            in[3] == 'e' &&
            in[4] == 't' )
        return 1;
    return 0;
}

int main()
{
    uart_init();
    char in[40]; // input buffer
    while(1)
    {
        if(!gameStarted) 
            intro();
        unsigned int theGuess = randInt(lowerBound, upperBound);
        guess(theGuess);
        read_echo(in);
        if(in[0] == 'h')
            lowerBound = theGuess;
        else if(in[0] == 'l')
            upperBound = theGuess;
        else if(in[0] == 'y')
        {
            printLine("I win");
            gameStarted = 0;
            printLine("press any key to continue...");
            uart_receive();
        }
        else if(isReset(in))
        {
            gameStarted = false;
            printLine("press any key to continue...");
            uart_receive();
        }
   }
}

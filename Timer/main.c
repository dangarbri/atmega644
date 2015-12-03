#include <avr/io.h>
#include <avr/interrupt.h>

#include "timer.h"  


void toggle_pin()
{
    PORTC ^= 1;
}
int main(void)
{
    // connect led to pin PC0
    DDRC |= (1 << 0);
    // initialize timer
    timer0_init();
    TASK task;
    create_task(&task, toggle_pin, 5000, 'y');
  
    // loop forever
    while(1)
    {
        // do nothing
        // comparison is done in the ISR itself
    }
}

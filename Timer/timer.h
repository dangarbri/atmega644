#ifndef __TIMER_H__
#define __TIMER_H__
#include <avr/io.h>
#include <avr/interrupt.h>

// The maximum number of tasks that the program can hold
#ifndef MAX_TASK_COUNT
#define MAX_TASK_COUNT 5
#endif


typedef struct {
    unsigned long long created;  // Creation time (in ticks)
    unsigned int interval;       // How often task is executed (in ms)
    unsigned char repeat;        // Repeat every interval?
    unsigned char ran;           // Set to 1 when the task has run
    void (*task)();              // Function to perform task
} TASK;

volatile TASK TASKS[MAX_TASK_COUNT];

extern volatile uint16_t tot_overflow;

void timer0_init(void);
void create_task(TASK*, void (*)(), unsigned int, unsigned char);
unsigned long long get_clock_ticks();

#endif

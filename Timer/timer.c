#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

// global variable to count the number of overflows
volatile uint16_t tot_overflow = 0;

// initialize the task array.
void task_init()
{
    int i;
    for(i = 0; i < MAX_TASK_COUNT; i++)
    {
        TASK tmp;
        tmp.repeat = 'z';  // set all tasks to z for not set. (n is reserved for no repeat)
        tmp.ran = 0;
        TASKS[i] = tmp;
    }
}

int get_available_task_slot()
{
    int i;
    for(i = 0; i < MAX_TASK_COUNT; i++)
    {
        TASK tmp = TASKS[i];
        if(tmp.repeat == 'z' || (tmp.repeat == 'n' && tmp.ran)) // task is new, use it or it shouldn't repeat and it has run
            return i;
    }
    return 0; // this shouldn't happen, if it does, chances are MAX_TASK_COUNT should be higher.
}

// check and run all tasks that should run
void run_tasks()
{
    int i;
    for(i = 0; i < MAX_TASK_COUNT; i++)
    {
        volatile TASK *tmp = &TASKS[i];
        // check repeat and if the task has already run. Run it if it should run
        if((tmp->repeat == 'n' && tmp->ran == 0) || tmp->repeat == 'y') 
        {
            // check clock ticks to see if it is time to run
            if(get_clock_ticks() > (tmp->created + tmp->interval))
            {
                tmp->task(); // run task
                tmp->ran = 1; // mark task as ran
                if(tmp->repeat == 'y')
                    tmp->created = get_clock_ticks(); // if it's a repeat task, set a new created time
            }
        }
    }
}

// Create a task and add it to the task list
  
// initialize timer, interrupt and variable
void timer0_init()
{
    task_init();
    // set up timer with prescaler = 256
    TCCR0B |= (1 << CS02);
    // initialize counter
    TCNT0 = 0;
    // enable overflow interrupt
    TIMSK0 |= (1 << TOIE0);
    // enable global interrupts
    sei();
    // initialize overflow counter variable
    tot_overflow = 0;
}

void create_task(TASK* task, void (*func)(), unsigned int interval, unsigned char repeat)
{
    task->created = get_clock_ticks();
    task->repeat = repeat;
    task->interval = interval;
    task->task = func;
    TASKS[get_available_task_slot()] = *task;
}

unsigned long long get_clock_ticks()
{
    unsigned long long i = tot_overflow * 256;
    i += TCNT0;
    return i;
}

// TIMER0 overflow interrupt service routine
// called whenever TCNT0 overflows
ISR(TIMER0_OVF_vect)
{
    // keep a track of number of overflows
    tot_overflow++;
    run_tasks();
}


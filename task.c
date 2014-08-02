#include <avr/io.h>
#include "task.h"
#include "timing.h"

uint8_t num_tasks = 0;

void task_manager()
{
    uint16_t last_tick = 0;

    while (1) {
	while (ticks == last_tick);
    
	for (uint8_t i = 0; i < num_tasks; i++) {
	    Task* task = &tasks[i];
	    task->counter += ticks - last_tick; 
	    if (task->counter >= task->period) {
		task->counter = 0;
		if (task->enable) 
		    task->handler();
	    }
	}

	last_tick = ticks;
    }
}

void task_add(void (*handler)(), uint16_t period, uint8_t delay)
{
    tasks[num_tasks].handler = handler;
    tasks[num_tasks].period = period;
    tasks[num_tasks].counter = delay;
    tasks[num_tasks].enable = 1;
    num_tasks++;
}
#ifndef M_TIMER_H
#define M_TIMER_H

#include <time.h>

struct Timer {
    clock_t start_t;
    clock_t end_t;
};

typedef struct Timer Timer;

// Allocates memory for a timer
// Sets start time
Timer *getTimer();

void setStartTime(Timer *timer);
void setEndTime(Timer *timer);

// Returns duration in seconds
double getDuration(const Timer *timer);

#endif
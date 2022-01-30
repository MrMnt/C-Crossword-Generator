#include "m_timer.h"
#include <stdlib.h>

Timer *getTimer(){
    Timer *timer = malloc(sizeof(Timer));
    setStartTime(timer);
    return timer;
}

void setStartTime(Timer *timer){
    timer->start_t = clock();
}

void setEndTime(Timer *timer){
    timer->end_t = clock();
}

double getDuration(const Timer *timer){
    return (double) (timer->end_t - timer->start_t) / CLOCKS_PER_SEC;
}
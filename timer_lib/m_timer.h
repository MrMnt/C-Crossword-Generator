/** @file m_timer.h */

#ifndef M_TIMER_H
#define M_TIMER_H

#include <time.h>

/** @struct Timer
 *  Times how long something takes.
 * Stores start and end values to calculate how much time has passed
 */
typedef struct {
    clock_t start_t; ///< Start time
    clock_t end_t;  ///< End time
} Timer;

/** Returns a pointer to newly allocated Timer
 * 
 * @returns Pointer to the newly allocated Timer
 * 
 * @note Automatically sets start time
 * 
 * @see setStartTime()
 * 
 */
Timer *getTimer();


/** Sets Timer::start_t for given @p timer
 * 
 * @param timer - pointer to the timer which @p start_t value will be set
 * 
 */
void setStartTime(Timer *timer);


/** Sets Timer::end_t for given @p timer
 * 
 * @param timer - pointer to the timer which @p end_t value will be set
 * 
 */
void setEndTime(Timer *timer);


/** Returns duration in seconds
 *  
 * @param timer - pointer to the timer which duration will be calculated
 * 
 * @returns Returns duration in seconds
 * 
 */
double getDuration(const Timer *timer);

#endif
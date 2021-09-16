/*
 * us_delay_timer.h
 *
 *  Created on: 25 Aug 2021
 *      Author: ihambleton
 */

#ifndef US_DELAY_TIMER_H_
#define US_DELAY_TIMER_H_

#ifdef  __cplusplus
extern "C" {
#endif

void us_delay_init(void);

void us_delay_timer(uint16_t usDelay);


#ifdef  __cplusplus
}
#endif


#endif /* US_DELAY_TIMER_H_ */

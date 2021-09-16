/*
 * us_delay_timer.c
 *
 *  Created on: 25 Aug 2021
 *      Author: ihambleton
 */

#include <stdint.h>
#include  <common/include/lib_def.h>
#include  <cpu/include/cpu.h>

#include "em_cmu.h"
#include "em_timer.h"
#include "NGSA_task.h"

static TIMER_Init_TypeDef timerInit = TIMER_INIT_DEFAULT;
static CPU_INT32U max_time_us = 0;
static CPU_INT32U max_timer_count = 0;
static CPU_INT32U freq = 0;


void us_delay_init(void)
{
  CMU_ClockEnable(cmuClock_TIMER4, true);

  timerInit.enable = false;
  timerInit.prescale = timerPrescale1;
  timerInit.clkSel = timerClkSelHFPerClk;
  timerInit.mode = timerModeUp;
  timerInit.oneShot = true;

  TIMER_Init(TIMER4, &timerInit);

  freq = CMU_ClockFreqGet(cmuClock_TIMER4);

  max_timer_count = TIMER_MaxCount(TIMER4);

  max_time_us = ((CPU_INT64U)max_timer_count * DEF_TIME_NBR_uS_PER_SEC) / ((freq / (1u << timerPrescale1)));

  NVIC_DisableIRQ(TIMER4_IRQn);   // Don't want actual interrupt (poll status instead)
}

/***************************************************************************//**
 * @brief Short delay timer (blocking) for the specified number of microseconds
 *
 * @note If required delay is more than 1000us, why not use __delay_ms(n)
 *       Delay is approximately 7us longer than expected.
 *       Assumes calling task is highest priority (to prevent preemption)
 *
 * @param[in] the number of microseconds to block (max. 1680)
 *
 ******************************************************************************/
void us_delay_timer(uint16_t usDelay)
{
  volatile CPU_INT32U top = 0;

//  DebugPin_SetHigh();  // Got sample TODO: remove debug

  // Determine counter Top required for desired delay.
  if (usDelay > max_time_us)
  {
      top = max_timer_count;
  }
  else
  {
      top = ((CPU_INT64U)(freq / (1u << (CPU_INT32U)timerInit.prescale)) * usDelay) / DEF_TIME_NBR_uS_PER_SEC;
      while ((top > max_timer_count) && (timerInit.prescale != (TIMER_Prescale_TypeDef)timerPrescale1024))
      {
        timerInit.prescale += (TIMER_Prescale_TypeDef)timerPrescale2;
        top = ((CPU_INT64U)(freq / (1u << (CPU_INT32U)timerInit.prescale)) * usDelay) / DEF_TIME_NBR_uS_PER_SEC;
      }
  }
  TIMER_TopSet(TIMER4, top);
  TIMER_IntClear(TIMER4, TIMER_IEN_OF);

  TIMER_IntEnable(TIMER4, TIMER_IEN_OF); // NVIC remains disabled

  TIMER_Enable(TIMER4, true);

//  CORE_ENTER_ATOMIC();

  while ( (TIMER_IntGet(TIMER4) & TIMER_IF_OF ) == 0) // Poll status
  {
    // Loop
  }
//  CORE_EXIT_ATOMIC();

  TIMER_IntDisable(TIMER4, TIMER_IEN_OF);
  TIMER_IntClear(TIMER4, TIMER_IF_OF);

//  DebugPin_SetLow();  // Got sample TODO: remove debug
}




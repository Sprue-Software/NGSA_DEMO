/*
 * buzzer.c
 *
 *  Created on: 17 Sep 2021
 *      Author: ihambleton
 */

#include "em_cmu.h"
#include "em_timer.h"
#include "sl_emlib_gpio_init_Enable_PIN_config.h"
#include "sl_power_manager.h"


#define DUTY_CYCLE_STEPS  0.5

static uint32_t topValue = 0;
static volatile float dutyCycle = 0;

static TIMER_Init_TypeDef timerInit = TIMER_INIT_DEFAULT;

// Configure TIMER0 Compare/Capture for output compare
static TIMER_InitCC_TypeDef timerCCInit = TIMER_INITCC_DEFAULT;


void TIMER0_IRQHandler(void)
{
  static uint8_t freqCounter = 2u;

  freqCounter--;
  if (freqCounter <= 0u)
  {
    freqCounter = 2u; // Reset the counter
    GPIO_PinOutToggle(SL_EMLIB_GPIO_INIT_ENABLE_PIN_PORT, SL_EMLIB_GPIO_INIT_ENABLE_PIN_PIN); // Toggle the buzzer drive
  }

  TIMER_IntClear(TIMER0, TIMER_IF_OF); /*Clear the interrupt*/
}

void buzzer_init(uint32_t pwmFreq)
{
  uint32_t timerFreq = 0;

  timerInit.prescale = timerPrescale1;
  timerInit.enable = false;
  timerCCInit.mode = timerCCModeCompare;
  timerCCInit.cofoa = timerOutputActionToggle;

  // configure, but do not start timer
  TIMER_Init(TIMER0, &timerInit);

  // Route Timer0 CC0 output to PA5
  GPIO->TIMERROUTE[0].ROUTEEN  = GPIO_TIMER_ROUTEEN_CC0PEN;
  GPIO->TIMERROUTE[0].CC0ROUTE = (SL_EMLIB_GPIO_INIT_ENABLE_PIN_PORT << _GPIO_TIMER_CC0ROUTE_PORT_SHIFT) |
                                 (SL_EMLIB_GPIO_INIT_ENABLE_PIN_PIN << _GPIO_TIMER_CC0ROUTE_PIN_SHIFT);

  TIMER_InitCC(TIMER0, 0, &timerCCInit);

  // Set Top value
  // Note each overflow event constitutes 1/2 the signal period
  timerFreq = CMU_ClockFreqGet(cmuClock_TIMER0)/(timerInit.prescale + 1);
  int topValue = timerFreq / (2*pwmFreq) - 1;
  TIMER_TopSet (TIMER0, topValue);

  SPI_Write(0x02, 0x02);  // Reg 1 - High Boost Enable
  SPI_Write(0x0A, 0x14);  // Reg 5 - High Boost 11.5v
  SPI_Write(0x10, 0x09);  // Reg 8 - FEED 2/3 pin Enabled HB/HS, Horn Enable selection -> Enable Pin
  SPI_Write(0x06, 0x01);  // Reg 3 - Horn Enable

  sl_power_manager_add_em_requirement(SL_POWER_MANAGER_EM1);

  // Start the timer
  TIMER_Enable(TIMER0, true);
}

void buzzer_stop(void)
{
  TIMER_Enable(TIMER0, false);
  TIMER_Reset(TIMER0);

  GPIO->TIMERROUTE[0].ROUTEEN  &= (~GPIO_TIMER_ROUTEEN_CC0PEN);

  sl_power_manager_remove_em_requirement(SL_POWER_MANAGER_EM1);
}

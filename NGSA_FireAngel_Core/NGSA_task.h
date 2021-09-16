/***************************************************************************//**
 * @file
 * @brief NGSA Thread
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef NGSA_task_H
#define NGSA_task_H
#include "os.h"
/***************************************************************************//**
 * Initialize  NGSA Thread
 ******************************************************************************/
void NGSA_SYS_INIT(void);
extern uint32_t read_val(void);
extern void ADC_init(void);
extern uint32_t ADC_wait_for_val(void);

void init_AEF(void);
extern void Stop_ADC(void);
extern void __delay_ms(uint16_t time_ms_val);
extern void SPI_Write(uint8_t add , uint8_t data);
extern void Enable_SetHigh(void);
extern void Enable_SetLow(void);
extern void COpolarization_SetHigh(void);
extern void COpolarization_SetLow(void);
extern void DebugPin_SetHigh(void);
extern void DebugPin_SetLow(void);

/* ************* AFE***********************************************************/
#define HEARTBEAT_ON     0U
#define SMOKE_ON         0U
#define CO_SENSING_ON    0u
#define CO_TEST_ON       1u
#define CO_AMP_ALWAYS_ON 0u
#undef LED_BLINK
//#define LED_BLINK 0
#endif  // BLINK_H

/***************************************************************************//**
 * @file main_single_interrupt.c
 * @brief Use the IADC to take repeated nonblocking measurements on single
 * input
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 *******************************************************************************
 * # Evaluation Quality
 * This code has been minimally tested to ensure that it builds and is suitable 
 * as a demonstration for evaluation purposes only. This code will be maintained
 * at the sole discretion of Silicon Labs.
 ******************************************************************************/


#include "em_device.h"
#include "em_chip.h"
#include "em_core.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_iadc.h"
#include "em_gpio.h"
#include "sl_power_manager.h"

#include "os.h"
#include "events.h"
#include "NGSA_task.h" // TODO: remove debug

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

// Set CLK_ADC to 10MHz
//#define CLK_SRC_ADC_FREQ          5000000 // CLK_SRC_ADC
//#define CLK_ADC_FREQ              10000 // CLK_ADC - 10MHz max in normal mode
/* Nishi */
//Default oversampling (OSR) is 2x, and Conversion Time = ((4 * OSR) + 2) / fCLK_ADC
//So the conversation time is
//((4 * 2)+2)/10000 = 0.001s  (1/0.001)= 1ksps ( 1k sample per second)

/* Kept default*/

#define CLK_SRC_ADC_FREQ          20000000 // CLK_SRC_ADC
#define CLK_ADC_FREQ              10000000 // CLK_ADC - 10MHz max in normal mode

/*
 * Specify the IADC input using the IADC_PosInput_t typedef.  This
 * must be paired with a corresponding macro definition that allocates
 * the corresponding ABUS to the IADC.  These are...
 *
 * GPIO->ABUSALLOC |= GPIO_ABUSALLOC_AEVEN0_ADC0
 * GPIO->ABUSALLOC |= GPIO_ABUSALLOC_AODD0_ADC0
 * GPIO->BBUSALLOC |= GPIO_BBUSALLOC_BEVEN0_ADC0
 * GPIO->BBUSALLOC |= GPIO_BBUSALLOC_BODD0_ADC0
 * GPIO->CDBUSALLOC |= GPIO_CDBUSALLOC_CDEVEN0_ADC0
 * GPIO->CDBUSALLOC |= GPIO_CDBUSALLOC_CDODD0_ADC0
 *
 * ...for port A, port B, and port C/D pins, even and odd, respectively.
 */
#define IADC_INPUT_0_PORT_PIN     iadcPosInputPortCPin5;

#define IADC_INPUT_0_BUS          CDBUSALLOC
#define IADC_INPUT_0_BUSALLOC     GPIO_CDBUSALLOC_CDODD0_ADC0

/* This example enters EM2 in the infinite while loop; Setting this define to 1
 * enables debug connectivity in the EMU_CTRL register, which will consume about
 * 0.5uA additional supply current */
#define EM2DEBUG                  1

/*******************************************************************************
 ***************************   GLOBAL VARIABLES   ******************************
 ******************************************************************************/

// Stores latest IADC sample and conversion to Volts
static volatile IADC_Result_t sample;
static volatile double singleResult;    // Volts

/**************************************************************************//**
 * @brief  IADC Initializer
 *****************************************************************************/
void initIADC (void)
{
  // Declare init structs
   IADC_Init_t init = IADC_INIT_DEFAULT;
   IADC_AllConfigs_t initAllConfigs = IADC_ALLCONFIGS_DEFAULT;
   IADC_InitSingle_t initSingle = IADC_INITSINGLE_DEFAULT;
   IADC_SingleInput_t initSingleInput = IADC_SINGLEINPUT_DEFAULT;


   /* Note: For EFR32xG21 radio devices, library function calls to
    * CMU_ClockEnable() have no effect as oscillators are automatically turned
    * on/off based on demand from the peripherals; CMU_ClockEnable() is a dummy
    * function for EFR32xG21 for library consistency/compatibility.
    */

   // Reset IADC to reset configuration in case it has been modified by
   // other code
   IADC_reset(IADC0);

   // Select clock for IADC
   CMU_ClockSelectSet(cmuClock_IADCCLK, cmuSelect_FSRCO);  // FSRCO - 20MHz

   // Modify init structs and initialize
   init.warmup = iadcWarmupKeepWarm;
  //initAllConfigs.configs[0].adcMode=iadcCfgModeHighSpeed;
 // TODO: init.warmup = iadcWarmupKeepInStandby; // modify according to param

   // Set the HFSCLK prescale value here
   init.srcClkPrescale = IADC_calcSrcClkPrescale(IADC0, CLK_SRC_ADC_FREQ, 0);

   // Configuration 0 is used by both scan and single conversions by default
   // Use unbuffered AVDD as reference
   initAllConfigs.configs[0].reference = iadcCfgReferenceVddx;

   // Divides CLK_SRC_ADC to set the CLK_ADC frequency
   initAllConfigs.configs[0].adcClkPrescale = IADC_calcAdcClkPrescale(IADC0,
                                              CLK_ADC_FREQ,
                                              0,
                                              iadcCfgModeNormal,
                                              init.srcClkPrescale);

   initAllConfigs.configs[0].digAvg = iadcDigitalAverage2;

   // Assign pins to positive and negative inputs in differential mode
   initSingleInput.posInput   = IADC_INPUT_0_PORT_PIN;
   initSingleInput.negInput   = iadcNegInputGnd;

   // Allocate the analog bus for ADC0 inputs
   GPIO->IADC_INPUT_0_BUS |= IADC_INPUT_0_BUSALLOC;

   // Initialize IADC
   IADC_init(IADC0, &init, &initAllConfigs);

   // Initialize Single
   IADC_initSingle(IADC0, &initSingle, &initSingleInput);

   // Clear any previous interrupt flags
   IADC_clearInt(IADC0, _IADC_IF_MASK);

  // DebugPin_SetHigh();  // TODO: remove debug

   // Enable single done interrupts
   IADC_enableInt(IADC0, IADC_IEN_SINGLEDONE);

   // Enable ADC interrupts
   NVIC_ClearPendingIRQ(IADC_IRQn);
   NVIC_EnableIRQ(IADC_IRQn);
}

/**************************************************************************//**
 * @brief  ADC Handler
 *****************************************************************************/
void IADC_IRQHandler(void)
{
  RTOS_ERR err;


   // Read data from the FIFO
   sample = IADC_pullSingleFifoResult(IADC0);
   DebugPin_SetHigh();
   uint32_t flags = IADC_getInt(IADC0);

   singleResult = sample.data * 3.3 / 0xFFF;

   OSFlagPost(&NGSAFlagGrp,
              EVENT_ADC_COMPLETE,
              OS_OPT_POST_FLAG_SET,
              &err);

   // Clear IADC interrupt flags
   IADC_clearInt(IADC0, flags);
   NVIC_ClearPendingIRQ(IADC_IRQn);
   NVIC_EnableIRQ(IADC_IRQn);

}

/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
void ADC_init(void)
{
  /* Initialize the IADC */
 // initIADC();
  /* Start the IADC */
  IADC_command(IADC0, iadcCmdStartSingle);
}

void Stop_ADC(void)
{
  CMU_ClockEnable(cmuClock_IADC0, false);
  CMU_ClockEnable(cmuClock_FSRCO, false);
}
extern uint32_t read_val(void)
{
  /* Enough Time to read Adc*/
  //sl_sleeptimer_delay_millisecond(10);
   IADC_reset(IADC0);

  return sample.data ;
}

extern uint32_t ADC_wait_for_val(void)
{
  RTOS_ERR err;

  /* Pending on the Event, 10 second Timeout set the event */
  OSFlagPend(&NGSAFlagGrp,
             EVENT_ADC_COMPLETE,
             (OS_TICK) 0,
             (OS_OPT_PEND_FLAG_SET_ANY | // Wait until ANY flags are set and
              OS_OPT_PEND_BLOCKING |     // task will block and
              OS_OPT_PEND_FLAG_CONSUME), // Consume flags
             (CPU_TS) 0,
             &err);

//  DebugPin_SetLow();  // Got sample TODO: remove debug

  return sample.data;
}

extern uint16_t measureAndSentADCReading(uint8_t channel)
{
    uint16_t reading;


    IADC_command(IADC0, iadcCmdStartSingle);
    DebugPin_SetLow();  // TODO: remove debug
    reading = ADC_wait_for_val();


#if USE_UART == 1u
#if NO_GUI == 0U
    if (channel == 0) {
        EUSART_Write(0x55);
    } else {
        EUSART_Write(0xAA);
    }
    EUSART_Write((uint8_t) (reading >> 8));
    EUSART_Write((uint8_t) (reading & 0xFF));
#endif  /* NO_GUI */
#endif  /* USE_UART */
    return reading;
}


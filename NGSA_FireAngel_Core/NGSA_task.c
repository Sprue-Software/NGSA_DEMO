/***************************************************************************//**
 * @file
 * @brief NGSA Demo 2021
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

#include "sl_simple_led.h"
#include "sl_simple_led_instances.h"
#include "spidrv.h"
#include "sl_spidrv_instances.h"
#include "os.h"
#include "sl_sleeptimer.h"

extern uint32_t read_val(void);
extern void ADC_init(void);
/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

#ifndef LED_INSTANCE
#define LED_INSTANCE      sl_led_led0
#endif

#ifndef TOOGLE_DELAY_MS
#define NGSA_DELAY_MS           10000
#endif

#ifndef BLINK_TASK_STACK_SIZE
#define NGSA_TASK_STACK_SIZE      10000
#endif

#ifndef BLINK_TASK_PRIO
#define NGSA_TASK_PRIO            20
#endif


/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/

static OS_TCB tcb;
static CPU_STK stack[NGSA_TASK_STACK_SIZE];

sl_sleeptimer_timer_handle_t timer,timer1;
// use SPI handle for EXP header (configured in project settings)
#define SPI_HANDLE                  sl_spidrv_SPI1_handle

// size of transmission and reception buffers
#define APP_BUFFER_SIZE             10
// Transmission and reception buffers
static char rx_buffer[APP_BUFFER_SIZE];
static char tx_buffer[APP_BUFFER_SIZE];


#define NGSA_EXAMPLE_FLAG_TOGGLE    (OS_FLAGS) 0x0001
OS_FLAG_GRP NGSAFlagGrp;
// Semaphore to signal that transfer is complete
static OS_SEM  tx_semaphore;
uint32_t adc_read=0;

/*******************************************************************************
 *********************   LOCAL FUNCTION PROTOTYPES   ***************************
 ******************************************************************************/


static void NGSA_Diagnostic_task_using_sleep_timer(void *arg);
static void on_timeout_Diagnostic(sl_sleeptimer_timer_handle_t *handle, void *data);
static void my_timer_callback(sl_sleeptimer_timer_handle_t *handle, void *data);
void transfer_callback(SPIDRV_HandleData_t *handle,Ecode_t transfer_status,int items_transferred);
static void spidrv_app_task(void);
/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * Initialize NGSA task.
 ******************************************************************************/
void NGSA_SYS_INIT(void)
{
  RTOS_ERR err;

  /* Create NGSA Task*/
  OSTaskCreate(&tcb,
               "NGSA task",
               NGSA_Diagnostic_task_using_sleep_timer,
               DEF_NULL,
               NGSA_TASK_PRIO,
               &stack[0],
               (NGSA_TASK_STACK_SIZE / 10u),
                NGSA_TASK_STACK_SIZE,
               0u,
               0u,
               DEF_NULL,
               (OS_OPT_TASK_STK_CLR),
               &err);
  EFM_ASSERT((RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE));
}

/***************************************************************************//**
 * Diagnostic task: every 60 second
 ******************************************************************************/
static void NGSA_Diagnostic_task_using_sleep_timer(void *arg)
{
  RTOS_ERR err;
  /* Calculate Delay  */
  uint32_t delay = sl_sleeptimer_ms_to_tick(180);
  OSSemCreate(&tx_semaphore, "transfer semaphore", (OS_SEM_CTR)0, &err);
  /* Create Events for synchronisation   */
  OSFlagCreate(&NGSAFlagGrp,
               "NGSA flag group",
               (OS_FLAGS) NULL,
               &err);
  /* Create Periodic Task of 10 seconds , On timeout signal the waiting Task  */
  sl_sleeptimer_start_periodic_timer_ms(&timer,
                                        NGSA_DELAY_MS,
                                        on_timeout_Diagnostic, NULL,
                                        0,
                                        SL_SLEEPTIMER_NO_HIGH_PRECISION_HF_CLOCKS_REQUIRED_FLAG);


  (void)&arg;
  /* Blocking Thread*/
  do {
    RTOS_ERR err;
    /* Pending on the Event, 10 second Timeout set the event */
    OSFlagPend(&NGSAFlagGrp,
               NGSA_EXAMPLE_FLAG_TOGGLE,
               (OS_TICK) 0,
               (OS_OPT) OS_OPT_PEND_FLAG_SET_ANY + OS_OPT_PEND_FLAG_CONSUME,
               (CPU_TS) 0,
               &err);

     /* SMoke */
     /* Co  */
     /* Heartbeat Led*/
     /* To check Code is running , toggle Board LED*/
    /* ADC Init: init ADC & start command */
    ADC_init();
#ifdef LED_BLINK
   // sl_led_turn_on(&LED_INSTANCE);
#endif
    sl_sleeptimer_start_timer(&timer1,delay,my_timer_callback,NULL,0,0);
    spidrv_app_task();
   /* This just for testing to switch off the LED afetr 180ms , You can use blocking call  /*sl_sleeptimer_delay_millisecond*/
    sl_sleeptimer_start_timer(&timer1,delay,my_timer_callback,NULL,0,0);

  } while (1);
}

static void on_timeout_Diagnostic(sl_sleeptimer_timer_handle_t *handle, void *data)
{
  RTOS_ERR err;
  (void)&data;
  OSFlagPost(&NGSAFlagGrp,
             NGSA_EXAMPLE_FLAG_TOGGLE,
             OS_OPT_POST_FLAG_SET,
             &err);
}

static void my_timer_callback(sl_sleeptimer_timer_handle_t *handle, void *data)
{
  (void)&data;
#ifdef LED_BLINK
 // sl_led_turn_off(&LED_INSTANCE);
#endif

  adc_read=read_val();
  /* Disable Clock for Low current*/
  CMU_ClockEnable(cmuClock_IADC0, false);
  CMU_ClockEnable(cmuClock_FSRCO, false);

}


/***************************************************************************//**
 * spidrv task.
 ******************************************************************************/
static void spidrv_app_task(void)
{
  RTOS_ERR err;
  CPU_TS  ts;
  Ecode_t ecode;

  int counter = 0;
  counter++;

    // Non-blocking data transfer to slave. When complete, rx buffer
    // will be filled.
    ecode = SPIDRV_MTransfer(SPI_HANDLE, "test", rx_buffer, APP_BUFFER_SIZE, transfer_callback);
    EFM_ASSERT(ecode == ECODE_OK);

    // Wait for semaphore indicating that transfer is complete
#if 1
    OSSemPend(&tx_semaphore,
              0,
              OS_OPT_PEND_BLOCKING,
              &ts,
              &err);
    EFM_ASSERT((RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE));
#endif
    //printf("Got message from slave: %s\r\n", rx_buffer);
}


// Callback fired when data is transmitted
void transfer_callback(SPIDRV_HandleData_t *handle,
                       Ecode_t transfer_status,
                       int items_transferred)
{
  RTOS_ERR err;
  (void)&handle;
  (void)items_transferred;

  // Post semaphore to signal to application
  // task that transfer is successful
  if (transfer_status == ECODE_EMDRV_SPIDRV_OK) {
    OSSemPost(&tx_semaphore,
              OS_OPT_POST_1,
              &err);
  }
}

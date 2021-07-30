#include "sl_emlib_gpio_simple_init.h"
#include "sl_emlib_gpio_init_CO_POL_config.h"
#include "sl_emlib_gpio_init_Enable_PIN_config.h"
#include "em_gpio.h"
#include "em_cmu.h"

void sl_emlib_gpio_simple_init(void)
{
  CMU_ClockEnable(cmuClock_GPIO, true);
  GPIO_PinModeSet(SL_EMLIB_GPIO_INIT_CO_POL_PORT,
                  SL_EMLIB_GPIO_INIT_CO_POL_PIN,
                  SL_EMLIB_GPIO_INIT_CO_POL_MODE,
                  SL_EMLIB_GPIO_INIT_CO_POL_DOUT);

  GPIO_PinModeSet(SL_EMLIB_GPIO_INIT_ENABLE_PIN_PORT,
                  SL_EMLIB_GPIO_INIT_ENABLE_PIN_PIN,
                  SL_EMLIB_GPIO_INIT_ENABLE_PIN_MODE,
                  SL_EMLIB_GPIO_INIT_ENABLE_PIN_DOUT);
}

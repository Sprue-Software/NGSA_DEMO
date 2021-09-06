#include "os.h"
extern void __delay_ms(uint16_t time_ms_val);
void HeartBeatOn(void)
{
    SPI_Write(0x06, 0x08);
}

void HeartBeatOff(void)
{
    SPI_Write(0x06, 0x00);
}

/* 50ms on, every 44 secs. 
 * Number of blinks defined by function argument. Set number of blinks to zero in order to blink continuously  */
void HeartBeatContBlink(uint16_t no_of_blinks)
{
    uint16_t blink_ctr = 0u;
    
    while((no_of_blinks == 0u) || (blink_ctr < no_of_blinks))
    {
        /* on for 50ms */
        //__delay_us(50000u); // todo: use only if more precision is required
        HeartBeatOn();
        __delay_ms(50);
        
        /* off for 43.950 secs */
        HeartBeatOff();
        for (uint8_t ctr = 0; ctr < 10u; ctr++)
        {
            __delay_ms(4395u);
        }
        blink_ctr++;
    }
}

/* 
 * File:   SleepTests.c
 * Author: pstarzyk (modified Microchip example)
 *
 * Created on 19 April 2021, 14:41
 */
#include "os.h"
#include "HeartBeatTests.h"
#include "SmokeDetection.h"


void HeartbeatAndSleep(void)
{
    CLRWDT();
    HeartBeatOn();
    __delay_ms(1000);
    HeartBeatOff();
    CLRWDT();
    
    while(1)
    {
        HeartBeatOn();
#if USE_GREEN_LED == 1U 
        LEDGreen_SetLow();
#endif /* USE_GREEN_LED */
        __delay_ms(10);
#if USE_GREEN_LED == 1U
        LEDGreen_SetHigh();
#endif /* USE_GREEN_LED */
        HeartBeatOff();
        CLRWDT(); 
        SLEEP();
    }
}


void SmokeHeartBeatAndSleep(void)
{
    uint8_t photo_int_ctr = 0u;
#if USE_GREEN_LED == 1U
    LEDGreen_SetDigitalOutput();
#endif /* USE_GREEN_LED */
    CLRWDT();
    HeartBeatOn();
    __delay_ms(1000);
    HeartBeatOff();
    CLRWDT();
    
    while(1)
    {
        Photo_Integrate(0x05u); /* blue(photo_1), gain=32, 100us of integration time */
        /* todo: uncomment after issue with IR LED is checked by Julian */
       // Photo_Integrate(0x23u); /* IR(photo_2), gain=8, 100us of integration time */
        
        if (photo_int_ctr == 4u)
        {
            photo_int_ctr = 0u;
            
            HeartBeatOn();
#if USE_GREEN_LED == 1U 
            LEDGreen_SetLow();
#endif /* USE_GREEN_LED */
            __delay_ms(10);
#if USE_GREEN_LED == 1U
            LEDGreen_SetHigh();
#endif /* USE_GREEN_LED */
            HeartBeatOff();
        }
        else
        {
            photo_int_ctr++;
        }
        CLRWDT(); 
        SLEEP();
    }
}


void AFE_smoke_detection_ready_mode(void)
{
#if 1 // IH
    SPI_Write(0x0A,0x01);  // SPI normal, bit0: low boost voltage is 1 (5.2V)

    SPI_Write(0x0C, 0x83); //Internal timer, 100us, Gain=8

    // Set Enable controls Photo Integration
    SPI_Write(0x10,0x00); //Horn= normal (no:direct_drive,Enable,bridge)
#endif

    SPI_Write(0x0E,0x74); // IRED1 = 80mA, IRED2 = 200mA
}


void AFE_low_power_mode(void)
{   
    SPI_Write(0x00,0x00);  // ABuf off
    SPI_Write(0x02, 0x00); // Low Boost Off, Hi Boost off, IRCAP off
    
    //Photo=off, reset
    SPI_Write(0x04,0x00); /* just in case. Should be already in this state */
    
    // Horn,IO,RLED=off, CO Current test off, CO Op Amp tristate disabled
    SPI_Write(0x06,0x00);
    
    //Battery switch on, regulator switch off
    SPI_Write(0x08,0x04);
    //IH    SPI_Write(0x08,0x14); // CO Amp Power ON, CO Ref OFF, Run internals VBAT, Regulator disable
    
    //Set SPI to RdNow high - SPI read output immediately available
    //turn off watch_dog timer - Otherwise there will be a chirp every 20sec
    //unless there is SPI communications, leave Low Boost at default of 5.2V
    SPI_Write(0x0A,0x11); /* bit0: low boost voltage is 1 (5.2V) */
    
    //Photo:Gain=1,timing=internal,Tint=100us,ABuf=Vp2
    SPI_Write(0x0C,0x00);

    /* IRED1 = 20mA, IRED2 = 20mA */
    SPI_Write(0x0E,0x00);
 
    //Horn= normal (no:direct_drive,Enable,bridge)
    SPI_Write(0x10,0x00);
}

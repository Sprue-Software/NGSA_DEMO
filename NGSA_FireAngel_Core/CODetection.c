/* 
 * File:   SmokeDetection.c
 * Author: pstarzyk (modified Microchip example)
 *
 * Created on 15 April 2021, 12:55
 */
#include "os.h"
#include "NGSA_task.h"
#include "SmokeDetection.h"

void SendCOPattern(uint8_t rxData) {
    SPI_Write(0x02, 0x05); //charges the IRCAP, low boost mode
    SPI_Write(0x0A, 0x01);
    __delay_ms(200);

    SPI_Write(0x06, 0x06); //Reg 3 - IOout  high, IOEn Transmit on
    SPI_Write(0x10, 0x30); //Reg 8 - HiIO high current, HiDmp high current
    __delay_ms(50);
    SPI_Write(0x06, 0x02); //Reg 3 - IOout  low, IOEn Transmit on
    __delay_ms(150);
    SPI_Write(0x06, 0x06); //Reg 3 - IOout  high, IOEn Transmit on
    __delay_ms(50);
    SPI_Write(0x06, 0x02); //Reg 3 - IOout  low, IOEn Transmit on
    __delay_ms(250);
    SPI_Write(0x06, 0x06); //Reg 3 - IOout  high, IOEn Transmit on
    __delay_ms(50);
    SPI_Write(0x06, 0x02); //Reg 3 - IOout  low, IOEn Transmit on
    __delay_ms(150);
    SPI_Write(0x06, 0x06); //Reg 3 - IOout  high, IOEn Transmit on
    __delay_ms(50);
    SPI_Write(0x06, 0x02); //Reg 3 - IOout  low, IOEn Transmit on
}

void EnableCO(void)
{
    //Setup and turn on the CO sensor
    SPI_Write(0x00, 0x03); //Register 0 - Set ABUF to the CO sensor
    SPI_Write(0x06, 0x00); //Register 3 - turn on the CO output stage - disable the tristate
    SPI_Write(0x08, 0x14); //Register 4 - CO Amp Power ON, CO Ref OFF, VBAT, Regulator disable

    __delay_ms(10);

    SPI_Write(0x08, 0x34); //Register 4 - CO Amp Power ON, CO Ref ON, VBAT, Regulator disable
    __delay_ms(1);
    COpolarization_SetHigh(); // Turn off anti-polarization JFET
}

void DisableCO(void)
{
#if 1 // standard PIC version
//    SPI_Write(0x08, 0x34); //Register 4 - Turn off CO reference
    SPI_Write(0x08, 0x14); // Register 4 - Turn off CO reference (not CO Amp)
    __delay_ms(10);
    SPI_Write(0x06, 0x80); //Register 3 - turn off the CO output stage - enable the tri-state
    __delay_ms(10);
    SPI_Write(0x08, 0x04); //Register 4 - Turn off CO amp
    COpolarization_SetLow(); //Turn back on anti-polarization JFET

    SPI_Write(0x00, 0x00); //Register 0 - Set ABUF OFF

#else
    /* Modified version (as Stuart Hart's recommendations) */
    // CO Amp should not be turned off
    // CO Tristate should only be Enabled for CO Test

    //    SPI_Write(0x08, 0x34); //Register 4 - Turn off CO reference
        SPI_Write(0x08, 0x14); // Register 4 - Turn off CO reference (not CO Amp)
        __delay_ms(10);
    //    SPI_Write(0x06, 0x80); //Register 3 - turn off the CO output stage - enable the tri-state
    //    __delay_ms(10);
    //    SPI_Write(0x08, 0x04); //Register 4 - Turn off CO amp
    //    COpolarization_SetLow(); //Turn back on anti-polarization JFET

    SPI_Write(0x00, 0x00); //Register 0 - Set ABUF OFF

#endif
}

void initCODetection(void)
{
    // Advised rules (but upset CO test!):
    // CO Amp should be ON all the time
    // CO OpAmp Tri-state should only be Enabled for CO Test (otherwise Tri-state disabled)
    // CO Ref only on when needed, to save power

    SPI_Write(0x08, 0x14); // Register 4 - CO Amp Power ON, Run internals VBAT, Regulator disable

    COpolarization_SetHigh(); //Turn off anti-polarization JFET
}

uint16_t readCO(void)
{
    volatile uint16_t reading = 0u;

    SPI_Write(0x00, 0x03); // Reg 0 - Set ABUF to the CO sensor

    SPI_Write(0x06, 0x00); // Reg 3 - turn on the CO output stage - disable the tristate
    __delay_us(5);

    SPI_Write(0x08, 0x34); // Reg 4 - CO Amp Power ON, CO reference ON, Run internals VBAT, Regulator disable

    __delay_us(5);

    reading = measureAndSentADCReading(1); //read the integration value and send out

    // CO reference OFF
    SPI_Write(0x08, 0x14); // Reg 4 - CO Amp Power ON, CO reference OFF, Run internals VBAT, Regulator disable

    return reading;
}

void EnableCOPolar(uint8_t rxData) {
    COpolarization_SetHigh(); //Turn OFF anti-polarization JFET
}

void DisableCOPolar(uint8_t rxData) {
    COpolarization_SetLow(); //Turn ON anti-polarization JFET
}

uint16_t RunCOTest(void)
{
  volatile uint16_t reading1 = 0u;
  volatile uint16_t reading2 = 0u;

  //IH
  SPI_Write (0x00, 0x03); // Reg 0 - Set ABUF to the CO sensor

  COpolarization_SetLow(); //Turn back on anti-polarization JFET (or analog switch)

  SPI_Write(0x06, 0x00); //Register 3 - turn on the CO output stage - disable the tristate
  SPI_Write(0x08, 0x14); //Register 4 - Run off Battery Internal, Regulator disable
  //             Enable CO Amp
  __delay_ms(10);
  SPI_Write(0x08, 0x34); //Register 4 - Same as above plus enable CO reference

  COpolarization_SetHigh(); //Turn off anti-polarization JFET or the analog switch
  __delay_ms(1300); //Run CO amp for 1.3 seconds

  reading1 = measureAndSentADCReading(1); //read the CO value

  SPI_Write(0x06, 0x80); //Register 3 - CO Output TriStated,sink, test OFF
  __delay_us(10);
  // *** No Breakpoint Zone - to avoid damage DO NOT put breakpoint between here and end
  SPI_Write(0x06, 0xA0); //Register 3 - CO Output TriStated,sink, test ON
  __delay_ms(500);       // Charging time 500 ms seconds

  SPI_Write(0x06, 0x80); //Register 3 - CO Output TriStated,sink, test OFF
  __delay_us(50);
  SPI_Write(0x06, 0x00); //Register 3 - CO Output tristate OFF,sink, test OFF
  // *** End of No Breakpoint Zone
  __delay_ms(1300); //Run CO amp for 1.3 seconds

//  SPI_Write(0x00, 0x03); //Register 0 - Set ABUF to the CO sensor
  reading2 = measureAndSentADCReading(1); //read the CO value

  SPI_Write(0x08, 0x14); //Register 4 - Turn off CO reference
  __delay_ms(10);

#if 1 // standard PIC
  SPI_Write(0x06, 0x80); //Register 3 - turn off the CO output stage - enable the tristate
  __delay_ms(10);
  SPI_Write(0x08, 0x04); //Turn off CO amp
  COpolarization_SetLow(); //Turn back on anti-polarization JFET
#endif

  // ABuf=off
  SPI_Write(0x00,0x00);

  return reading1;
}

#if 0 // Unused alternative from PIC code

volatile uint16_t reading = 0u;

COpolarization_SetLow(); //Turn back on anti-polarization JFET (or analog switch)

SPI_Write(0x06, 0x40); //Register 3 - turn on the CO output stage (disable the tristate), non-Inverting source

  SPI_Write(0x08, 0x54); //Register 4 - Run off Battery Internal, Regulator disable, INN source

  __delay_ms(10);

  SPI_Write(0x08, 0x74); //Register 4 - Same as above plus enable CO reference, INN source

  COpolarization_SetHigh(); //Turn off anti-polarization JFET or the analog switch

  __delay_ms(8000); //Run CO amp for 1.3 seconds

  SPI_Write(0x06, 0xC0); //Register 3 - CO Output TriStated,sink, test OFF, non-Inverting source
  __delay_us(10);

  SPI_Write(0x06, 0xE0); //Register 3 - CO Output TriStated,sink, test ON, non-Inverting source
  __delay_ms(4000); //Run test for 4000 ms seconds

  SPI_Write(0x06, 0xC0); //Register 3 - CO Output TriStated,sink, test OFF, non-Inverting source
  __delay_us(40);

  SPI_Write(0x06, 0x40); //Register 3 - turn on the CO output stage - disable the tristate, non-Inverting source
  __delay_ms(10000); //Run CO amp for 1.3 seconds

  SPI_Write(0x00, 0x03); //Register 0 - Set ABUF to the CO sensor
  reading = measureAndSentADCReading(1); //read the integration value and send out

  SPI_Write(0x08, 0x54); //Register 4 - Run off Battery Internal, Regulator disable, INN source

  SPI_Write(0x06, 0x00); //Register 3 - CO Output tristate OFF,sink, test OFF
  __delay_ms(1300); //Run CO amp for 1.3 seconds

  SPI_Write(0x08, 0x14); //Register 4 - Turn off CO reference
  __delay_ms(10);
  SPI_Write(0x06, 0x80); //Register 3 - turn off the CO output stage - enable the tristate
  __delay_ms(10);
  SPI_Write(0x08, 0x04); //Turn off CO amp
  COpolarization_SetLow(); //Turn back on anti-polarization JFET

return reading;

#endif

/*    void RunCOTest(uint8_t rxData)
    {
        COpolarization_SetLow();   //Turn back on anti-polarization JFET

        SPI_Write(0x06,0x40);      //Register 3 - turn on the CO output stage - disable the tristate
        SPI_Write(0x08,0x54);      //Register 4 - Register 4 - Run off Battery Internal, Regulator disable
                                   //             Enable CO Amp
        __delay_ms(10);
        SPI_Write(0x08,0x74);      //Register 4 - Same as above plus enable CO reference
        COpolarization_SetHigh();  //Turn off anti-polarization JFET
        __delay_ms(10000);         //Run CO amp for 10 seconds
        SPI_Write(0x06,0xC0);      //Register 3 - CO Output TriStated,source, test OFF
        __delay_us(10);
        SPI_Write(0x06,0xE0);      //Register 3 - CO Output TriStated,source, test ON
        __delay_ms(4000);          //Run test for 4 seconds
        SPI_Write(0x06,0xC0);      //Register 3 - CO Output TriStated,source, test OFF
        __delay_us(50);
        SPI_Write(0x06,0x40);      //Register 3 - CO Output ON,source, test OFF
        __delay_ms(12000);         //Run CO amp for 10 seconds
        SPI_Write(0x08,0x54);      //Register 4 - Turn off CO reference
        __delay_ms(10);
        SPI_Write(0x06,0xC0);      //Register 3 - turn off the CO output stage - enable the tristate
        __delay_ms(10);
        SPI_Write(0x08,0x04);      //Turn off CO amp        
        COpolarization_SetLow();   //Turn back on anti-polarization JFET
    }     
 */

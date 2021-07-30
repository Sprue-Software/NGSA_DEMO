/* 
 * File:   SmokeDetection.c
 * Author: pstarzyk (modified Microchip example)
 *
 * Created on 15 April 2021, 11:51
 */
#include "os.h"
#define USE_UART 0
#define NO_GUI 1
#define DEFAULT_PHOTO_AMP_ENABLE_PERIOD 1

//void *memset(void * p1, int c, register size_t n);

uint8_t pa1reg6data = 0u;
uint8_t pa2reg6data = 0u;
uint8_t integ1Time = 0u;
uint8_t integ2Time = 0u;


uint16_t measureAndSentADCReading(uint8_t channel) {
    uint16_t reading;
   // reading = ADCC_GetSingleConversion(ABUF);
    reading=read_val ();
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


/*
 * Function perform a 100uS integration on PA1
 */
void PA1_100us_Integration() {
  #if (USE_UART == 1u && NO_GUI == 1u)
    static uint16_t secs;
#endif /* (USE_UART == 1u && NO_GUI == 1u) */
    uint16_t dark_reading = 0u;
    uint16_t bright_reading = 0u;
    uint16_t diff = 0u;
    char buffer[4] = {0, 0, 0, 0};
    __delay_us(10); //first integration will be a dark - LED1En is low
    SPI_Write(0x04, 0x03); //enable the photo-amp, and set the Status bit to 1 - READY State
    /*NOTE: as per spec 107us for startup should be enough */
    __delay_us(150); //wait for internal photo amp 3v regulator to stabilize 
    Enable_SetHigh(); //start dark integration utilizing Enable Pin
    __delay_us(5);
    Enable_SetLow();
    __delay_us(125); //allow enough time for the integration with some slack
    dark_reading = measureAndSentADCReading(0); //read the integration value and send out
    SPI_Write(0x04, 0x01); //reset integration capacitors - RESET State
    __delay_us(10); //second integration will be a Lit - LED1En is high
    SPI_Write(0x04, 0x0B); //enable the photo-amp, and set the Status bit to 1, enable LED1 - READY State
    __delay_us(10);
    Enable_SetHigh(); //start Lit integration utilizing Enable Pin
    __delay_us(5);
    Enable_SetLow();
    __delay_us(125);
    bright_reading = measureAndSentADCReading(0); //read the integration value and send out
    diff = (bright_reading > dark_reading) ? bright_reading - dark_reading : 0u;
#if DEFAULT_PHOTO_AMP_ENABLE_PERIOD == 1U
    __delay_ms(1);
    SPI_Write(0x04, 0x00); // disable the photo-amp, will put into RESET State
    __delay_ms(1); //allow time to switch back to CO for ABUF 
    measureAndSentADCReading(0); //take CO reading -WAK 08102018
#else
    SPI_Write(0x04, 0x00);
#endif /* DEFAULT_PHOTO_AMP_ENABLE_PERIOD */
    
#if (USE_UART == 1u && NO_GUI == 1u)
#if DATA_FOR_EXCEL == 1U
    if (secs == 0u)
    {
    EUSART_Write((uint8_t) 's');
    EUSART_Write((uint8_t) 'e');
    EUSART_Write((uint8_t) 'c');
    EUSART_Write((uint8_t) ' ');
    EUSART_Write((uint8_t) ' ');
    EUSART_Write((uint8_t) 'B');
    EUSART_Write((uint8_t) '_');
    EUSART_Write((uint8_t) 'd');
    EUSART_Write((uint8_t) 'a');
    EUSART_Write((uint8_t) 'r');
    EUSART_Write((uint8_t) 'k');
    EUSART_Write((uint8_t) ' ');
    EUSART_Write((uint8_t) ' ');
    EUSART_Write((uint8_t) 'B');
    EUSART_Write((uint8_t) '_');
    EUSART_Write((uint8_t) 'l');
    EUSART_Write((uint8_t) 'i');
    EUSART_Write((uint8_t) 'g');
    EUSART_Write((uint8_t) 'h');
    EUSART_Write((uint8_t) 't');
    EUSART_Write((uint8_t) ' ');
    EUSART_Write((uint8_t) ' ');
    EUSART_Write((uint8_t) 'B');
    EUSART_Write((uint8_t) '_');
    EUSART_Write((uint8_t) 'd');
    EUSART_Write((uint8_t) 'i');
    EUSART_Write((uint8_t) 'f');
    EUSART_Write((uint8_t) 'f');
    EUSART_Write((uint8_t) ' ');
    EUSART_Write((uint8_t) ' ');
    
    EUSART_Write((uint8_t) 'I');
    EUSART_Write((uint8_t) '_');
    EUSART_Write((uint8_t) 'd');
    EUSART_Write((uint8_t) 'a');
    EUSART_Write((uint8_t) 'r');
    EUSART_Write((uint8_t) 'k');
    EUSART_Write((uint8_t) ' ');
    EUSART_Write((uint8_t) ' ');
    EUSART_Write((uint8_t) 'I');
    EUSART_Write((uint8_t) '_');
    EUSART_Write((uint8_t) 'l');
    EUSART_Write((uint8_t) 'i');
    EUSART_Write((uint8_t) 'g');
    EUSART_Write((uint8_t) 'h');
    EUSART_Write((uint8_t) 't');
    EUSART_Write((uint8_t) ' ');
    EUSART_Write((uint8_t) ' ');
    EUSART_Write((uint8_t) 'I');
    EUSART_Write((uint8_t) '_');
    EUSART_Write((uint8_t) 'd');
    EUSART_Write((uint8_t) 'i');
    EUSART_Write((uint8_t) 'f');
    EUSART_Write((uint8_t) 'f');
    EUSART_Write((uint8_t) '\r');
    EUSART_Write((uint8_t) '\n');
    }
#endif /* DATA_FOR_EXCEL */  
    memset(buffer, 0, 4);
    itoa(buffer, secs, 10);
#if DATA_FOR_EXCEL == 0U
    EUSART_Write((uint8_t) 's');
    EUSART_Write((uint8_t) 'e');
    EUSART_Write((uint8_t) 'c');
    EUSART_Write((uint8_t) ':');
#endif /* DATA_FOR_EXCEL */
    EUSART_Write((uint8_t) ' ');
    EUSART_Write((uint8_t) buffer[0]);
    EUSART_Write((uint8_t) buffer[1]); 
    EUSART_Write((uint8_t) buffer[2]); 
    EUSART_Write((uint8_t) buffer[3]); 
#if DATA_FOR_EXCEL == 0U    
    EUSART_Write((uint8_t) '\r'); 
    EUSART_Write((uint8_t) '\n');
#endif /* DATA_FOR_EXCEL */    
    memset(buffer, 0, 4);
    itoa(buffer, dark_reading, 10);
#if DATA_FOR_EXCEL == 0U
    EUSART_Write((uint8_t) 'd');
    EUSART_Write((uint8_t) 'a');
    EUSART_Write((uint8_t) 'r');
    EUSART_Write((uint8_t) 'k');
    EUSART_Write((uint8_t) ':');
#else
    EUSART_Write((uint8_t) ',');
#endif /* DATA_FOR_EXCEL */
    EUSART_Write((uint8_t) ' ');
    EUSART_Write((uint8_t) buffer[0]);
    EUSART_Write((uint8_t) buffer[1]); 
    EUSART_Write((uint8_t) buffer[2]); 
    EUSART_Write((uint8_t) buffer[3]); 
    EUSART_Write((uint8_t) ' ');
    EUSART_Write((uint8_t) ' ');
    
    memset(buffer, 0, 4);
    itoa(buffer, bright_reading, 10);
#if DATA_FOR_EXCEL == 0U
    EUSART_Write((uint8_t) 'b');
    EUSART_Write((uint8_t) 'l');
    EUSART_Write((uint8_t) 'u');
    EUSART_Write((uint8_t) 'e');
    EUSART_Write((uint8_t) ':');
#else
    EUSART_Write((uint8_t) ',');
#endif /* DATA_FOR_EXCEL */
    EUSART_Write((uint8_t) ' ');
    EUSART_Write((uint8_t) buffer[0]);
    EUSART_Write((uint8_t) buffer[1]); 
    EUSART_Write((uint8_t) buffer[2]); 
    EUSART_Write((uint8_t) buffer[3]);
    EUSART_Write((uint8_t) ' ');
    EUSART_Write((uint8_t) ' ');
    
    memset(buffer, 0, 4);
    itoa(buffer, diff, 10);
#if DATA_FOR_EXCEL == 0U
    EUSART_Write((uint8_t) 'd');
    EUSART_Write((uint8_t) 'i');
    EUSART_Write((uint8_t) 'f');
    EUSART_Write((uint8_t) 'f');
    EUSART_Write((uint8_t) ':');
#else
    EUSART_Write((uint8_t) ',');
#endif /* DATA_FOR_EXCEL */
    EUSART_Write((uint8_t) ' ');
    EUSART_Write((uint8_t) buffer[0]);
    EUSART_Write((uint8_t) buffer[1]); 
    EUSART_Write((uint8_t) buffer[2]); 
    EUSART_Write((uint8_t) buffer[3]);
#if DATA_FOR_EXCEL == 0U
    EUSART_Write((uint8_t) '\r'); 
    EUSART_Write((uint8_t) '\n');
#endif
    
    secs += 10u;
    
#endif /* (USE_UART == 1u && NO_GUI == 1u) */
}

/*
 * Function perform a 100uS integration on PA2
 */
void PA2_100us_Integration() {
    uint16_t dark_reading = 0u;
    uint16_t bright_reading = 0u;
    uint16_t diff = 0u;
    char buffer[4] = {0, 0, 0, 0};
    
    __delay_us(10); //first integration will be a dark - LED2En is low
    SPI_Write(0x04, 0x03); //enable the photo-amp, and set the Status bit to 1 - READY State
    __delay_us(150); //wait for internal photo amp 3v regulator to stabilize            
    Enable_SetHigh(); //start dark integration utilizing Enable Pin
    __delay_us(5);
    Enable_SetLow();
    __delay_us(125); //allow enough time for the integration with some slack
    dark_reading = measureAndSentADCReading(1); //read the integration value and send out
    SPI_Write(0x04, 0x11); //reset integration capacitors - RESET State
    __delay_us(10); //second integration will be a Lit - LED2En is high
    SPI_Write(0x04, 0x13); //enable the photo-amp, and set the Status bit to 1, enable LED2 - READY State
    __delay_us(10);
    Enable_SetHigh(); //start Lit integration utilizing Enable Pin
    __delay_us(5);
    Enable_SetLow();
    __delay_us(125);
    bright_reading = measureAndSentADCReading(1); //read the integration value and send out
    diff = bright_reading - dark_reading;
 #if DEFAULT_PHOTO_AMP_ENABLE_PERIOD == 1U
    __delay_ms(1);
    SPI_Write(0x04, 0x00); // disable the photo-amp, will put into RESET State
    __delay_ms(1); //allow time to switch back to CO for ABUF 
    measureAndSentADCReading(1); //take CO reading -WAK 08102018
#else
    SPI_Write(0x04, 0x00);
#endif /* DEFAULT_PHOTO_AMP_ENABLE_PERIOD */
    
#if (USE_UART == 1u && NO_GUI == 1u)
    memset(buffer, 0, 4);
    itoa(buffer, dark_reading, 10);
#if DATA_FOR_EXCEL == 0U
    EUSART_Write((uint8_t) 'd');
    EUSART_Write((uint8_t) 'a');
    EUSART_Write((uint8_t) 'r');
    EUSART_Write((uint8_t) 'k');
    EUSART_Write((uint8_t) ':');
#else
    EUSART_Write((uint8_t) ',');
#endif /* DATA_FOR_EXCEL */
    EUSART_Write((uint8_t) ' ');
    EUSART_Write((uint8_t) buffer[0]);
    EUSART_Write((uint8_t) buffer[1]); 
    EUSART_Write((uint8_t) buffer[2]); 
    EUSART_Write((uint8_t) buffer[3]); 
    EUSART_Write((uint8_t) ' ');
    EUSART_Write((uint8_t) ' ');
  
    memset(buffer, 0, 4);
    itoa(buffer, bright_reading, 10);
#if DATA_FOR_EXCEL == 0U
    EUSART_Write((uint8_t) 'I');
    EUSART_Write((uint8_t) 'R');
    EUSART_Write((uint8_t) ':');
    EUSART_Write((uint8_t) ' ');
    EUSART_Write((uint8_t) ' ');
#else
    EUSART_Write((uint8_t) ',');
#endif /* DATA_FOR_EXCEL */
    EUSART_Write((uint8_t) ' ');
    EUSART_Write((uint8_t) buffer[0]);
    EUSART_Write((uint8_t) buffer[1]); 
    EUSART_Write((uint8_t) buffer[2]); 
    EUSART_Write((uint8_t) buffer[3]);
    EUSART_Write((uint8_t) ' ');
    EUSART_Write((uint8_t) ' ');
    
    memset(buffer, 0, 4);
    itoa(buffer, diff, 10);
#if DATA_FOR_EXCEL == 0U
    EUSART_Write((uint8_t) 'd');
    EUSART_Write((uint8_t) 'i');
    EUSART_Write((uint8_t) 'f');
    EUSART_Write((uint8_t) 'f');
    EUSART_Write((uint8_t) ':');
#else
    EUSART_Write((uint8_t) ',');
#endif /* DATA_FOR_EXCEL */
    EUSART_Write((uint8_t) ' ');
    EUSART_Write((uint8_t) buffer[0]);
    EUSART_Write((uint8_t) buffer[1]); 
    EUSART_Write((uint8_t) buffer[2]); 
    EUSART_Write((uint8_t) buffer[3]);
    EUSART_Write((uint8_t) '\r'); 
    EUSART_Write((uint8_t) '\n');
    
#if DATA_FOR_EXCEL == 0U    
    /* empty line */
    EUSART_Write((uint8_t) '\r'); 
    EUSART_Write((uint8_t) '\n');
#endif /* DATA_FOR_EXCEL */    
#endif /* (USE_UART == 1u && NO_GUI == 1u) */
}

/*
 * Function perform a 200uS integration on PA1
 */
void PA1_200us_Integration() {
    __delay_us(10); //first integration will be a dark - LED1En is low
    SPI_Write(0x04, 0x03); //enable the photo-amp, and set the Status bit to 1 - READY State
    __delay_us(150); //wait for internal photo amp 3v regulator to stabilize            
    Enable_SetHigh(); //start dark integration utilizing Enable Pin
    __delay_us(5);
    Enable_SetLow();
    __delay_us(250); //allow enough time for the integration with some slack
    measureAndSentADCReading(0); //read the integration value and send out
    SPI_Write(0x04, 0x01); //reset integration capacitors - RESET State
    __delay_us(10); //second integration will be a Lit - LED1En is high
    SPI_Write(0x04, 0x0B); //enable the photo-amp, and set the Status bit to 1, enable LED1 - READY State
    __delay_us(10);
    Enable_SetHigh(); //start Lit integration utilizing Enable Pin
    __delay_us(5);
    Enable_SetLow();
    __delay_us(250);
    measureAndSentADCReading(0); //read the integration value and send out
    __delay_ms(1);
    SPI_Write(0x04, 0x00); // disable the photo-amp, will put into RESET State
    __delay_ms(1); //allow time to switch back to CO for ABUF 
    measureAndSentADCReading(0); //take CO reading -WAK 08102018
}

/*
 * Function perform a 200uS integration on PA2
 */
void PA2_200us_Integration() {
    __delay_us(10); //first integration will be a dark - LED2En is low
    SPI_Write(0x04, 0x03); //enable the photo-amp, and set the Status bit to 1 - READY State
    __delay_us(150); //wait for internal photo amp 3v regulator to stabilize            
    Enable_SetHigh(); //start dark integration utilizing Enable Pin
    __delay_us(5);
    Enable_SetLow();
    __delay_us(250); //allow enough time for the integration with some slack
    measureAndSentADCReading(1); //read the integration value and send out
    SPI_Write(0x04, 0x11); //reset integration capacitors - RESET State
    __delay_us(10); //second integration will be a Lit - LED2En is high
    SPI_Write(0x04, 0x13); //enable the photo-amp, and set the Status bit to 1, enable LED2 - READY State
    __delay_us(10);
    Enable_SetHigh(); //start Lit integration utilizing Enable Pin
    __delay_us(5);
    Enable_SetLow();
    __delay_us(250);
    measureAndSentADCReading(1); //read the integration value and send out
    __delay_ms(1);
    SPI_Write(0x04, 0x00); // disable the photo-amp, will put into RESET State
    __delay_ms(1); //allow time to switch back to CO for ABUF 
    measureAndSentADCReading(1); //take CO reading -WAK 08102018
}

/*
 * Function perform a 300uS integration on PA1
 */
void PA1_300us_Integration() {
    __delay_us(10); //first integration will be a dark - LED1En is low
    SPI_Write(0x04, 0x03); //enable the photo-amp, and set the Status bit to 1 - READY State
    __delay_us(150); //wait for internal photo amp 3v regulator to stabilize            
    Enable_SetHigh(); //start dark integration utilizing Enable Pin
    __delay_us(5);
    Enable_SetLow();
    __delay_us(375); //allow enough time for the integration with some slack
    measureAndSentADCReading(0); //read the integration value and send out
    SPI_Write(0x04, 0x01); //reset integration capacitors - RESET State
    __delay_us(10); //second integration will be a Lit - LED1En is high
    SPI_Write(0x04, 0x0B); //enable the photo-amp, and set the Status bit to 1, enable LED1 - READY State
    __delay_us(10);
    Enable_SetHigh(); //start Lit integration utilizing Enable Pin
    __delay_us(5);
    Enable_SetLow();
    __delay_us(375);
    measureAndSentADCReading(0); //read the integration value and send out
    __delay_ms(1);
    SPI_Write(0x04, 0x00); // disable the photo-amp, will put into RESET State
    __delay_ms(1); //allow time to switch back to CO for ABUF 
    measureAndSentADCReading(0); //take CO reading -WAK 08102018
}

/*
 * Function perform a 300uS integration on PA2
 */
void PA2_300us_Integration() {
    __delay_us(10); //first integration will be a dark - LED2En is low
    SPI_Write(0x04, 0x03); //enable the photo-amp, and set the Status bit to 1 - READY State
    __delay_us(150); //wait for internal photo amp 3v regulator to stabilize            
    Enable_SetHigh(); //start dark integration utilizing Enable Pin
    __delay_us(5);
    Enable_SetLow();
    __delay_us(375); //allow enough time for the integration with some slack
    measureAndSentADCReading(1); //read the integration value and send out
    SPI_Write(0x04, 0x11); //reset integration capacitors - RESET State
    __delay_us(10); //second integration will be a Lit - LED2En is high
    SPI_Write(0x04, 0x13); //enable the photo-amp, and set the Status bit to 1, enable LED2 - READY State
    __delay_us(10);
    Enable_SetHigh(); //start Lit integration utilizing Enable Pin
    __delay_us(5);
    Enable_SetLow();
    __delay_us(375);
    measureAndSentADCReading(1); //read the integration value and send out
    __delay_ms(1);
    SPI_Write(0x04, 0x00); // disable the photo-amp, will put into RESET State
    __delay_ms(1); //allow time to switch back to CO for ABUF 
    measureAndSentADCReading(1); //take CO reading -WAK 08102018
}

/*
 * Function perform a 400uS integration on PA1
 */
void PA1_400us_Integration() {
    __delay_us(10); //first integration will be a dark - LED1En is low
    SPI_Write(0x04, 0x03); //enable the photo-amp, and set the Status bit to 1 - READY State
    __delay_us(150); //wait for internal photo amp 3v regulator to stabilize            
    Enable_SetHigh(); //start dark integration utilizing Enable Pin
    __delay_us(5);
    Enable_SetLow();
    __delay_us(500); //allow enough time for the integration with some slack
    measureAndSentADCReading(0); //read the integration value and send out
    SPI_Write(0x04, 0x01); //reset integration capacitors - RESET State
    __delay_us(10); //second integration will be a Lit - LED1En is high
    SPI_Write(0x04, 0x0B); //enable the photo-amp, and set the Status bit to 1, enable LED1 - READY State
    __delay_us(10);
    Enable_SetHigh(); //start Lit integration utilizing Enable Pin
    __delay_us(5);
    Enable_SetLow();
    __delay_us(500);
    measureAndSentADCReading(0); //read the integration value and send out
    __delay_ms(1);
    SPI_Write(0x04, 0x00); // disable the photo-amp, will put into RESET State
    __delay_ms(1); //allow time to switch back to CO for ABUF 
    measureAndSentADCReading(0); //take CO reading -WAK 08102018
}

/*
 * Function perform a 400uS integration on PA2
 */
void PA2_400us_Integration() {
    __delay_us(10); //first integration will be a dark - LED2En is low
    SPI_Write(0x04, 0x03); //enable the photo-amp, and set the Status bit to 1 - READY State
    __delay_us(150); //wait for internal photo amp 3v regulator to stabilize            
    Enable_SetHigh(); //start dark integration utilizing Enable Pin
    __delay_us(5);
    Enable_SetLow();
    __delay_us(500); //allow enough time for the integration with some slack
    measureAndSentADCReading(1); //read the integration value and send out
    SPI_Write(0x04, 0x11); //reset integration capacitors - RESET State
    __delay_us(10); //second integration will be a Lit - LED2En is high
    SPI_Write(0x04, 0x13); //enable the photo-amp, and set the Status bit to 1, enable LED2 - READY State 
    __delay_us(10);
    Enable_SetHigh(); //start Lit integration utilizing Enable Pin
    __delay_us(5);
    Enable_SetLow();
    __delay_us(500);
    measureAndSentADCReading(1); //read the integration value and send out
    __delay_ms(1);
    SPI_Write(0x04, 0x00); // disable the photo-amp, will put into RESET State
    __delay_ms(1); //allow time to switch back to CO for ABUF 
    measureAndSentADCReading(1); //take CO reading -WAK 08102018
}

/*
 * function to take PA1 Settings and store away in variable for loop test(probably
 * could save a lot of this if I format the data in the GUI software).
 */
void CreatePA1Settings(uint8_t rxData) {
    switch (rxData) //determine which PA1, Gain setting, and integ. time
    {
        case (0x00): //100us integration time / Gain=1
            pa1reg6data = 0x80;
            break;

        case (0x01): //100us integration time / Gain=2
            pa1reg6data = 0x81;
            break;

        case (0x02): //100us integration time / Gain=4
            pa1reg6data = 0x82;
            break;

        case (0x03): //100us integration time / Gain=8
            pa1reg6data = 0x83;
            break;

        case (0x04): //100us integration time / Gain=16
            pa1reg6data = 0x84;
            break;

        case (0x05): //100us integration time / Gain=32
            pa1reg6data = 0x85;
            break;

        case (0x08): //200us integration time / Gain=1
            pa1reg6data = 0x90;
            break;

        case (0x09): //200us integration time / Gain=2
            pa1reg6data = 0x91;
            break;

        case (0x0A): //200us integration time / Gain=4
            pa1reg6data = 0x92;
            break;

        case (0x0B): //200us integration time / Gain=8
            pa1reg6data = 0x93;
            break;

        case (0x0C): //200us integration time / Gain=16
            pa1reg6data = 0x94;
            break;

        case (0x0D): //200us integration time / Gain=32
            pa1reg6data = 0x95;
            break;

        case (0x10): //300us integration time / Gain=1
            pa1reg6data = 0xA0;
            break;

        case (0x11): //300us integration time / Gain=2
            pa1reg6data = 0xA1;
            break;

        case (0x12): //300us integration time / Gain=4
            pa1reg6data = 0xA2;
            break;

        case (0x13): //300us integration time / Gain=8
            pa1reg6data = 0xA3;
            break;

        case (0x14): //300us integration time / Gain=16
            pa1reg6data = 0xA4;
            break;

        case (0x15): //300us integration time / Gain=32
            pa1reg6data = 0xA5;
            break;

        case (0x18): //400us integration time / Gain=1
            pa1reg6data = 0xB0;
            break;

        case (0x19): //400us integration time / Gain=2
            pa1reg6data = 0xB1;
            break;

        case (0x1A): //400us integration time / Gain=4
            pa1reg6data = 0xB2;
            break;

        case (0x1B): //400us integration time / Gain=8
            pa1reg6data = 0xB3;
            break;

        case (0x1C): //400us integration time / Gain=16
            pa1reg6data = 0xB4;
            break;

        case (0x1D): //400us integration time / Gain=32
            pa1reg6data = 0xB5;
            break;
    }
}

/*
 * function to take PA2 Settings and store away in variable for loop test (probably
 * could save a lot of this if I format the data in the GUI software).
 */
void CreatePA2Settings(uint8_t rxData) {
    switch (rxData) //determine which PA1, Gain setting, and integ. time
    {
        case (0x00): //100us integration time / Gain=1
            pa2reg6data = 0x80;
            break;

        case (0x01): //100us integration time / Gain=2
            pa2reg6data = 0x81;
            break;

        case (0x02): //100us integration time / Gain=4
            pa2reg6data = 0x82;
            break;

        case (0x03): //100us integration time / Gain=8
            pa2reg6data = 0x83;
            break;

        case (0x04): //100us integration time / Gain=16
            pa2reg6data = 0x84;
            break;

        case (0x05): //100us integration time / Gain=32
            pa2reg6data = 0x85;
            break;

        case (0x08): //200us integration time / Gain=1
            pa2reg6data = 0x90;
            break;

        case (0x09): //200us integration time / Gain=2
            pa2reg6data = 0x91;
            break;

        case (0x0A): //200us integration time / Gain=4
            pa2reg6data = 0x92;
            break;

        case (0x0B): //200us integration time / Gain=8
            pa2reg6data = 0x93;
            break;

        case (0x0C): //200us integration time / Gain=16
            pa2reg6data = 0x94;
            break;

        case (0x0D): //200us integration time / Gain=32
            pa2reg6data = 0x95;
            break;

        case (0x10): //300us integration time / Gain=1
            pa2reg6data = 0xA0;
            break;

        case (0x11): //300us integration time / Gain=2
            pa2reg6data = 0xA1;
            break;

        case (0x12): //300us integration time / Gain=4
            pa2reg6data = 0xA2;
            break;

        case (0x13): //300us integration time / Gain=8
            pa2reg6data = 0xA3;
            break;

        case (0x14): //300us integration time / Gain=16
            pa2reg6data = 0xA4;
            break;

        case (0x15): //300us integration time / Gain=32
            pa2reg6data = 0xA5;
            break;

        case (0x18): //400us integration time / Gain=1
            pa2reg6data = 0xB0;
            break;

        case (0x19): //400us integration time / Gain=2
            pa2reg6data = 0xB1;
            break;

        case (0x1A): //400us integration time / Gain=4
            pa2reg6data = 0xB2;
            break;

        case (0x1B): //400us integration time / Gain=8
            pa2reg6data = 0xB3;
            break;

        case (0x1C): //400us integration time / Gain=16
            pa2reg6data = 0xB4;
            break;

        case (0x1D): //400us integration time / Gain=32
            pa2reg6data = 0xB5;
            break;
    }
}

/*
 * function to perform a functional photo integration, based upon PA 
 * selection, as well as the integration time selected and gain selected. 
 * Assumes Internal timing control.
 */
void Photo_Integrate(uint8_t rxData) {
#if PHOTO_AMP_OUT_TO_ABUF_CTRL == 1u
    uint8_t EnBuf = 0x80u; // ABUF = Vint
#else
    uint8_t EnBuf = 0x00;  // ABUF = Hold
#endif /* PHOTO_AMP_OUT_TO_ABUF_CTRL */
    SPI_Write(0x02, 0x05); //charges the IRCAP, low boost mode
    __delay_ms(8);//(20);
    SPI_Write(0x02, 0x00); //stop charging IRCAP

    switch (rxData) //determine which PA, Gain setting, and integ. time
    {
        case (0x00): //PA1 / 100us integration time / Gain=1
            SPI_Write(0x0C, 0x00 | EnBuf); //Internal timing, 100us, ABUF=Vint, Gain=1
            PA1_100us_Integration(); //Start detection   
            break;

        case (0x01): //PA1 / 100us integration time / Gain=2
            SPI_Write(0x0C, 0x01 | EnBuf); //Internal timing, 100us, Gain=2
            PA1_100us_Integration(); //Start detection
            break;

        case (0x02): //PA1 / 100us integration time / Gain=4
            SPI_Write(0x0C, 0x02 | EnBuf); //Internal timing, 100us, Gain=4
            PA1_100us_Integration(); //Start detection
            break;

        case (0x03): //PA1 / 100us integration time / Gain=8
            SPI_Write(0x0C, 0x03 | EnBuf); //Internal timing, 100us, Gain=8
            PA1_100us_Integration(); //Start detection
            break;

        case (0x04): //PA1 / 100us integration time / Gain=16
            SPI_Write(0x0C, 0x04 | EnBuf); //Internal timing, 100us, Gain=16
            PA1_100us_Integration(); //Start detection
            break;

        case (0x05): //PA1 / 100us integration time / Gain=32
            SPI_Write(0x0C, 0x05 | EnBuf);  //Internal timing, 100us, ABUF=Hold, Gain=32
            PA1_100us_Integration(); //Start detection
            break;

        case (0x08): //PA1 / 200us integration time / Gain=1
            SPI_Write(0x0C, 0x10 | EnBuf); //Internal timing, 200us, Gain=1
            PA1_200us_Integration(); //Start detection
            break;

        case (0x09): //PA1 / 200us integration time / Gain=2
            SPI_Write(0x0C, 0x11 | EnBuf); //Internal timing, 200us, Gain=2
            PA1_200us_Integration(); //Start detection                
            break;

        case (0x0A): //PA1 / 200us integration time / Gain=4
            SPI_Write(0x0C, 0x12 | EnBuf); //Internal timing, 200us, Gain=4
            PA1_200us_Integration(); //Start detection                
            break;

        case (0x0B): //PA1 / 200us integration time / Gain=8
            SPI_Write(0x0C, 0x13 | EnBuf); //Internal timing, 200us, Gain=8
            PA1_200us_Integration(); //Start detection
            break;

        case (0x0C): //PA1 / 200us integration time / Gain=16
            SPI_Write(0x0C, 0x14 | EnBuf); //Internal timing, 200us, Gain=16
            PA1_200us_Integration(); //Start detection
            break;

        case (0x0D): //PA1 / 200us integration time / Gain=32
            SPI_Write(0x0C, 0x15 | EnBuf); //Internal timing, 200us, Gain=32
            PA1_200us_Integration(); //Start detection
            break;

        case (0x10): //PA1 / 300us integration time / Gain=1
            SPI_Write(0x0C, 0x20 | EnBuf); //Internal timing, 300us, Gain=1
            PA1_300us_Integration(); //Start detection
            break;

        case (0x11): //PA1 / 300us integration time / Gain=2
            SPI_Write(0x0C, 0x21 | EnBuf); //Internal timing, 300us, Gain=2
            PA1_300us_Integration(); //Start detection
            break;

        case (0x12): //PA1 / 300us integration time / Gain=4
            SPI_Write(0x0C, 0x22 | EnBuf); //Internal timing, 300us, Gain=4
            PA1_300us_Integration(); //Start detection
            break;

        case (0x13): //PA1 / 300us integration time / Gain=8
            SPI_Write(0x0C, 0x23 | EnBuf); //Internal timing, 300us, Gain=8
            PA1_300us_Integration(); //Start detection
            break;

        case (0x14): //PA1 / 300us integration time / Gain=16
            SPI_Write(0x0C, 0x24 | EnBuf); //Internal timing, 300us, Gain=16
            PA1_300us_Integration(); //Start detection
            break;

        case (0x15): //PA1 / 300us integration time / Gain=32
            SPI_Write(0x0C, 0x25 | EnBuf); //Internal timing, 300us, Gain=32
            PA1_300us_Integration(); //Start detection
            break;

        case (0x18): //PA1 / 400us integration time / Gain=1
            SPI_Write(0x0C, 0x30 | EnBuf); //Internal timing, 400us, Gain=1
            PA1_400us_Integration(); //Start detection
            break;

        case (0x19): //PA1 / 400us integration time / Gain=2
            SPI_Write(0x0C, 0x31 | EnBuf); //Internal timing, 400us, Gain=2
            PA1_400us_Integration(); //Start detection
            break;

        case (0x1A): //PA1 / 400us integration time / Gain=4
            SPI_Write(0x0C, 0x32 | EnBuf); //Internal timing, 400us, Gain=4
            PA1_400us_Integration(); //Start detection
            break;

        case (0x1B): //PA1 / 400us integration time / Gain=8
            SPI_Write(0x0C, 0x33 | EnBuf); //Internal timing, 400us, Gain=8
            PA1_400us_Integration(); //Start detection
            break;

        case (0x1C): //PA1 / 400us integration time / Gain=16
            SPI_Write(0x0C, 0x34 | EnBuf); //Internal timing, 400us, Gain=16
            PA1_400us_Integration(); //Start detection
            break;

        case (0x1D): //PA1 / 400us integration time / Gain=32
            SPI_Write(0x0C, 0x35 | EnBuf); //Internal timing, 400us, Gain=32
            PA1_400us_Integration(); //Start detection
            break;

        case (0x20): //PA2 / 100us integration time / Gain=1
            SPI_Write(0x0C, 0x00 | EnBuf); //Internal timing, 100us, Gain=1
            PA2_100us_Integration(); //Start detection
            break;

        case (0x21): //PA2 / 100us integration time / Gain=2
            SPI_Write(0x0C, 0x01 | EnBuf); //Internal timing, 100us, Gain=2
            PA2_100us_Integration(); //Start detection
            break;

        case (0x22): //PA2 / 100us integration time / Gain=4
            SPI_Write(0x0C, 0x02 | EnBuf); //Internal timing, 100us, Gain=4
            PA2_100us_Integration(); //Start detection
            break;

        case (0x23): //PA2 / 100us integration time / Gain=8
            SPI_Write(0x0C, 0x03 | EnBuf); //Internal timing, 100us, Gain=8
            PA2_100us_Integration(); //Start detection
            break;

        case (0x24): //PA2 / 100us integration time / Gain=16
            SPI_Write(0x0C, 0x04 | EnBuf);  //Internal timing, 100us, Gain=16
            PA2_100us_Integration(); //Start detection
            break;

        case (0x25): //PA2 / 100us integration time / Gain=32
            SPI_Write(0x0C, 0x05 | EnBuf); //Internal timing, 100us, Gain=32
            PA2_100us_Integration(); //Start detection
            break;

        case (0x28): //PA2 / 200us integration time / Gain=1
            SPI_Write(0x0C, 0x10 | EnBuf); //Internal timing, 200us, Gain=1
            PA2_200us_Integration(); //Start detection
            break;

        case (0x29): //PA2 / 200us integration time / Gain=2
            SPI_Write(0x0C, 0x11 | EnBuf); //Internal timing, 200us, Gain=2
            PA2_200us_Integration(); //Start detection
            break;

        case (0x2A): //PA2 / 200us integration time / Gain=4
            SPI_Write(0x0C, 0x12 | EnBuf); //Internal timing, 200us, Gain=4
            PA2_200us_Integration(); //Start detection
            break;

        case (0x2B): //PA2 / 200us integration time / Gain=8
            SPI_Write(0x0C, 0x13 | EnBuf); //Internal timing, 200us, Gain=8
            PA2_200us_Integration(); //Start detection
            break;

        case (0x2C): //PA2 / 200us integration time / Gain=16
            SPI_Write(0x0C, 0x14 | EnBuf); //Internal timing, 200us, Gain=16
            PA2_200us_Integration(); //Start detection
            break;

        case (0x2D): //PA2 / 200us integration time / Gain=32
            SPI_Write(0x0C, 0x15 | EnBuf); //Internal timing, 200us, Gain=32
            PA2_200us_Integration(); //Start detection
            break;

        case (0x30): //PA2 / 300us integration time / Gain=1
            SPI_Write(0x0C, 0x20 | EnBuf); //Internal timing, 300us, Gain=1
            PA2_300us_Integration(); //Start detection
            break;

        case (0x31): //PA2 / 300us integration time / Gain=2
            SPI_Write(0x0C, 0x21 | EnBuf); //Internal timing, 300us, Gain=2
            PA2_300us_Integration(); //Start detection
            break;

        case (0x32): //PA2 / 300us integration time / Gain=4
            SPI_Write(0x0C, 0x22 | EnBuf); //Internal timing, 300us,, Gain=4
            PA2_300us_Integration(); //Start detection
            break;

        case (0x33): //PA2 / 300us integration time / Gain=8
            SPI_Write(0x0C, 0x23 | EnBuf); //Internal timing, 300us, Gain=8
            PA2_300us_Integration(); //Start detection
            break;

        case (0x34): //PA2 / 300us integration time / Gain=16
            SPI_Write(0x0C, 0x24 | EnBuf); //Internal timing, 300us, Gain=16
            PA2_300us_Integration(); //Start detection
            break;

        case (0x35): //PA2 / 300us integration time / Gain=32
            SPI_Write(0x0C, 0x25 | EnBuf); //Internal timing, 300us, Gain=32
            PA2_300us_Integration(); //Start detection
            break;

        case (0x38): //PA2 / 400us integration time / Gain=1
            SPI_Write(0x0C, 0x30 | EnBuf); //Internal timing, 400us, Gain=1
            PA2_400us_Integration(); //Start detection
            break;

        case (0x39): //PA2 / 400us integration time / Gain=2
            SPI_Write(0x0C, 0x31 | EnBuf); //Internal timing, 400us, Gain=2
            PA2_400us_Integration(); //Start detection
            break;

        case (0x3A): //PA2 / 400us integration time / Gain=4
            SPI_Write(0x0C, 0x32 | EnBuf); //Internal timing, 400us, Gain=4
            PA2_400us_Integration(); //Start detection
            break;

        case (0x3B): //PA2 / 400us integration time / Gain=8
            SPI_Write(0x0C, 0x33 | EnBuf); //Internal timing, 400us, Gain=8
            PA2_400us_Integration(); //Start detection
            break;

        case (0x3C): //PA2 / 400us integration time / Gain=16
            SPI_Write(0x0C, 0x34 | EnBuf); //Internal timing, 400us, Gain=16
            PA2_400us_Integration(); //Start detection
            break;

        case (0x3D): //PA2 / 400us integration time / Gain=32
            SPI_Write(0x0C, 0x35 | EnBuf); //Internal timing, 400us, Gain=32
            PA2_400us_Integration(); //Start detection
            break;
    }
}


/*
 *
 */
void RunLoopTest(uint8_t rxData)
{
    /*Set up and run PA1*/
        SPI_Write(0x02,0x05);           //charges the IRCAP, low boost mode
        __delay_ms(20);
        SPI_Write(0x02,0x00);           //stop charging IRCAP
        
        SPI_Write(0x0C, pa1reg6data);   //similar to method Photo_Integrate write setup data to reg 6
        
        integ1Time = pa1reg6data>>4;    //shift the register 6 bits so just the integration time
                                        //bits are left, put them into var. for decision making below
        
        //SPI_Write(0x0C, pa1reg6data);   //similar to method Photo_Integrate write setup data to reg 6
        if (integ1Time == 8)            //determine which integration time method to use 
            PA1_100us_Integration();
        else if (integ1Time == 9)
            PA1_200us_Integration();
        else if (integ1Time == 0xA)
            PA1_300us_Integration();
        else if (integ1Time == 0xB)
            PA1_400us_Integration();
        
        __delay_ms(100);
        
        /*Set up and run PA2*/
        SPI_Write(0x02,0x05);           //charges the IRCAP, low boost mode
        __delay_ms(20);
        SPI_Write(0x02,0x00);           //stop charging IRCAP
        
        SPI_Write(0x0C, pa2reg6data);  //
        
        integ2Time = pa2reg6data>>4;
        
        //SPI_Write(0x0C, pa2reg6data);  //
        if (integ2Time == 8)
            PA2_100us_Integration();
        else if (integ2Time == 9)
            PA2_200us_Integration();
        else if (integ2Time == 0xA)
            PA2_300us_Integration();
        else if (integ2Time == 0xB)
            PA2_400us_Integration();
    }
    

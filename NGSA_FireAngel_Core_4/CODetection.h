/* 
 * File:   CODetection.h
 * Author: pstarzyk
 *
 * Created on 15 April 2021, 12:59
 */

#ifndef CODETECTION_H
#define	CODETECTION_H

#ifdef	__cplusplus
extern "C" {
#endif

void initCODetection(void);
uint16_t readCO(void);

uint16_t RunCOTest(void);

void SendCOPattern(uint8_t rxData);
void EnableCO(void);
void DisableCO(void);
void EnableCOPolar(uint8_t rxData);
void DisableCOPolar(uint8_t rxData);
extern void __delay_ms(uint16_t time_ms_val);
extern void SPI_Write(uint8_t add , uint8_t data);

#ifdef	__cplusplus
}
#endif

#endif	/* CODETECTION_H */


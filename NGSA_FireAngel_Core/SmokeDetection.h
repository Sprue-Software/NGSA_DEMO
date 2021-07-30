/* 
 * File:   SmokeDetection.h
 * Author: pstarzyk
 *
 * Created on 15 April 2021, 12:03
 */

#ifndef SMOKEDETECTION_H
#define	SMOKEDETECTION_H

#ifdef	__cplusplus
extern "C" {
#endif

extern uint8_t pa1reg6data;
extern uint8_t pa2reg6data;
extern uint8_t integ1Time;
extern uint8_t integ2Time;

void Photo_Integrate(uint8_t rxData);
void RunLoopTest(uint8_t rxData);
void CreatePA1Settings(uint8_t rxData);
void CreatePA2Settings(uint8_t rxData);
extern void __delay_us(uint16_t time_us_val);

#ifdef	__cplusplus
}
#endif

#endif	/* SMOKEDETECTION_H */


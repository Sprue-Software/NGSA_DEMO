/* 
 * File:   HeartBeatTests.h
 * Author: pstarzyk
 *
 * Created on 13 April 2021, 10:57
 */

#ifndef HEARTBEATTESTS_H
#define	HEARTBEATTESTS_H


#ifdef	__cplusplus
extern "C" {
#endif

void HeartBeatContBlink(uint16_t no_of_blinks);
extern void HeartBeatOn(void);
extern void HeartBeatOff(void);
extern void SPI_Write(uint8_t add , uint8_t data);
#ifdef	__cplusplus
}
#endif

#endif	/* HEARTBEATTESTS_H */


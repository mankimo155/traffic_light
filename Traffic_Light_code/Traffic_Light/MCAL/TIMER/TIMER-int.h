/*
 * TIMER-int.h
 *
 *  Created on: Aug 3, 2023
 *      Author: userH
 */

#ifndef MCAL_TIMER_TIMER_INT_H_
#define MCAL_TIMER_TIMER_INT_H_

#define TIM_CB_OVF		0
#define TIM_CB_CTC		1

#define TIM_mode_OVF        0
#define TIM_mode_CTC        1
#define TIM_mode_ICU        2

#define ISR_DISABLE 0
#define ISR_OVF     1
#define ISR_CTC     2
#define ISR_ICU     3

#define TIMER0			0
#define u16TIMER1	    1
#define TIMER2			2

typedef enum
{
	ICU_Falling,
	ICU_Rising
}ICU_Trigger_t;

void MTIMERS_vInit(void);

void MTIMERS_SetTimerOvfCounter(u8 A_u8TimerId,u16 A_u16IntervalCounts);

void MTIMERS_vSetPreloadValue(u8 A_u8TimerId , u16 A_u16Preload);

void MTIMERS_vSetCompareValue(u8 A_u8TimerId , u16 A_u16CompareValue);

void MTIMERS_vSetInterval_Asynch(u8 A_u8TimerId,u16 A_u16IntervalCounts, void (*A_fptr)(void));

void MTIMERS_vSetInterval_CTC_Asynch(u8 A_u8TimerId,u16 A_u16IntervalCounts,
									u16 A_u16CompareValue,
								      void (*A_fptr)(void));

u16  MTIMERS_u16GetElapsedTime(u8 A_u8TimerId);
u16  MTIMERS_u16GetCapturedValue(void);
void MTIMERS_vSetIcuTrigger(ICU_Trigger_t A_xIcuTrigger);
void MTIMERS_vIsrFeatuer(u8 A_u8TimerId, u8 A_u8InterruptType);

void MTIMERS_vSetCallback( u8 A_u8TimerId,u8 A_u8TimerMode,void (*A_xFptr)(void));


void MTIMERS_vStartTimer(u8 A_u8TimerId) ;

void MTIMERS_vStopTimer(u8 A_u8TimerId) ;


#endif /* MCAL_TIMER_TIMER_INT_H_ */

/*
 * TIMER-pro.c
 *
 *  Created on: Aug 3, 2023
 *      Author: userH
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "TIMER-int.h"
#include "TIMER-prv.h"
#include "TIMER-cfg.h"

static u32 LS_u32Counter0 = 0;
static u32 LS_u32Counter2 = 0;


static void (*G_TIM0_OVF_Callback)(void);
static void (*G_TIM0_CTC_Callback)(void);
static void (*G_TIM2_OVF_Callback)(void);
static void (*G_TIM2_CTC_Callback)(void);
static void (*G_TIMu16_OVF_Callback)(void);
static void (*G_TIMu16_CTC_Callback)(void);
static void (*G_TIMu16_ICU_Callback)(void);
//static void (*G_TIM0_Callback[2])(void);

u32  G_u32IntervalCount = 1;
u32  G_u32IntervalCount2 = 1;

void MTIMERS_vInit(void)
{
	/**
	 * Mode: Normal Overflow
	 * Interrupt: enable OVerflow intterupt
	 * Prescaler: No CLOCK -> timer stopped
	 */
#if TIMER0_ENABLE==ENABLE
	/*1- Wave Generation Mode */
#if TIMER0_MODE==TIMER_OVF
	CLR_BIT(TCCR0,WGM01);
	CLR_BIT(TCCR0,WGM00);
#elif TIMER0_MODE==TIMER_CTC
	SET_BIT(TCCR0,WGM01);
	CLR_BIT(TCCR0,WGM00);
#if TIMER0_OC0_MODE==OC_DISABLE
	CLR_BIT(TCCR0,COM00);
	CLR_BIT(TCCR0,COM01);
#elif	TIMER0_OC0_MODE==OC_TOGGLE
	SET_BIT(TCCR0,COM00);
	CLR_BIT(TCCR0,COM01);
#elif	TIMER0_OC0_MODE==OC_CLEAR
	CLR_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
#elif	TIMER0_OC0_MODE==OC_SET
	SET_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
#else
#error "Please select a valid Timer Mode"
#endif
#elif TIMER0_MODE==TIMER_FASTPWM
	SET_BIT(TCCR0,WGM01);
	SET_BIT(TCCR0,WGM00);
#if TIMER0_OC0_MODE == OC_DISABLE
	CLR_BIT(TCCR0,COM00);
	CLR_BIT(TCCR0,COM01);
#elif	TIMER0_OC0_MODE==OC_CLEAR
	CLR_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
#elif	TIMER0_OC0_MODE==OC_SET
	SET_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
#else
#error "Please select a valid Timer Mode"
#endif
#elif TIMER0_MODE==TIMER_PHASECORRECT
	CLR_BIT(TCCR0,WGM01);
	SET_BIT(TCCR0,WGM00);
#if TIMER0_OC0_MODE==OC_DISABLE
	CLR_BIT(TCCR0,COM00);
	CLR_BIT(TCCR0,COM01);
#elif	TIMER0_OC0_MODE==OC_CLEAR
	CLR_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
#elif	TIMER0_OC0_MODE==OC_SET
	SET_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
#else
#error "Please select a valid Timer Mode"
#endif
#else
#error "Please select a valid Timer Mode"
#endif
#endif

#if u16TIMER1_ENABLE==ENABLE
	TCCR1A = 0b10000000;
	TCCR1B = 0b01000010;
	ICR1 = 625;

#endif

#if TIMER2_ENABLE==ENABLE
	/*1- Wave Generation Mode */
#if TIMER2_MODE==TIMER_OVF
	CLR_BIT(TCCR2,WGM21);
	CLR_BIT(TCCR2,WGM20);
#elif TIMER2_MODE==TIMER_CTC
	SET_BIT(TCCR2,WGM21);
	CLR_BIT(TCCR2,WGM20);
#if TIMER2_OC2_MODE == OC_DISABLE
	CLR_BIT(TCCR2,COM20);
	CLR_BIT(TCCR2,COM21);
#elif	TIMER2_OC2_MODE==OC_TOGGLE
	SET_BIT(TCCR2,COM20);
	CLR_BIT(TCCR2,COM21);
#elif	TIMER2_OC2_MODE==OC_CLEAR
	CLR_BIT(TCCR2,COM20);
	SET_BIT(TCCR2,COM21);
#elif	TIMER2_OC2_MODE==OC_SET
	SET_BIT(TCCR2,COM20);
	SET_BIT(TCCR2,COM21);
#else
#error "Please select a valid Timer Mode"
#endif
#elif TIMER2_MODE==TIMER_FASTPWM
	SET_BIT(TCCR2,WGM21);
	SET_BIT(TCCR2,WGM20);
#if TIMER2_OC2_MODE == OC_DISABLE
	CLR_BIT(TCCR2,COM20);
	CLR_BIT(TCCR2,COM21);
#elif	TIMER2_OC2_MODE==OC_CLEAR
	CLR_BIT(TCCR2,COM20);
	SET_BIT(TCCR2,COM21);
#elif	TIMER2_OC2_MODE==OC_SET
	SET_BIT(TCCR2,COM20);
	SET_BIT(TCCR2,COM21);
#else
#error "Please select a valid Timer Mode"
#endif
#elif TIMER2_MODE==TIMER_PHASECORRECT
	CLR_BIT(TCCR2,WGM21);
	SET_BIT(TCCR2,WGM20);
#if TIMER2_OC2_MODE == OC_DISABLE
	CLR_BIT(TCCR2,COM10);
	CLR_BIT(TCCR2,COM21);
#elif	TIMER2_OC2_MODE==OC_CLEAR
	CLR_BIT(TCCR2,COM20);
	SET_BIT(TCCR2,COM21);
#elif	TIMER2_OC2_MODE==OC_SET
	SET_BIT(TCCR2,COM20);
	SET_BIT(TCCR2,COM21);
#else
#error "Please select a valid Timer Mode"
#endif
#else
#error "Please select a valid Timer Mode"
#endif
#endif

}

u16  MTIMERS_u16GetCapturedValue(void)
{
	return ICR1;
}

void MTIMERS_SetTimerOvfCounter(u8 A_u8TimerId,u16 A_u16IntervalCounts)
{
	switch(A_u8TimerId)
	{
	case TIMER0:
		G_u32IntervalCount = A_u16IntervalCounts;
		LS_u32Counter0 = 0;
		break;
	case TIMER2:
		G_u32IntervalCount2 = A_u16IntervalCounts;
		LS_u32Counter2 = 0;
		break;
	}

}


void MTIMERS_vSetIcuTrigger(ICU_Trigger_t A_xIcuTrigger)
{
	switch(A_xIcuTrigger)
	{
	case ICU_Falling:
		CLR_BIT(TCCR1B,6);
		break;
	case ICU_Rising:
		SET_BIT(TCCR1B,6);
		break;
	}

}


void MTIMERS_vIsrFeatuer(u8 A_u8TimerId, u8 A_u8InterruptType)
{
	switch(A_u8TimerId)
	{
	case TIMER0 :
		switch(A_u8InterruptType)
		{
		case ISR_DISABLE:
			CLR_BIT(TIMSK,TOIE0);
			CLR_BIT(TIMSK,OCIE0);
			break;
		case ISR_OVF :
			SET_BIT(TIMSK,TOIE0);
			CLR_BIT(TIMSK,OCIE0);
			break;
		case ISR_CTC:
			CLR_BIT(TIMSK,TOIE0);
			SET_BIT(TIMSK,OCIE0);
			break;
		}
		break;
		case u16TIMER1 :
			switch(A_u8InterruptType)
			{
			case ISR_DISABLE:
				CLR_BIT(TIMSK,TICIE1);
				CLR_BIT(TIMSK,OCIE1A);
				CLR_BIT(TIMSK,OCIE1B);
				CLR_BIT(TIMSK,TOIE1);
				break;
			case ISR_OVF :
				CLR_BIT(TIMSK,TICIE1);
				CLR_BIT(TIMSK,OCIE1A);
				CLR_BIT(TIMSK,OCIE1B);
				SET_BIT(TIMSK,TOIE1);
				break;
			case ISR_CTC:
				CLR_BIT(TIMSK,TICIE1);
				SET_BIT(TIMSK,OCIE1A);
				CLR_BIT(TIMSK,OCIE1B);
				CLR_BIT(TIMSK,TOIE1);
				break;
			case ISR_ICU :
				SET_BIT(TIMSK,TICIE1);
				CLR_BIT(TIMSK,OCIE1A);
				CLR_BIT(TIMSK,OCIE1B);
				CLR_BIT(TIMSK,TOIE1);
				break;
			}
			break;
			case TIMER2 :
				switch(A_u8InterruptType)
				{
				case ISR_DISABLE:
					CLR_BIT(TIMSK,TOIE2);
					CLR_BIT(TIMSK,OCIE2);
					break;
				case ISR_OVF :
					SET_BIT(TIMSK,TOIE2);
					CLR_BIT(TIMSK,OCIE2);
					break;
				case ISR_CTC:
					CLR_BIT(TIMSK,TOIE2);
					SET_BIT(TIMSK,OCIE2);
					break;
				}
				break;
	}
}


void MTIMERS_vSetCallback( u8 A_u8TimerId,u8 A_u8TimerMode,void (*A_xFptr)(void))
{
	switch(A_u8TimerId)
	{
	case TIMER0 :
		if(A_u8TimerMode==TIM_mode_OVF)
		{
			G_TIM0_OVF_Callback=A_xFptr;
		}
		else if(A_u8TimerMode==TIM_mode_CTC)
		{
			G_TIM0_CTC_Callback=A_xFptr;
		}
		else
		{/*do do eny sing*/}
		break;
	case u16TIMER1:
		if(A_u8TimerMode==TIM_mode_OVF)
		{
			G_TIMu16_OVF_Callback=A_xFptr;
		}
		else if(A_u8TimerMode==TIM_mode_CTC)
		{
			G_TIMu16_CTC_Callback=A_xFptr;
		}
		else if(A_u8TimerMode==TIM_mode_ICU)
		{
			G_TIMu16_ICU_Callback=A_xFptr;
		}
		else
		{
			/*no thing*/
		}
		break;
	case TIMER2:
		if(A_u8TimerMode==TIM_mode_OVF)
		{
			G_TIM2_OVF_Callback=A_xFptr;
		}
		else if(A_u8TimerMode==TIM_mode_CTC)
		{
			G_TIM2_CTC_Callback=A_xFptr;
		}
		else
		{/*do do eny sing*/}
		break;
	}

}



void MTIMERS_vSetPreloadValue(u8 A_u8TimerId , u16 A_u16Preload)
{
	switch(A_u8TimerId)
	{
	case TIMER0:
		TCNT0 = A_u16Preload ;
		break;
	case u16TIMER1:
		TCNT1 = A_u16Preload ;
		break;
	case TIMER2:
		TCNT2 = A_u16Preload ;
		break;
	}

}

void MTIMERS_vSetCompareValue(u8 A_u8TimerId ,u16 A_u16CompareValue)
{
	switch(A_u8TimerId)
	{
	case TIMER0:
		OCR0 = A_u16CompareValue ;
		break;
	case u16TIMER1:
		OCR1A = A_u16CompareValue ;
		break;
	case TIMER2:
		OCR2 = A_u16CompareValue ;
		break;
	}
}

void MTIMERS_vSetInterval_Asynch(u8 A_u8TimerId,u16 A_u16IntervalCounts, void (*A_fptr)(void))
{
	switch(A_u8TimerId)
	{
	case TIMER0:
		G_u32IntervalCount = A_u16IntervalCounts ;
		G_TIM0_OVF_Callback = A_fptr ;
		MTIMERS_vStartTimer(A_u8TimerId);
		break;
	case u16TIMER1:
		G_u32IntervalCount = A_u16IntervalCounts ;
		G_TIMu16_OVF_Callback = A_fptr ;
		MTIMERS_vStartTimer(A_u8TimerId);
		break;
	case TIMER2:
		G_u32IntervalCount2 = A_u16IntervalCounts ;
		G_TIM2_OVF_Callback = A_fptr ;
		MTIMERS_vStartTimer(A_u8TimerId);
		break;

	}
}

void MTIMERS_vSetInterval_CTC_Asynch(u8 A_u8TimerId,u16 A_u16IntervalCounts,
		u16 A_u16CompareValue,
		void (*A_fptr)(void))
{
	switch(A_u8TimerId)
	{
	case TIMER0 :
		G_u32IntervalCount = A_u16IntervalCounts ;
		G_TIM0_CTC_Callback = A_fptr ;
		MTIMERS_vSetCompareValue(A_u8TimerId,A_u16CompareValue);
		MTIMERS_vStartTimer(A_u8TimerId);
		break;
	case u16TIMER1 :
		G_u32IntervalCount = A_u16IntervalCounts ;
		G_TIMu16_CTC_Callback = A_fptr ;
		MTIMERS_vSetCompareValue(A_u8TimerId,A_u16CompareValue);
		MTIMERS_vStartTimer(A_u8TimerId);
		break;
	case TIMER2 :
		G_u32IntervalCount2 = A_u16IntervalCounts ;
		G_TIM2_CTC_Callback = A_fptr ;
		MTIMERS_vSetCompareValue(A_u8TimerId,A_u16CompareValue);
		MTIMERS_vStartTimer(A_u8TimerId);
		break;
	}
}

u16  MTIMERS_u16GetElapsedTime(u8 A_u8TimerId)
{
	u16 L_u16TimeValue=0;
	switch(A_u8TimerId)
	{
	case TIMER0 :
		L_u16TimeValue = TCNT0;
		break;
	case u16TIMER1 :
		L_u16TimeValue = TCNT1;
		break;
	case TIMER2 :
		L_u16TimeValue = TCNT2;
		break;
	}
	return L_u16TimeValue;

}

void MTIMERS_vStartTimer(u8 A_u8TimerId)
{
	switch(A_u8TimerId)
	{
	case TIMER0 :
		TCCR0 = (TCCR0 & 0xF8) | (TIMER_PRESCALER) ;
		break;
	case u16TIMER1 :
		TCCR1B = (TCCR1B & 0xF8) | (TIMER_PRESCALER) ;
		break;
	case TIMER2 :
		TCCR2 = (TCCR2 & 0xF8) | (TIMER_PRESCALER) ;
		break;
	}
}

void MTIMERS_vStopTimer(u8 A_u8TimerId)
{
	switch(A_u8TimerId)
	{
	case TIMER0 :
		TCCR0 = (TCCR0 & 0xF8) | (TIMER_DISABLE);
		break;
	case u16TIMER1 :
		TCCR1B = (TCCR0 & 0xF8) | (TIMER_DISABLE);
		break;
	case TIMER2 :
		TCCR2 = (TCCR2 & 0xF8) | (TIMER_DISABLE);
		break;
	}
}

/* Timer 0 Overflow ISR */
void __vector_11(void)  __attribute__((signal));
void __vector_11(void)
{


	LS_u32Counter0++ ;

	if(LS_u32Counter0 == G_u32IntervalCount)
	{
		if(G_TIM0_OVF_Callback != NULL)
		{
			G_TIM0_OVF_Callback();
			LS_u32Counter0 = 0;
		}
	}
}

/* Timer 0 CTC ISR */
void __vector_10(void) __attribute__((signal))  ;
void __vector_10(void)
{
	static u32 LS_u32Counter = 0;

	LS_u32Counter++ ;

	if(LS_u32Counter == G_u32IntervalCount)
	{
		if(G_TIM0_CTC_Callback != NULL)
		{
			G_TIM0_CTC_Callback();
			LS_u32Counter = 0;
		}
	}
}


/* Timer 2 Overflow ISR */
void __vector_5(void)  __attribute__((signal));
void __vector_5(void)
{


	LS_u32Counter2++ ;

	if(LS_u32Counter2 == G_u32IntervalCount2)
	{
		if(G_TIM2_OVF_Callback != NULL)
		{
			G_TIM2_OVF_Callback();
			LS_u32Counter2 = 0;
		}
	}
}

/* Timer 2 CTC ISR */
void __vector_4(void) __attribute__((signal))  ;
void __vector_4(void)
{
	static u32 LS_u32Counter = 0;

	LS_u32Counter++ ;

	if(LS_u32Counter == G_u32IntervalCount2)
	{
		if(G_TIM2_CTC_Callback != NULL)
		{
			G_TIM2_CTC_Callback();
			LS_u32Counter = 0;
		}
	}
}

/* u16Timer1  CTC ISR */
void __vector_6(void) __attribute__((signal))  ;
void __vector_6(void)
{
	G_TIMu16_ICU_Callback();
}








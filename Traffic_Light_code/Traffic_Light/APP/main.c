/*
 * main.c
 *
 *  Created on: Sep 23, 2023
 *      Author: userH
 */
#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/GIE/GIE_int.h"
#include "../MCAL/EXTI/EXTI-int.h"
#include "../MCAL/TIMER/TIMER-int.h"
#include "util/delay.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void Yellow_Car_Blink(void);
void Green_Car(void);
void Red_Car(void);
void Yellow_passenger_Blink(void);
void Red_passenger(void);
void Green_passenger(void);
void StopPassengerTrifficLight(void);


#define LED_YELLOW    1
#define LED_RED       2
#define LED_GREEN     3
#define ENABLE        1
#define DISEBLE       0

volatile static u8 GS_u8ISRFlag = 0 ;
volatile static u8 GS_u8CarCounter = 0 ;
volatile static u8 GS_u8PassengerCounter = 0 ;
volatile static u8 GS_u8CarFlag = 0 ;
volatile static u8 GS_u8TypeOFLEDon = 0 ;
volatile static u8 GS_u8CaseOneFlag = 0 ;






void StopPassengerTrifficLight(void)
{

	MEXTI_vEnableInterrupt(EXTI_INT0);
	MDIO_vSetPortVal(DIO_PORTB,0);
	MTIMERS_vStopTimer(TIMER2);


}
void Yellow_Car_Blink(void)
{
	MTIMERS_SetTimerOvfCounter(TIMER0,500);
	GS_u8CarCounter++;
	MDIO_vSetPinVal(DIO_PORTA,DIO_PIN2,DIO_LOW);
	MDIO_vSetPinVal(DIO_PORTA,DIO_PIN0,DIO_LOW);
	MDIO_vTogPinVal(DIO_PORTA,DIO_PIN1);
	if(GS_u8CarCounter == 40)
	{
		if(GS_u8TypeOFLEDon==LED_GREEN)
		{
			MTIMERS_vSetCallback(TIMER0,TIM_mode_OVF,Red_Car);
			MTIMERS_SetTimerOvfCounter(TIMER0,1);
		}
		else if(GS_u8TypeOFLEDon==LED_RED)
		{
			MTIMERS_vSetCallback(TIMER0,TIM_mode_OVF,Green_Car);
			MTIMERS_SetTimerOvfCounter(TIMER0,1);
		}
		GS_u8CarCounter=0;
	}
	GS_u8CarFlag=LED_YELLOW;
}

void Green_Car(void)
{

	MTIMERS_SetTimerOvfCounter(TIMER0,19532);
	MTIMERS_vSetCallback(TIMER0,TIM_mode_OVF,Yellow_Car_Blink);
	MDIO_vSetPinVal(DIO_PORTA,DIO_PIN1,DIO_LOW);
	MDIO_vSetPinVal(DIO_PORTA,DIO_PIN2,DIO_HIGH);
	GS_u8CarFlag=LED_GREEN;
	GS_u8TypeOFLEDon=LED_GREEN;

}

void Red_Car(void)
{

	MTIMERS_SetTimerOvfCounter(TIMER0,19532);
	MTIMERS_vSetCallback(TIMER0,TIM_mode_OVF,Yellow_Car_Blink);
	MDIO_vSetPinVal(DIO_PORTA,DIO_PIN2,DIO_LOW);
	MDIO_vSetPinVal(DIO_PORTA,DIO_PIN0,DIO_HIGH);
	GS_u8CarFlag=LED_RED;
	GS_u8TypeOFLEDon=LED_RED;
}

void Yellow_passenger_Blink(void)
{

	MTIMERS_SetTimerOvfCounter(TIMER2,500);
	GS_u8PassengerCounter++;
	MDIO_vSetPinVal(DIO_PORTB,DIO_PIN2,DIO_LOW);
	MDIO_vTogPinVal(DIO_PORTB,DIO_PIN1);

	if(GS_u8PassengerCounter == 40)
	{
		if(GS_u8CaseOneFlag==DISEBLE)
		{

			MTIMERS_vSetCallback(TIMER2,TIM_mode_OVF,Red_passenger);
			MTIMERS_SetTimerOvfCounter(TIMER2,1);
			GS_u8PassengerCounter = 0 ;
		}
		else if (GS_u8CaseOneFlag==ENABLE )
		{
			MTIMERS_vSetCallback(TIMER2,TIM_mode_OVF,Green_passenger);
			MDIO_vSetPinVal(DIO_PORTB,DIO_PIN0,DIO_LOW);
			MTIMERS_SetTimerOvfCounter(TIMER2,1);
			GS_u8PassengerCounter = 0 ;
		}
	}

}
void Green_passenger(void)
{

	MTIMERS_SetTimerOvfCounter(TIMER2,19532);
	MDIO_vSetPinVal(DIO_PORTB,DIO_PIN2,DIO_HIGH);
	if (GS_u8CaseOneFlag==ENABLE )
	{
		MTIMERS_vSetCallback(TIMER2,TIM_mode_OVF,StopPassengerTrifficLight);

	}
	else if(GS_u8CaseOneFlag==DISEBLE)
	{
		MTIMERS_vSetCallback(TIMER2,TIM_mode_OVF,Yellow_passenger_Blink);
	}

}
void Red_passenger(void)
{

	MTIMERS_SetTimerOvfCounter(TIMER2,19532);
	MDIO_vSetPinVal(DIO_PORTB,DIO_PIN1,DIO_LOW);
	MDIO_vSetPinVal(DIO_PORTB,DIO_PIN0,DIO_HIGH);
	MTIMERS_vSetCallback(TIMER2,TIM_mode_OVF,StopPassengerTrifficLight);

}

ISR(INT0_vect)
{


	if(GS_u8CarFlag==LED_RED)
	{
		MEXTI_vDisableInterrupt(EXTI_INT0);
		GS_u8CaseOneFlag=DISEBLE;
		MTIMERS_vSetCallback(TIMER0,TIM_CB_OVF,Red_Car);
		MTIMERS_vSetCallback(TIMER2,TIM_CB_OVF,Green_passenger);
		MTIMERS_SetTimerOvfCounter(TIMER0,1);
		MTIMERS_SetTimerOvfCounter(TIMER2,1);
		MTIMERS_vStartTimer(TIMER2);

	}
	else if((GS_u8CarFlag==LED_GREEN) || (GS_u8CarFlag==LED_YELLOW))
	{
		MEXTI_vDisableInterrupt(EXTI_INT0);
		GS_u8CarCounter=0;
		GS_u8TypeOFLEDon=LED_GREEN;
		GS_u8CaseOneFlag=ENABLE;
		MDIO_vSetPinVal(DIO_PORTB,DIO_PIN0,DIO_HIGH);
		MTIMERS_vSetCallback(TIMER0,TIM_CB_OVF,Yellow_Car_Blink);
		MTIMERS_vSetCallback(TIMER2,TIM_CB_OVF,Yellow_passenger_Blink);
		MTIMERS_vStartTimer(TIMER2);
		MTIMERS_SetTimerOvfCounter(TIMER0,1);
		MTIMERS_SetTimerOvfCounter(TIMER2,1);

	}


}



int main(void)
{
	MEXTI_vSetSenseControl(EXTI_INT0,EXTI_FALLING_EDGE);
	MEXTI_vEnableInterrupt(EXTI_INT0);
	MDIO_vSetPinVal(DIO_PORTD,DIO_PIN2,DIO_HIGH);
	MGIE_vEnableGlobalInterrupt();
	MTIMERS_vInit();
	MDIO_vSetPortDir(DIO_PORTA,0x07);
	MDIO_vSetPortDir(DIO_PORTB,0x07);
	MTIMERS_vIsrFeatuer(TIMER0,ISR_OVF);
	MTIMERS_vIsrFeatuer(TIMER2,ISR_OVF);
	MTIMERS_vSetCallback(TIMER0,TIM_mode_OVF,Green_Car);
	MTIMERS_vStartTimer(TIMER0);


	while(1)
	{


	}
}






/*
 * EXTI-pro.c
 *
 *  Created on: Jul 23, 2023
 *      Author: userH
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../DIO/DIO_int.h"
#include "EXTI-int.h"
#include "EXTI-prv.h"
#include "EXTI-con.h"


void MEXTI_vEnableInterrupt(u8 A_u8ExtiLineNo)
{
	switch(A_u8ExtiLineNo)
	{
	case EXTI_INT0:
		SET_BIT(GICR,6);
		MDIO_vSetPinDir(DIO_PORTD,DIO_PIN2,DIO_INPUT);
		break;
	case EXTI_INT1:
		SET_BIT(GICR,7);
		MDIO_vSetPinDir(DIO_PORTD,DIO_PIN3,DIO_INPUT);
		break;
	case EXTI_INT2:
		SET_BIT(GICR,5);
		MDIO_vSetPinDir(DIO_PORTB,DIO_PIN2,DIO_INPUT);
		break;

	}

}
void MEXTI_vDisableInterrupt(u8 A_u8ExtiLineNo)
{
	switch(A_u8ExtiLineNo)
	{
	case EXTI_INT0:
		CLR_BIT(GICR,6);
		break;
	case EXTI_INT1:
		CLR_BIT(GICR,7);
		break;
	case EXTI_INT2:
		CLR_BIT(GICR,5);
		break;

	}
}
void MEXTI_vSetSenseControl(u8 A_u8ExtiLineNo, u8 A_u8SenseCtrl)
{
	switch(A_u8ExtiLineNo)
	{
	case EXTI_INT0 :
		switch(A_u8SenseCtrl)
		{
		case EXTI_FALLING_EDGE :
			CLR_BIT(MCUCR,0);
			SET_BIT(MCUCR,1);
			break;
		case EXTI_RISING_EDGE :
			SET_BIT(MCUCR,1);
			SET_BIT(MCUCR,0);
			break;
		case EXTI_LOW :
			CLR_BIT(MCUCR,1);
			CLR_BIT(MCUCR,0);
			break;
		case EXTI_ANY_CHANGE :
			CLR_BIT(MCUCR,1);
			SET_BIT(MCUCR,0);
			break;
		}
		break;

	case EXTI_INT1 :
		switch(A_u8SenseCtrl)
		{
		case EXTI_FALLING_EDGE :
				CLR_BIT(MCUCR,2);
				SET_BIT(MCUCR,3);
				break;
		case EXTI_RISING_EDGE :
				SET_BIT(MCUCR,2);
				SET_BIT(MCUCR,3);
				break;
		case EXTI_LOW :
				CLR_BIT(MCUCR,2);
				CLR_BIT(MCUCR,3);
				break;
		case EXTI_ANY_CHANGE :
				CLR_BIT(MCUCR,3);
				SET_BIT(MCUCR,2);
				break;
		}
		break;

	case EXTI_INT2:
		if((A_u8SenseCtrl==EXTI_RISING_EDGE)||(A_u8SenseCtrl==EXTI_FALLING_EDGE))
		{
		switch(A_u8SenseCtrl)
		{
		case EXTI_FALLING_EDGE:
					CLR_BIT(MCUCSR,6);
					break;
		case EXTI_RISING_EDGE:
					SET_BIT(MCUCSR,6);
					break;
		}
		}
		break;
	}
}

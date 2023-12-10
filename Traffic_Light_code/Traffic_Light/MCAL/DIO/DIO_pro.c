/*
 * DIO_pro.c
 *
 *  Created on: Jul 13, 2023
 *      Author: userH
 */
#include"../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "DIO_int.h"
#include "DIO-prv.h"



void MDIO_vSetPinDir(u8 A_u8PortNo , u8 A_u8PinNo , u8 A_u8Dir)
{
	if(A_u8Dir == DIO_OUTPUT)
	{
		switch(A_u8PortNo)
		{
		case DIO_PORTA :
			SET_BIT(DDRA , A_u8PinNo );
			break;
		case DIO_PORTB :
			SET_BIT(DDRB , A_u8PinNo );
			break;
		case DIO_PORTC:
			SET_BIT(DDRC , A_u8PinNo );
			break;
		case DIO_PORTD :
			SET_BIT(DDRD , A_u8PinNo );
			break;
		}
	}
	else if(A_u8Dir == DIO_INPUT)
	{
		switch(A_u8PortNo)
		{
		case DIO_PORTA :
			CLR_BIT(DDRA , A_u8PinNo );
			break;
		case DIO_PORTB :
			CLR_BIT(DDRB , A_u8PinNo );
			break;
		case DIO_PORTC :
			CLR_BIT(DDRC , A_u8PinNo );
			break;
		case DIO_PORTD :
			CLR_BIT(DDRD , A_u8PinNo );
			break;
		}
	}
}

void MDIO_vSetPinVal(u8 A_u8PortNo ,u8 A_u8PinNo , u8 A_u8Val)
{
	if(A_u8Val == DIO_HIGH)
	{
		switch(A_u8PortNo)
		{
		case DIO_PORTA :
			SET_BIT(PORTA , A_u8PinNo );
			break;
		case DIO_PORTB :
			SET_BIT(PORTB, A_u8PinNo );
			break;
		case DIO_PORTC:
			SET_BIT(PORTC , A_u8PinNo );
			break;
		case DIO_PORTD :
			SET_BIT(PORTD , A_u8PinNo );
			break;
		}
	}
	else if(A_u8Val == DIO_LOW)
	{
		switch(A_u8PortNo)
		{
		case DIO_PORTA :
			CLR_BIT(PORTA , A_u8PinNo );
			break;
		case DIO_PORTB :
			CLR_BIT(PORTB , A_u8PinNo );
			break;
		case DIO_PORTC :
			CLR_BIT(PORTC , A_u8PinNo );
			break;
		case DIO_PORTD :
			CLR_BIT(PORTD , A_u8PinNo );
			break;
		}
	}

}

void MDIO_vTogPinVal(u8 A_u8PortNo ,u8 A_u8PinNo)
{
	switch(A_u8PortNo)
	{
	case DIO_PORTA :
		TOG_BIT(PORTA , A_u8PinNo );
		break;
	case DIO_PORTB :
		TOG_BIT(PORTB, A_u8PinNo );
		break;
	case DIO_PORTC:
		TOG_BIT(PORTC , A_u8PinNo );
		break;
	case DIO_PORTD :
		TOG_BIT(PORTD , A_u8PinNo );
		break;
	}
}

u8 MDIO_u8GetPinVal(u8 A_u8PortNo , u8 A_u8PinNo)
{
	u8 L_PinVal = 0;

	switch(A_u8PortNo)
	{
	case DIO_PORTA :
		L_PinVal = GET_BIT(PINA , A_u8PinNo );
		break;
	case DIO_PORTB :
		L_PinVal = GET_BIT(PINB , A_u8PinNo );
		break;
	case DIO_PORTC :
		L_PinVal = GET_BIT(PINC , A_u8PinNo );
		break;
	case DIO_PORTD :
		L_PinVal = GET_BIT(PIND , A_u8PinNo );
		break;
	}

	return L_PinVal ;
}

void MDIO_vSetPortDir(u8 A_u8PortNo , u8 A_u8Dir)
{

	switch(A_u8PortNo)
	{
	case DIO_PORTA :
		DDRA =  A_u8Dir;
		break;
	case DIO_PORTB :
		DDRB = A_u8Dir;
		break;
	case DIO_PORTC:
		DDRC = A_u8Dir ;
		break;
	case DIO_PORTD :
		DDRD = A_u8Dir ;
		break;
	}

}
void MDIO_vSetPortVal(u8 A_u8PortNo , u8 A_u8val)
{
	switch(A_u8PortNo)
	{
	case DIO_PORTA :
		PORTA=  A_u8val;
		break;
	case DIO_PORTB :
		PORTB = A_u8val;
		break;
	case DIO_PORTC:
		PORTC = A_u8val ;
		break;
	case DIO_PORTD :
		PORTD = A_u8val ;
		break;
	}

}

u8 MDIO_u8GetPortVal(u8 A_u8PortNo)
{

	u8 L_PortVal = 0 ;

	switch(A_u8PortNo)
	{
	case DIO_PORTA :
		L_PortVal = PORTA ;
		break;
	case DIO_PORTB :
		L_PortVal = PORTB ;
		break;
	case DIO_PORTC:
		L_PortVal = PORTC ;
		break;
	case DIO_PORTD :
		L_PortVal = PORTD ;
		break;
	}

	return L_PortVal ;
}





/*
 * LCD_pro.c
 *
 *  Created on: Jul 15, 2023
 *      Author: userH
 */
#include"../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include"../../MCAL/DIO/DIO_int.h"
#include <util/delay.h>
#include"LCD_int.h"


void HLCD_vSendCommand(u8 A_u8Command)
{

	MDIO_vSetPinVal(LCD_CTRL_PORT, LCD_RS_PIN , DIO_LOW);
	MDIO_vSetPinVal(LCD_CTRL_PORT, LCD_RW_PIN , DIO_LOW);
	MDIO_vSetPortVal(LCD_DATA_PORT,A_u8Command);

	MDIO_vSetPinVal(LCD_CTRL_PORT, LCD_EN_PIN,DIO_HIGH);
	_delay_ms(1);
	MDIO_vSetPinVal(LCD_CTRL_PORT, LCD_EN_PIN,DIO_LOW);
	_delay_ms(1);
}

void HLCD_vSendChar(u8 A_u8Char)
{
	MDIO_vSetPinVal(LCD_CTRL_PORT, LCD_RS_PIN , DIO_HIGH);
	MDIO_vSetPinVal(LCD_CTRL_PORT, LCD_RW_PIN , DIO_LOW);
	MDIO_vSetPortVal(LCD_DATA_PORT,A_u8Char);

	MDIO_vSetPinVal(LCD_CTRL_PORT, LCD_EN_PIN,DIO_HIGH);
	_delay_ms(1);
	MDIO_vSetPinVal(LCD_CTRL_PORT, LCD_EN_PIN,DIO_LOW);
	_delay_ms(1);

}


void HLCD_vInit(void)
{

	MDIO_vSetPortDir(LCD_DATA_PORT,0xff);
	MDIO_vSetPinDir(LCD_CTRL_PORT,LCD_RS_PIN,DIO_OUTPUT);
	MDIO_vSetPinDir(LCD_CTRL_PORT,LCD_RW_PIN,DIO_OUTPUT);
	MDIO_vSetPinDir(LCD_CTRL_PORT,LCD_EN_PIN,DIO_OUTPUT);

	_delay_ms(50);
	HLCD_vSendCommand(0b00111000);
	_delay_ms(1);
	//HLCD_vSendCommand(0b00001110); Cursor ON
	HLCD_vSendCommand(0b00001100);
	_delay_ms(1);
	HLCD_vSendCommand(0b00000001);
	_delay_ms(3);
	HLCD_vSendCommand(0b00000110);
	_delay_ms(1);
}


void HLCD_vPrintString(u8 A_s8String[])
{
	for(u8 L_u8I = 0 ; A_s8String[L_u8I] != '\0' ; L_u8I++)
	{
		HLCD_vSendChar(A_s8String[L_u8I]);

	}


}


void HLCD_vPrintNumber(s32 A_s32Number)
{
	u8 L_u8Digits[10]={0};
	u8 L_u8counter = 0;
	while(A_s32Number >0)
	{
		L_u8Digits[L_u8counter]=A_s32Number%10;
		L_u8counter++;
		A_s32Number/=10 ;
	}
	for(s8 L_s8loop=L_u8counter-1;L_s8loop>=0;L_s8loop--)
		HLCD_vSendChar('0'+L_u8Digits[L_s8loop]);
}

void HLCD_vGoToXY(u8 A_u8Row , u8 A_u8Col)
{

	u8 L_u8DdramAdderss ;

	if( (A_u8Row < MAX_IDX_OF_ROW) && (A_u8Col < MAX_IDX_OF_COL) )
	{
		if(A_u8Row == FIRST_ROW_IDX)
		{
			L_u8DdramAdderss = FIRST_ROW_START + A_u8Col;
		}
		else
		{
			L_u8DdramAdderss = SEC_ROW_START + A_u8Col;
		}

		SET_BIT(L_u8DdramAdderss , 7);
		HLCD_vSendCommand(L_u8DdramAdderss);

	}

	else
	{
		/*dont do eny thing*/
	}

}





void HLCD_vSaveCustomChar(u8 A_u8PatternIdx , u8 A_PatternValue[])
{
	u8 L_u8LoopIterator;
/*SET CURSOR POTHSION TO CGRAM*/
	HLCD_vSendCommand(0b01000000 + (A_u8PatternIdx*8) ) ;

	/*SAVE CUSTEM CHAR*/
	for (L_u8LoopIterator = 0; L_u8LoopIterator < 8 ; L_u8LoopIterator++)
	{
		HLCD_vSendChar(A_PatternValue[L_u8LoopIterator]);
	}
	/*SET CURSOR POTHSION TO CGROM*/
	HLCD_vSendCommand(0x80);

}


void HLCD_vDisplayCustomChar(u8 A_u8CgramIndex)
{
	if(A_u8CgramIndex < 8 )
	{
		HLCD_vSendChar(A_u8CgramIndex);
	}
}

void HLCD_vClearDisplay(void)
{


	HLCD_vSendCommand(CLEAR_COMD);
}
void HLCD_vShiftPostion(u8 L_u8TypeOfShifting)
{
	void HLCD_vShiftPostion(u8 L_u8TypeOfShifting)
	{
		switch (L_u8TypeOfShifting)
		{
		case SHIFT_Cursor_LEFT:
			HLCD_vSendCommand(SHIFT_Cursor_LEFT);
			break;
		case SHIFT_Cursor_RIGHT:
			HLCD_vSendCommand(SHIFT_Cursor_RIGHT);
			break;
		case SHIFT_LEFT:
			HLCD_vSendCommand(SHIFT_LEFT);
			break;
		case SHIFT_RIGHT:
			HLCD_vSendCommand(SHIFT_RIGHT);
			break;

		}

	}

}

/*
 * LCD_int.h
 *
 *  Created on: Jul 15, 2023
 *      Author: userH
 */

#ifndef HAL_LCD_LCD_INT_H_
#define HAL_LCD_LCD_INT_H_

#define LCD_CTRL_PORT DIO_PORTD
#define LCD_DATA_PORT DIO_PORTC
#define LCD_RS_PIN    DIO_PIN3
#define LCD_RW_PIN    DIO_PIN4
#define LCD_EN_PIN    DIO_PIN5
#define MAX_IDX_OF_ROW 2
#define MAX_IDX_OF_COL   16
#define FIRST_ROW_START 0x00
#define SEC_ROW_START 0x40
#define FIRST_ROW_IDX  0
#define CLEAR_COMD   0x01
#define SHIFT_Cursor_RIGHT  0x14
#define SHIFT_Cursor_LEFT   0x10
#define SHIFT_RIGHT  0x1C
#define SHIFT_LEFT   0x18


void HLCD_vSendCommand(u8 A_u8Commandd);
void HLCD_vSendChar(u8 A_u8Char);
void HLCD_vInit(void);
void HLCD_vPrintString(u8 A_s8String[]);
void HLCD_vPrintNumber(s32 A_s32Number);
void HLCD_vGoToXY(u8 A_u8Row , u8 A_u8Col);
void HLCD_vSaveCustomChar(u8 A_u8PatternIdx , u8 A_PatternValue[]);
void HLCD_vDisplayCustomChar(u8 A_u8CgramIndex);
void HLCD_vClearDisplay(void);
void HLCD_vShiftPostion(u8 L_u8TypeOfShifting);



#endif /* HAL_LCD_LCD_INT_H_ */

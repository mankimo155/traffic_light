/*
 * EXTI-int.h
 *
 *  Created on: Jul 23, 2023
 *      Author: userH
 */

#ifndef MCAL_EXTI_EXTI_INT_H_
#define MCAL_EXTI_EXTI_INT_H_

#define EXTI_INT0 0
#define EXTI_INT1 1
#define EXTI_INT2 2

#define EXTI_FALLING_EDGE 0
#define EXTI_RISING_EDGE  1
#define EXTI_LOW          2
#define EXTI_ANY_CHANGE   3


void MEXTI_vEnableInterrupt(u8 A_u8ExtiLineNo);
void MEXTI_vDisableInterrupt(u8 A_u8ExtiLineNo);
void MEXTI_vSetSenseControl(u8 A_u8ExtiLineNo, u8 A_u8SenseCtrl);


#endif /* MCAL_EXTI_EXTI_INT_H_ */

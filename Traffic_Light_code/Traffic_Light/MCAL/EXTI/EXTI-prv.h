/*
 * EXTI-prv.h
 *
 *  Created on: Jul 29, 2023
 *      Author: userH
 */

#ifndef MCAL_EXTI_EXTI_PRV_H_
#define MCAL_EXTI_EXTI_PRV_H_






#define GICR   *((volatile u8*)(0x5B))
#define MCUCR  *((volatile u8*)(0x55))
#define MCUCSR *((volatile u8*)(0x54))
#endif /* MCAL_EXTI_EXTI_PRV_H_ */

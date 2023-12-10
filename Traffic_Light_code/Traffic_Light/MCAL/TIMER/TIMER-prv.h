/*
 * TIMER-prv.h
 *
 *  Created on: Aug 3, 2023
 *      Author: userH
 */

#ifndef MCAL_TIMER_TIMER_PRV_H_
#define MCAL_TIMER_TIMER_PRV_H_

#define TIMER_OVF			0
#define TIMER_CTC			2
#define TIMER_FASTPWM		3
#define TIMER_PHASECORRECT	1

#define TIMER_NO_PS      0b001
#define TIMER_PS_8       0b010
#define TIMER_PS_64      0b011
#define TIMER_PS_256     0b100
#define TIMER_PS_1024    0b101
#define TIMER_DISABLE    0b000

#define OC_DISABLE      0
#define OC_TOGGLE       1
#define OC_CLEAR        2
#define OC_SET          3



#define ENABLE		1
#define DISABLE		0
/*TIMER0*/
#define WGM01       3
#define WGM00       6
#define COM01       5
#define COM00       4
#define TOIE0       0
#define OCIE0       1
/*TIMER2*/
#define WGM20       3
#define WGM21       6
#define COM21       5
#define COM20       4
#define TOIE2       6
#define OCIE2       7

/*TIMER1*/
#define  TICIE1 5
#define  OCIE1A 4
#define  OCIE1B 3
#define  TOIE1  2

/*timer0 register*/
#define TCCR0		*((volatile u8*)(0x53))
#define TCNT0		*((volatile u8*)(0x52))
#define OCR0		*((volatile u8*)(0x5C))
#define TIMSK		*((volatile u8*)(0x59))
#define TIFR		*((volatile u8*)(0x58))

/*u16timer1 register*/
#define TCCR1A		*((volatile u8*)(0x4F))
#define TCCR1B		*((volatile u8*)(0x4E))
#define TCNT1		*((volatile u16*)(0x4C))
#define OCR1A       *((volatile u16*)(0x4A))
#define OCR1B       *((volatile u16*)(0x48))
#define ICR1        *((volatile u16*)(0x46))


/*timer2 register*/
#define TCCR2		*((volatile u8*)(0x45))
#define TCNT2		*((volatile u8*)(0x44))
#define OCR2		*((volatile u8*)(0x43))
#define ASSR		*((volatile u8*)(0x42))

#endif /* MCAL_TIMER_TIMER_PRV_H_ */

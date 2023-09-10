/*
 * interrupt.h
 *
 *  Created on: Aug 16, 2023
 *      Author: Modern Computer
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#define EXT_INT0	0
#define EXT_INT1	1
#define EXT_INT2	2

#define RISING		0
#define FALLING		1
#define LOW_LEVEL	2
#define TOGGLING	3

#define GIE 		7

void Intrrupt_Init      (u8 copy_u8Interrupt_id,u8 copy_u8Interrupt_mode);
void Intrrupt_Enbled    (u8 copy_u8Interrupt_id);
void Intrrupt_Desbled   (u8 copy_u8Interrupt_id);
void Intrrupt_Get_fun	(u8 copy_u8Interrupt_id , void(*pf)(void));

#endif /* INTERRUPT_H_ */

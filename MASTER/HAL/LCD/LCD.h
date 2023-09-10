/*
 * TYPES.h
 *
 *  Created on: Sep 5, 2023
 *      Author: Lamiaa Gabriel
 */

#ifndef HAL_LCD_LCD_H_
#define HAL_LCD_LCD_H_

#define CLEAR_DISPLAY 				 0x01
#define RETURN_HOME 				 0x02
#define ENTRY_MODE_SET 			     0x06
#define DISPLAY_OFF_CONTROL		     0x08
#define DISPLAY_ON_CONTROL		     0x0C
#define CURSOR_OR_DISPLAY_SHIFT      0x80
#define LCD_RESET		  			 0x30
#define LCD_SET 		 			0x38


#define LCD_DATA_PORT			PORTA
#define LCD_DATA_PORT_DDR		DDRA

#define LCD_CONTROL_PORT 		PORTD
#define LCD_CONTROL_PORT_DDR	DDRD

#define RS_PIN				PIN0
#define RW_PIN				PIN1
#define E_PIN				PIN2

#endif /* HAL_LCD_LCD_H_ */

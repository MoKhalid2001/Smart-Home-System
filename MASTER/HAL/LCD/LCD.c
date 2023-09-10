/*
 * UTILS.c
 *
 *  Created on: Sep 5, 2023
 *      Author: Lamiaa Gabriel
 */



/*
 * LCD.c
 *
 *  Created on: Aug 13, 2023
 *      Author: eng_youssef_goher
 */
#include "LCD.h"

#include<avr/io.h>
#include<avr/delay.h>
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"


void LCD_INIT(void){
	 LCD_DATA_PORT_DDR = 0xFF;
//	 SET_PORT_TYPE(LCD_DATA_PORT_DDR, OUTPUT);
	 SET_BIT(LCD_CONTROL_PORT_DDR, RS_PIN);
	 SET_BIT(LCD_CONTROL_PORT_DDR, RW_PIN);
	 SET_BIT(LCD_CONTROL_PORT_DDR, E_PIN);

	 _delay_ms(30);
	 LCD_WRITE_CMD(LCD_SET);
	 _delay_ms(1);
	 LCD_WRITE_CMD(DISPLAY_ON_CONTROL);
	 _delay_ms(1);
	 LCD_WRITE_CMD(CLEAR_DISPLAY);
	 _delay_ms(2);
	 LCD_WRITE_CMD(ENTRY_MODE_SET);
}
void LCD_WRITE_DATA(u8 data){
	/* Set RS to HIGH */
	SET_BIT(LCD_CONTROL_PORT, RS_PIN);
	/* Set R/W to LOW */
	CLR_BIT(LCD_CONTROL_PORT, RW_PIN);
	/* Set E to HIGH */
	SET_BIT(LCD_CONTROL_PORT, E_PIN);

	/*set data*/
	LCD_DATA_PORT = data;
	_delay_ms(5);

	/* Set E to LOW */
	CLR_BIT(LCD_CONTROL_PORT, E_PIN);
	_delay_ms(10);
}
void LCD_WRITE_CMD(u8 command){
	/* Set RS to HIGH */
	CLR_BIT(LCD_CONTROL_PORT, RS_PIN);
	/* Set R/W to LOW */
	CLR_BIT(LCD_CONTROL_PORT, RW_PIN);
	/* Set E to HIGH */
	SET_BIT(LCD_CONTROL_PORT, E_PIN);
	/*set data*/
	LCD_DATA_PORT= command;
	_delay_ms(5);
	/* Set E to LOW */
	CLR_BIT(LCD_CONTROL_PORT, E_PIN);
	/* Delay for 10ms to do command*/
	_delay_ms(10);
}
void LCD_SET_CURSOR_POSITION(u8 row, u8 col){

	u8 command=127;
	if(col>=1&&col<=16){
		switch(row){
		case 1:
			command+=col;
			break;
		case 2:
			command+=col+64;
			break;
		default:break;
		}
		LCD_WRITE_CMD(command);
	} else{

	}
}
void LCD_WRITE_STRING(u8* string){
	 u8 counter=0;
	 for(counter=0;string[counter]!='\0';counter++){
		 LCD_WRITE_DATA(string[counter]);
		 _delay_ms(2);
	 }
}
void LCD_SAVE_CUSTOM_CHAR(u8 data[], u8 location){
	 u8 address=0;
	 u8 counter;
	 if(location >= 1 && location <= 8){
		 address=(location - 1) * 8;
		 SET_BIT(address, 6);
		 LCD_WRITE_CMD(address);
		 for(counter=0;counter<8;counter++){
			 LCD_WRITE_DATA(data[counter]);
			 _delay_ms(2);
		 }
		 LCD_SET_CURSOR_POSITION(1, 1);
	 }

 }
 void LCD_SET_CURSOR_POSITION_WITH_OFFSET(u8 row, u8 col, u8 offset) {
     u8 command = 127;

     // Calculate the cursor position based on the starting position and offset
     u8 position = (row == 1) ? col : (col + 64);

     // Adjust the position based on the offset
     if (offset > 0) {
         position += offset;
     }

     if (position >= 1 && position <= 16) {
         command += position;
         LCD_WRITE_CMD(command);
     } else {

     }
}

void LCD_CLR_RANGE(u8 row, u8 from, u8 to) {
	for(int i = from; i < to; i++)
		LCD_SET_CURSOR_POSITION(row, i);
}


void LCD_WRITE_CENTER_STRING(u8 * string, u8 row) {
	// clear the row
	LCD_CLR_RANGE(row, 0, 16);
	_delay_ms(5);

	u8 start = (16 - strlen(string)) / 2 + 1;   // Calculate starting position for "string"

	// Display "string" at the center of the specified row
	LCD_SET_CURSOR_POSITION(row, start);
	LCD_WRITE_STRING(string);
}


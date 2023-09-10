/*
 * UTILS.c
 *
 *  Created on: Sep 5, 2023
 *      Author: Lamiaa Gabriel
 */

#include "KEYPAD.h"

#include<avr/io.h>
#include<avr/delay.h>
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"


const u8 BUTTONS[4][4] = {
	{'7','8','9','/'},
	{'4','5','6','*'},
	{'1','2','3','-'},
	{'N','0','=','+'}
};

static u8 ROWS[4] = {ROW_PIN0, ROW_PIN1, ROW_PIN2, ROW_PIN3};
static u8 COLS[4] = {COL_PIN0, COL_PIN1, COL_PIN2, COL_PIN3};


void KEYPAD_INIT(void) {
	u8 counter = 0;
	for(counter = 0; counter < 4; counter++){
	//Set ROWS as O/P
		SET_BIT(KEY_PORT_DDR, ROWS[counter]);
	//Set CLOMS as I/P
		CLR_BIT(KEY_PORT_DDR, COLS[counter]);
	}

	KEY_PORT=0xFF;
}
u8 KEYPAD_INPUT(void) {
	u8 inner_counter=0;
	u8 outer_counter=0;
		for(outer_counter=0;outer_counter<4;outer_counter++){
			CLR_BIT(KEY_PORT,ROWS[outer_counter]);
			for(inner_counter=0;inner_counter<4;inner_counter++){
				if(GET_BIT(KEY_PORT_PIN, COLS[inner_counter])==0){
					while(GET_BIT(KEY_PORT_PIN, COLS[inner_counter])==0);
					SET_BIT(KEY_PORT, ROWS[outer_counter]);
					return BUTTONS[outer_counter][inner_counter] ;
				}
			}
			SET_BIT(KEY_PORT, ROWS[outer_counter]);

		}
		return '\0';
}

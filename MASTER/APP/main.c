
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

#include <string.h>
#include <stdbool.h>

#include "../HAL/KEYPAD/KEYPAD.h"
#include "../HAL/LCD/LCD.h"

#include "../MCAL/SPI/SPI.h"
#include "../MCAL/ADC/ADC.h"

#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/task.h"
#include "../FreeRTOS/FreeRTOSConfig.h"

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#define ACCOUNT_LENGTH 		10
#define PASSWORD_DIGITS		3
#define MAX_PASSWORD_TRIES	3

void BUZ1(void * pvParameters);
void vDoorTaskCode(void * pvParameters);
void Send(void * pvParameters);
void greetingText(void);
bool isValidUser(void);
u8 getUserId(void);
bool isPasswordValid(u8 userId);
void message(const u8* string);

u8 Door_counter = 1,Send_Enable = 1, BUZ_Enable = 0, Data = 0 ;
BaseType_t xOpenDoorTask;
TaskHandle_t xHandleDoorTask = NULL;

struct User {
    u8 username[10];
    u8 password[PASSWORD_DIGITS];
};

struct User users[ACCOUNT_LENGTH] = {
   { "Abdallah"	, "000" },
   { "Mahmoud"	, "111" },
   { "Mohammed"	, "222" },
   { "Mohammed"	, "333" },
   { "Lamiaa"	, "444" },
   { "Mostafa"	, "555" },
   { "Yossef"	, "666" },
   { "Ahmed"	, "777" },
   { "Ali"		, "888" },
   { "Mona"		, "999" },
};

void main(){
	// Initializations
	SPI_voidInit(Master);
	LCD_INIT();
	KEYPAD_INIT();

	SET_BIT(DDRB,PIN0); // BUZZER 2 " Thief "
	SET_BIT(DDRB,PIN1); // DOOR
	SET_BIT(DDRB,PIN2); // DOOR

    greetingText();

    if(!isValidUser()) {
    	while(1){
    		message("Access Denied");
    	}
    }

    LCD_WRITE_CMD(CLEAR_DISPLAY);
   	LCD_WRITE_CENTER_STRING("Access Granted", 1);

	Data = SPI_u8transcieve(1);
   	_delay_ms(1000);

	xOpenDoorTask = xTaskCreate(vDoorTaskCode,"OpenDoor",configMINIMAL_STACK_SIZE,NULL,1,NULL);
	vTaskStartScheduler();

	while(1);

}

void vDoorTaskCode(void * pvParameters){

    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );

    for( ;; )
    {
    	vTaskDelay(50);
    	if(Door_counter != 0){
    		SET_BIT(PORTB,PIN1);
    		vTaskDelay(3000);
    		CLR_BIT(PORTB,PIN1);

    		vTaskDelay(5000);

    		SET_BIT(PORTB,PIN2);
    		vTaskDelay(3000);
    		CLR_BIT(PORTB,PIN2);
    		Door_counter--;
    	}
    }
}

void greetingText() {
    LCD_WRITE_CENTER_STRING("Welcome", 1);
    LCD_WRITE_CENTER_STRING("to Smart Home!", 2);
    _delay_ms(500);
    LCD_WRITE_CMD(CLEAR_DISPLAY);
}

bool isValidUser(void) {
    u8 userId = getUserId();

    if (userId < 0 || userId >= ACCOUNT_LENGTH) {
        message("Invalid ID");
        return false;
    }

    bool accessGranted = isPasswordValid(userId);

    if (!accessGranted) {
        message("Invalid Password");
        return false;
    }

    return true;
}

u8 getUserId(void) {
    // Prompt user to enter ID
    LCD_SET_CURSOR_POSITION(1, 1);
    LCD_WRITE_STRING("user: ");

    // Read user ID
    u8 inputedId = -1;
    while (1) {
        inputedId = KEYPAD_INPUT();

        if (inputedId >= '0' && inputedId <= '9') {
            inputedId -= '0'; // Convert the ASCII character to an integer
            LCD_SET_CURSOR_POSITION(1, 7);
            LCD_WRITE_STRING(users[inputedId].username);
            break;
        }
    }

    return inputedId;
}

bool isPasswordValid(u8 userId) {
    u8 triesLeft = MAX_PASSWORD_TRIES;

    while (triesLeft--) {
    	u8 enteredPassword[PASSWORD_DIGITS] = {0};

        LCD_SET_CURSOR_POSITION(2, 1);
        LCD_WRITE_STRING("pass: ");


        u8 i = 0;
        while (i < PASSWORD_DIGITS) {
            u8 keyValue = KEYPAD_INPUT();

            if (keyValue >= '0' && keyValue <= '9') {
            	enteredPassword[i] = keyValue;
                LCD_WRITE_DATA('*');
                i++;
            }
        }
        _delay_ms(500);

        // Compare entered password with correct password
        if (strncmp(enteredPassword, users[userId].password, PASSWORD_DIGITS) == 0)
            return true;


        // Access denied, decrement the number of tries left
        LCD_WRITE_CMD(CLEAR_DISPLAY);
        LCD_WRITE_CENTER_STRING("Access Denied", 1);
        LCD_SET_CURSOR_POSITION(2, 2);
        LCD_WRITE_STRING("tries left: ");
        LCD_WRITE_DATA(triesLeft + '0');
        _delay_ms(1000);

        LCD_WRITE_CMD(CLEAR_DISPLAY);

        // Prompt user to enter ID
        LCD_SET_CURSOR_POSITION(1, 1);
        LCD_WRITE_STRING("user: ");
        LCD_SET_CURSOR_POSITION(1, 7);
        LCD_WRITE_STRING(users[userId].username);
    }

    message("No more tries"); // No more tries, access denied
    SET_BIT(PORTB , PIN0);
    return false;
}

void message(const u8* string) {
    LCD_WRITE_CMD(CLEAR_DISPLAY);
    _delay_ms(50);
    LCD_WRITE_CENTER_STRING(string, 1);
    _delay_ms(2000);
    LCD_WRITE_CMD(CLEAR_DISPLAY);
}

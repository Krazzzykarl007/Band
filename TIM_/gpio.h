#ifndef __JJC__JOE_COOL_GPIO_LIB__
#define __JJC__JOE_COOL_GPIO_LIB__

#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>

#include "globalInfo.h"

#define _LOW  0
#define _HIGH 1

#ifndef NUMPINS
    #define NUMPINS 3
#endif // NUMPINS

/*
 * Initialize global GPIO values that are the same for all GPIO regardless of function
 *     - make sure nothing is repeated from other libs (PWM)
 * User needs to set values for specific GPIO ports/pins
 * Start function to begin actual GPIO operation
 * Use 'private' function(s) wherever needed to simplify operation for user
 */

typedef struct {
	GPIO_TypeDef* port;
	uint16_t pin;
} pin;

typedef struct {
	GPIO_InitTypeDef GPIOS; // GPIO init structure
	pin pins[NUMPINS];
	globalInfo*      ginfo;
}   gpiostruct;

gpiostruct* getgpio(void) {
	static gpiostruct intern_;
	return &intern_;
}

// START OF FUNCTION DECLARATIONS #############################################
void initialGPIO_LibSetup(globalInfo* ginfo);

void initGPIO_output(     GPIO_TypeDef* port, uint16_t pinNumber, int pinIndex);
void initGPIO_input(      GPIO_TypeDef* port, uint16_t pinNumber, int pinIndex);
void initGPIO_inputOutput(GPIO_TypeDef* port, uint16_t pinNumber, int pinIndex);

int  digitalRead(int pinIndex);
void digitalWrite(int pinIndex, int value);
// END OF FUNCTION DECLARATIONS ###############################################

void initialGPIO_LibSetup(globalInfo* ginfo) {
	getgpio()->ginfo = ginfo;
}

void initGPIO_output(GPIO_TypeDef* port, uint16_t pinNumber, int pinIndex) {
	getgpio()->pins[pinIndex].pin  = pinNumber;
	getgpio()->pins[pinIndex].port = port;

	getgpio()->GPIOS.GPIO_Pin   = pinNumber;
	getgpio()->GPIOS.GPIO_Mode  = GPIO_Mode_OUT;
	getgpio()->GPIOS.GPIO_Speed = GPIO_Speed_100MHz;
	getgpio()->GPIOS.GPIO_PuPd  = GPIO_PuPd_UP;
	getgpio()->GPIOS.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(port, &getgpio()->GPIOS);
}

void initGPIO_input( GPIO_TypeDef* port, uint16_t pinNumber, int pinIndex) {
	getgpio()->pins[pinIndex].pin  = pinNumber;
	getgpio()->pins[pinIndex].port = port;

	port->

	getgpio()->GPIOS.GPIO_Pin   = pinNumber;
	getgpio()->GPIOS.GPIO_Mode  = GPIO_Mode_IN;
	getgpio()->GPIOS.GPIO_Speed = GPIO_Speed_100MHz;
	getgpio()->GPIOS.GPIO_PuPd  = GPIO_PuPd_UP;
	getgpio()->GPIOS.GPIO_OType = GPIO_OType_PP;
	getgpio()->GPIOS.
	GPIO_Init(port, &getgpio()->GPIOS);
}

#endif // __JJC__JOE_COOL_GPIO_LIB__

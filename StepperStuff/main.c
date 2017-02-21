#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_tim.h>
#include <math.h>	//KK edit

#include "StepperHybrid.h"
#include "GPIOstepper.h"
#define NUMPINS 4
//#include "gpio.h"

int main(void) {
	// initialize all system components, this should always be done in main()
	SystemInit();

	/* call this function before any other PWM configuration functions */
	GPIO_Initializations_Stepper();
	PWM_Initializations_Stepper(42000,200); // set a bunch of variables located in the Pwm.h library
//60
	//TIM3->CCR3 = 30;	//FIX
	//TIM3->CCR4 = 15;	//FIX



    while(1)
    {


    	//Stepper 1
        GPIO_SetBits(GPIOD, GPIO_Pin_0); // -> Direction
        GPIO_ResetBits(GPIOE, GPIO_Pin_0); // -> On/Off
        TIM3->CCR3 = 100;

    	//Stepper 2
        GPIO_ResetBits(GPIOD, GPIO_Pin_1); // -> Direction
        GPIO_ResetBits(GPIOE, GPIO_Pin_1); // -> On/Off
        TIM3->CCR4 = 100;

    	//Stepper 4
        GPIO_ResetBits(GPIOD, GPIO_Pin_3); // -> Direction
        GPIO_ResetBits(GPIOE, GPIO_Pin_3); // -> On/Off
        TIM9->CCR1 = 100;

    }

    return 0;
}

#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_tim.h>

#include "PWM.h"

GPIO_InitTypeDef  GPIO_InitStructure;

int main(void) {
	// initialize all system components, this should always be done in main()
	SystemInit();


	/* call this function before any other PWM configuration functions */
	initialPWM_LibSetup(); // set a bunch of variables located in the Pwm.h library
	initTimerNum(TIM_3);
	initTimerPort(PORT_C);
	initTimerFrequency(42000);
	//initTimerPrescale(1000);
	initTicksPerCycle(60);

	// initialize third channel of given timer
	initTimerPins(PIN_(8), CH3);
	initPinConnect();
	startPWM(); // start PWM output

	// initialize fourth channel of given timer
	initTimerPins(PIN_(9), CH4);
	initPinConnect();
	startPWM();

	/* enable ports C, E, D for GPIO */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	/* GPIOC Configuration: TIM3 CH3 (PC8) and TIM3 CH4 (PC9)*/
	  	GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_8 | GPIO_Pin_9;
	  	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF;
	  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  	GPIO_InitStructure.GPIO_PuPd =  GPIO_PuPd_UP ;
	  	GPIO_Init(GPIOC, &GPIO_InitStructure);



	TIM3->CCR3 = 30;
	TIM3->CCR4 = 15;

    while(1) {

    }

    return 0;
}

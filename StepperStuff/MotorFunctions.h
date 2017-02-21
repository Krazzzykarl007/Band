#ifndef __KARL__MOTOR__FUNCTIONS__
#define __KARL__MOTOR__FUNCTIONS__

void	Stepper3(void)
	{
    GPIO_SetBits(GPIOD, GPIO_Pin_2); // -> Direction
    GPIO_SetBits(GPIOE, GPIO_Pin_2); // -> On/Off
	}

#endif // __KARL__PWM__Initializations__H__

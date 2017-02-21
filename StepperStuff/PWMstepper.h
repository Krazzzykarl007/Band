#ifndef __KARL__PWM__Initializations__Stepper__
#define __KARL__PWM__Initializations__Stepper__

#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_tim.h>

//uint16_t PrescalerValue = 0;
//uint32_t adjusted_bus_clock_frequency;
//uint16_t freq;

void PWM_Initializations_Stepper(void)
	{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;	//x
	TIM_OCInitTypeDef TIM_OCInitStructure;	//x
	// Frequency setup
	#ifndef BUS_CLOCK_FREQUENCY
	#define BUS_CLOCK_FREQUENCY (42000000) // default 42MHz
	#endif // BUS_CLOCK_FREQUENCY

	float tempBus = BUS_CLOCK_FREQUENCY * 250.0 / 400.0;
	uint32_t adjusted_bus_clock_frequency = tempBus;
	int prescale = adjusted_bus_clock_frequency / freq;

	RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);
	PrescalerValue =(uint16_t) (SystemCoreClock  / 8000000)-1;//3 x
	// TIMER TEMEL AYARLAMALAR
	TIM_TimeBaseStructure.TIM_Period=400;
	TIM_TimeBaseStructure.TIM_Prescaler=839;//PrescalerValue;

	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_ClockDivision=0;
	TIM_TimeBaseInit(TIM9,&TIM_TimeBaseStructure);
	//PWM canal 1
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse=CCR1_Val;//CCR1_Val;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OC1Init(TIM9,&TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM9,TIM_OCPreload_Enable);
	//PWM canal 2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
	TIM_OC2Init(TIM9, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM9, TIM_OCPreload_Enable);
	//PWM canal 3
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse=CCR3_Val;
	TIM_OC3Init(TIM9,&TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM9,TIM_OCPreload_Enable);
	//PWM canal 4
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse=CCR4_Val;
	TIM_OC4Init(TIM9,&TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM9,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM9,ENABLE);
	TIM_Cmd(TIM9,ENABLE);
}

#endif // __KARL__PWM__Initializations__H__

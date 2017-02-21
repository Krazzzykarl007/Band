#ifndef __KARL__PWM__TIMER__H__
#define __KARL__PWM__TIMER__H__

#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_tim.h>

uint32_t tpc; 						//ticks per cycle
uint16_t freq;						//used for prescaler
uint32_t ticksPerPWM_Cycle;			//for duty cycle
void PWM_Initializations_Stepper(freq,tpc)
	{
	/*________________CLOCK FREQUENCY_________________________*/
	#ifndef BUS_CLOCK_FREQUENCY
	#define BUS_CLOCK_FREQUENCY (42000000) // default 42MHz
	#endif // BUS_CLOCK_FREQUENCY

	ticksPerPWM_Cycle=0x00000000;

	float tempBus = BUS_CLOCK_FREQUENCY * 250.0 / 400.0;
	uint32_t adjusted_bus_clock_frequency = tempBus;
	int prescale1 = adjusted_bus_clock_frequency / freq;
	int prescale2 = adjusted_bus_clock_frequency / (freq*2);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;	//x
	TIM_OCInitTypeDef TIM_OCInitStructure;	//x

	//////////////////////TIM9///////////////////////////////////

	/*________________INITIALIZE PERIPHERAL CLOCK______________*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);



	TIM_TimeBaseStructure.TIM_Prescaler     = prescale1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period      	= tpc;
	TIM_TimeBaseInit(TIM9,&TIM_TimeBaseStructure);
	ticksPerPWM_Cycle = tpc;

	//PWM Canal 1
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1; 			//x
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;	//x
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;		//x
	TIM_OC1Init(TIM9,&TIM_OCInitStructure);						//x
	TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM9,ENABLE);
	TIM_Cmd(TIM9,ENABLE);
	/*________________CONFIGURE_______________________________*/
	TIM9->CCR1 = ticksPerPWM_Cycle >> 1; // 50% duty cycle default

	//missing tim pulse

	//////////////////////TIM3///////////////////////////////////

	/*________________INITIALIZE PERIPHERAL CLOCK______________*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

	TIM_TimeBaseStructure.TIM_Prescaler     = prescale2;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period      	= tpc;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	ticksPerPWM_Cycle = tpc;

	//PWM Canal 3
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1; 			//x
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;	//x
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;		//x
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);						//x
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
		//possible tim pulse for ccr values

	//PWM Canal 4
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1; 			//x
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;	//x
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;		//x
	TIM_OC4Init(TIM3,&TIM_OCInitStructure);						//x
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM3,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
	/*________________CONFIGURE_______________________________*/
	TIM3->CCR3 = ticksPerPWM_Cycle >> 1; // 50% duty cycle default
	TIM3->CCR4 = ticksPerPWM_Cycle >> 1; // 50% duty cycle default
	//missing tim pulse

	}

#endif // __KARL__PWM__TIMER__H__

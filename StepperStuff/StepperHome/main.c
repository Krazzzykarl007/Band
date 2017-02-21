#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"

//Stepper 1: PC8, TIM3_CH3
//Stepper 2: PC9, TIM3_CH4
//Stepper 3: PE4, TIM9_CH1
//Stepper 4: PE5, TIM9_CH2
int main(void)
{
	RCC_HSEConfig(RCC_HSE_ON);
	while(!RCC_WaitForHSEStartUp())
	{
		/*Wait here awhile*/
	}
	/*******************CREATE VARIABLES*******************/
	uint8_t dir; 	//DC
	uint32_t x;		//DC
	uint16_t PrescalerValue = 0;	//DC
	uint16_t SignalPeriod=0;		//DC


	TIM_OCInitTypeDef  TIM_OCInitStructure;	//IDK

  	GPIO_InitTypeDef GPIO_InitStructure;	//page 60p1 (3 Coretex M4 Buses and Peripherals)
  	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;//page 60p2

  	/*Starts clock to GPIOC & GPIOD*/
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); //page 60p3
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

  	/* TIM3 and TIM9 clock enable */
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//page 60p4
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);


  	/* GPIOC Configuration: TIM3 CH3 (PC8) and TIM3 CH4 (PC9)*/
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  	GPIO_Init(GPIOC, &GPIO_InitStructure);
  	//connects Tim 3 pins to AF2 on Port C (page 60 part 5)

  	/* GPIOE Configuration: TIM9 CH1 (PE4) and TIM9 CH2 (PE5)*/
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  	GPIO_Init(GPIOC, &GPIO_InitStructure);
  	//connects Tim 9 pins to AF2 on Port E (page 60 part 5)

  	/* Connect TIM3 and TIM9 pins to AF2 */ //page60 part 6
  	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM3);
  	GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_TIM3);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource4, GPIO_AF_TIM9);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_TIM9);

	/*Compute the prescaler value  for 28MHz count
	 *  frequency; system clock is 168MHz */

	PrescalerValue = (uint16_t) ((SystemCoreClock /2) / 65536) - 1;
	/* Time base configuration */
	SignalPeriod=(uint16_t)(2800000/(65536));

	TIM_TimeBaseStructure.TIM_Period = 24;//12000;
	TIM_TimeBaseStructure.TIM_Prescaler = 20000;//PrescalerValue;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure);
while (1)
	{

	}

}//End of Main

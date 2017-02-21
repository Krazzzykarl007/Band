#ifndef __KARL__GPIO__Initializations__Stepper__
#define __KARL__GPIO__Initializations__Stepper__

#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_tim.h>

//Stepper 1
/* PD12 -> DC1 good
 * PC08 -> TIM_3 CH_3 good //possibly stepper 2?
 * PD00 -> Direction
 * PE00 -> On/Off
 */

//Stepper 2
/* PD13 -> DC2 good
 * PC09 -> TIM_3 CH_4 good	//possibly stepper 1?
 * PD01 -> Direction
 * PE01 -> On/Off
 */

//Stepper 3
/* PD14 -> DC3 good
 * PE04 -> TIM_9 CH_1 bad (Shold be PE5)
 * PD02 -> Direction
 * PE02 -> On/Off
 */

//Stepper 4
/*
 * PD15 -> DC4 good
 * PE05 -> TIM_9 CH_1 is wired as 2? (SHould be PE6)
 * PD03 -> Direction
 * PE03 -> On/Off
 */

void GPIO_Initializations_Stepper(void)
	{
	GPIO_InitTypeDef  GPIO_InitStructure;

	/*________________INITIALIZE PERIPHERAL CLOCK______________*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	/* Configure PD00, PD01, PD02 and PD03  in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* Configure PE00, PE01, PE02 and PE03 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	/*Timer Initializations*/

	/*Stepper 1 | Stepper 2*/
	/* GPIOE Configuration: TIM3 CH3 (PC8), TIM3 CH4 (PC9) */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8 |GPIO_Pin_9 ;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOC,&GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM3);

	/*Stepper 4*/
	/* GPIOE Configuration: TIM9 CH1 (PE4)*bad*, TIM9 CH2 (PE5) */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOE,&GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOE,GPIO_PinSource5,GPIO_AF_TIM9);
	//GPIO_PinAFConfig(GPIOE,GPIO_PinSource4,GPIO_AF_TIM9);
	}

#endif // __KARL__GPIO__Initializations__H__

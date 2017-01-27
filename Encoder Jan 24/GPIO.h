#ifndef __KARL__GPIO__Initializations__H__
#define __KARL__GPIO__Initializations__H__

#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_tim.h>

void GPIO_Initializations(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	//Encoder Initializations

	//ENCODER 1A->PE9 -> TIM1-CH1
	//ENCODER 1B->PE11-> TIM1-CH2

	//ENCODER 2A->PC6 -> TIM8-CH1
	//ENCODER 2B->PC7 -> TIM8-CH2

	//ENCODER 3A->PA0 -> TIM5-CH1
	//ENCODER 3B->PA1 -> TIM5-CH2

	//ENCODER 4A->PA6 -> TIM3-CH1
	//ENCODER 4B->PA7 -> TIM3-CH2

    //  Initialize the peripheral clocks.
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);	//ENC 1
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);	//ENC 2
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	//ENC 3 && ENC 4

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);	//ENC 1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);	//ENC 2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//ENC 3
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ENC 4

	//Enable Encoder 1 Pins
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	//Enable Encoder 2 Pins
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	//Enable Encoder 3 Pins
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	//Enable Encoder 4 Pins
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//Connect TIM Encoder pins to GPIO
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9,  GPIO_AF_TIM1);  // TIM CH.1->ENC 1A
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_TIM1);  // TIM CH.2->ENC 1B

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6,  GPIO_AF_TIM8);  // TIM CH.1->ENC 2A
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7,  GPIO_AF_TIM8);  // TIM CH.2->ENC 2B

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0,  GPIO_AF_TIM5);  // TIM CH.1->ENC 3A
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1,  GPIO_AF_TIM5);  // TIM CH.2->ENC 3B
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6,  GPIO_AF_TIM3);  // TIM CH.1->ENC 4A
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7,  GPIO_AF_TIM3);  // TIM CH.2->ENC 4B

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStruct;

	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_Period = 0xFFFFFFFF; // Maximal
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);	//ENC 1
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);	//ENC 2
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);	//ENC 3
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);	//ENC 4
	TIM_EncoderInterfaceConfig(TIM1,TIM_EncoderMode_TI1,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);	//ENC 1
	TIM_EncoderInterfaceConfig(TIM8,TIM_EncoderMode_TI1,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);	//ENC 2
	TIM_EncoderInterfaceConfig(TIM5,TIM_EncoderMode_TI1,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);	//ENC 3
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI1,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);	//ENC 4

	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStruct.TIM_ICFilter = 0xFF;
	TIM_ICInit(TIM1,&TIM_ICInitStruct);	//ENC 1
	TIM_ICInit(TIM8,&TIM_ICInitStruct);	//ENC 2
	TIM_ICInit(TIM5,&TIM_ICInitStruct);	//ENC 3
	TIM_ICInit(TIM3,&TIM_ICInitStruct);	//ENC 4
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_2;
	TIM_ICInit(TIM1,&TIM_ICInitStruct);	//ENC 1
	TIM_ICInit(TIM8,&TIM_ICInitStruct);	//ENC 2
	TIM_ICInit(TIM5,&TIM_ICInitStruct);	//ENC 3
	TIM_ICInit(TIM3,&TIM_ICInitStruct);	//ENC 4
	TIM_Cmd(TIM1, ENABLE);	//ENC 1
	TIM_Cmd(TIM8, ENABLE);	//ENC 2
	TIM_Cmd(TIM5, ENABLE);	//ENC 5
	TIM_Cmd(TIM3, ENABLE);	//ENC 3

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	//POTENTIOMETER INITIALIZATIONS

	//POT 1 -> PB0 -> ADC123_IN8
	//POT 2 -> PB1 -> ADC123_IN9
	//POT 3 -> PC4 -> ADC123_IN14
	//POT 4 -> PA3 -> ADC123_IN3
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	//POT 1 && POT 2
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);	//POT 3
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	//POT 4


//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC, ENABLE);	//ENC 1
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);	//ENC 2

//	  ADC_InitTypeDef  ADC_InitStructure;
	  /* PCLK2 is the APB2 clock */
	  /* ADCCLK = PCLK2/6 = 72/6 = 12MHz*/
//	  RCC_ADCCLKConfig(RCC_PCLK2_Div6);

	  /* Enable ADC1 clock so that we can talk to it */
//	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	  /* Put everything back to power-on defaults */
//	  ADC_DeInit(ADC1);

	  /* ADC1 Configuration ------------------------------------------------------*/
	  /* ADC1 and ADC2 operate independently */
//	  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	  /* Disable the scan conversion so we do one at a time */
//	  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	  /* Don't do contimuous conversions - do them on demand */
//	  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	  /* Start conversin by software, not an external trigger */
//	  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	  /* Conversions are 12 bit - put them in the lower 12 bits of the result */
//	  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	  /* Say how many channels would be used by the sequencer */
//	  ADC_InitStructure.ADC_NbrOfChannel = 1;

	  /* Now do the setup */
//	  ADC_Init(ADC1, &ADC_InitStructure);
	  /* Enable ADC1 */
//	  ADC_Cmd(ADC1, ENABLE);

//	  /* Enable ADC1 reset calibaration register */
//	  ADC_ResetCalibration(ADC1);
//	  /* Check the end of ADC1 reset calibration register */
//	  while(ADC_GetResetCalibrationStatus(ADC1));
//	  /* Start ADC1 calibaration */
//	  ADC_StartCalibration(ADC1);
//	  /* Check the end of ADC1 calibration */
//	  while(ADC_GetCalibrationStatus(ADC1));
//http://www.micromouseonline.com/2009/05/26/simple-adc-use-on-the-stm32/

}
#endif // __KARL__GPIO__Initializations__H__

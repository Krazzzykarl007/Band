#ifndef __KARL__TIMER__H__
#define __KARL__TIMER__H__

#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_tim.h>

TIM_OCInitTypeDef  TIM_OCInitStructure;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
GPIO_InitTypeDef GPIO_InitStructure;

//=============================================================================

	enum COUNTERTYPES {
		UP, DOWN
	};

	// initialize timer hardware, but no specific port
	void HW_Init(void) {
		RCC_HSEConfig(RCC_HSE_ON);
		while(!RCC_WaitForHSEStartUp()) {
			/*Wait here awhile*/
		}
		GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
		GPIO_InitStructure.GPIO_Pin   = 0x00000000;
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	}

	void enableTimerClock(uint32_t PeripheralDevBus) {
		RCC_APB1PeriphClockCmd(PeripheralDevBus, ENABLE);
	}

	void setPrescalarValue(int preScalarValue) {
		TIM_TimeBaseStructure.TIM_Prescaler = 0;
	}

	void setCounterMode(enum COUNTERTYPES ct) {
		switch(ct) {
			case UP:
				TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
			case DOWN:
				TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;
			default:
				break;
		}
	}

	void enableTimerChannel(uint32_t pins) {
		GPIO_InitStructure.GPIO_Pin |= pins;
	}

	void setTimerPinOutputType(uint32_t ot) {
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	}

	void initializeTimer(GPIO_TypeDef * port) {
		GPIO_Init(port, &GPIO_InitStructure);
	}

//=============================================================================

#endif // __KARL__TIMER__H__

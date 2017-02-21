#ifndef __KARL__PWM__TIMER__H__
#define __KARL__PWM__TIMER__H__

#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_tim.h>

#define PIN_(pinNumber)  (1 * pinNumber) // ugly hack from back in the day, didnt want to change the interface
#define TIMERCHANNEL_(a) (a-1)

#ifndef BUS_CLOCK_FREQUENCY
	#define BUS_CLOCK_FREQUENCY (42000000) // default 42MHz
#endif // BUS_CLOCK_FREQUENCY

typedef struct {
	TIM_TimeBaseInitTypeDef TBS;   // timer base structure
	TIM_OCInitTypeDef       OCS;   // output control structure
	GPIO_InitTypeDef        GPIOS; // GPIO init structure
	int portSpecified;             // c-equivalent of true or false
	char portLetter;               // shows which port specified timer is connected to
	char timerNumber;              // shows which timer is being used
	uint32_t timerChannel;         // shows which channel on specified timer is being used
	uint32_t ticksPerPWM_Cycle;
	uint32_t pins;              // directly related to timer channel, must be confugured one at a time
	uint32_t adjusted_bus_clock_frequency;
} _intern_;

_intern_ intern_;

typedef enum PortLetter {
	PORT_A, PORT_B, PORT_C, PORT_D, PORT_E
} PortLetter;

typedef enum TimerNumber {
	TIM_1, TIM_2, TIM_3, TIM_4, TIM_5, TIM_6, TIM_7, TIM_8, TIM_9
} TimerNumber;

typedef enum TimerChannel {
	CH1 = 0x000000FF, CH2 = 0x0000FF00, CH3 = 0x00FF0000, CH4 = 0xFF000000
} TimerChannel;

void initialPWM_LibSetup(void) {
	intern_.portSpecified     = 0;
	intern_.timerChannel      = 0x00000000;
	intern_.ticksPerPWM_Cycle = 0x00000000;
	intern_.pins              = 0x00000000;

	float tempBus = BUS_CLOCK_FREQUENCY * 250.0 / 400.0;

	intern_.adjusted_bus_clock_frequency = tempBus;
}

GPIO_TypeDef* getGPIO_Port(void) {
	switch(intern_.portLetter) {
		case 'A': return GPIOA;
		case 'B': return GPIOB;
		case 'C': return GPIOC;
		case 'D': return GPIOD;
		case 'E': return GPIOE;
		default:
			return 0;
	}
}

TIM_TypeDef* getTimer(void) {
	switch(intern_.timerNumber) {
			case '1': return TIM1;
			case '2': return TIM2;
			case '3': return TIM3;
			case '4': return TIM4;
			case '5': return TIM5;
			case '6': return TIM6;
			case '7': return TIM7;
			case '8': return TIM8;
			case '9': return TIM9;
			default:
				return 0;
	}
}

void initTimerNum(TimerNumber tm) {
	switch(tm) {
		case TIM_1:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
			intern_.timerNumber = '1'; break;
		case TIM_2:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
			intern_.timerNumber = '2'; break;
		case TIM_3:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
			intern_.timerNumber = '3'; break;
		case TIM_4:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
			intern_.timerNumber = '4'; break;
		case TIM_5:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
			intern_.timerNumber = '5'; break;
		case TIM_6:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
			intern_.timerNumber = '6'; break;
		case TIM_7:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
			intern_.timerNumber = '7'; break;
		case TIM_8:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
			intern_.timerNumber = '8'; break;
		case TIM_9:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
			intern_.timerNumber = '9'; break;
		default:
			return;
	}
}

void initTimerPort(PortLetter pl) {
	switch(pl) {
		case PORT_A:
			RCC_AHB2PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
			intern_.portLetter = 'A'; break;
		case PORT_B:
			RCC_AHB2PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
			intern_.portLetter = 'B'; break;
		case PORT_C:
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
			intern_.portLetter = 'C'; break;
		case PORT_D:
			RCC_AHB2PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
			intern_.portLetter = 'D'; break;
		case PORT_E:
			RCC_AHB2PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
			intern_.portLetter = 'E'; break;
		default:
			return;
	}

	intern_.portSpecified = 1;
}

void initTimerFrequency(uint16_t freq) {
	int prescale =
		intern_.adjusted_bus_clock_frequency / freq;

	intern_.TBS.TIM_Prescaler     = prescale;
	intern_.TBS.TIM_ClockDivision = 0;
	intern_.TBS.TIM_CounterMode   = TIM_CounterMode_Up;
}

void initTimerPrescale(uint32_t prescaleFreq) {
	intern_.TBS.TIM_Prescaler     = prescaleFreq;
	intern_.TBS.TIM_ClockDivision = 0;
	intern_.TBS.TIM_CounterMode   = TIM_CounterMode_Up;
}

/* safest way to do this, other way is not guaranteed */
void initTimerPins(uint32_t pins, TimerChannel tc) {

	intern_.pins = pins;

	if(intern_.portSpecified == 0) {
		return;
	}

	intern_.GPIOS.GPIO_Pin   = (1 << pins);
	intern_.GPIOS.GPIO_Mode  = GPIO_Mode_AF;
	intern_.GPIOS.GPIO_Speed = GPIO_Speed_100MHz;
	intern_.GPIOS.GPIO_OType = GPIO_OType_PP;
	intern_.GPIOS.GPIO_PuPd  = GPIO_PuPd_UP;

	GPIO_Init(getGPIO_Port(), &intern_.GPIOS);

	intern_.timerChannel = tc;
}

void initPinConnect(void) {
	GPIO_TypeDef* gtd = getGPIO_Port();
	uint8_t AF_Connection;

	TIM_TypeDef* ttd = getTimer();
	if(ttd == TIM1 || ttd == TIM2) {
		AF_Connection = (uint8_t)0x01;
	} else if(ttd == TIM3 || ttd == TIM4 || ttd == TIM5) {
		AF_Connection = (uint8_t)0x02;
	} else if(ttd == TIM8 || ttd == TIM9) {
		AF_Connection = (uint8_t)0x03;
	}

	GPIO_PinAFConfig(gtd, intern_.pins, AF_Connection);
}

void initTicksPerCycle(uint32_t tpc) {
	intern_.OCS.TIM_OCPolarity  = TIM_OCPolarity_High;

	intern_.OCS.TIM_OCMode      = TIM_OCMode_PWM1;
	intern_.TBS.TIM_Period      = tpc;
	//intern_.TBS.TIM_Period      = 10000;
	intern_.OCS.TIM_OutputState = TIM_OutputState_Enable;

	// save tpc info
	intern_.ticksPerPWM_Cycle = tpc;
}

void startPWM(void) {
	TIM_TypeDef* ttd = getTimer();

	// initialize the time base structure
	TIM_TimeBaseInit(getTimer(), &intern_.TBS);

	// figure out active timer channel, and active timer
	if(intern_.timerChannel & CH1) { // bitwise AND
		TIM_OC1Init(ttd, &intern_.OCS);
		TIM_OC1PreloadConfig(ttd, TIM_OCPreload_Enable);
		ttd->CCR1 = intern_.ticksPerPWM_Cycle >> 1; // 50% duty cycle default
	} else
	if(intern_.timerChannel & CH2) {
		TIM_OC2Init(ttd, &intern_.OCS);
		TIM_OC2PreloadConfig(ttd, TIM_OCPreload_Enable);
		ttd->CCR2 = intern_.ticksPerPWM_Cycle >> 1; // --
	} else
	if(intern_.timerChannel & CH3) {
		TIM_OC3Init(ttd, &intern_.OCS);
		TIM_OC3PreloadConfig(ttd, TIM_OCPreload_Enable);
		ttd->CCR3 = intern_.ticksPerPWM_Cycle >> 1; // --
	} else
	if(intern_.timerChannel & CH4) {
		TIM_OC4Init(ttd, &intern_.OCS);
		TIM_OC4PreloadConfig(ttd, TIM_OCPreload_Enable);
		ttd->CCR4 = intern_.ticksPerPWM_Cycle >> 1; // --
	}

	TIM_ARRPreloadConfig(ttd, ENABLE);
	TIM_Cmd(ttd, ENABLE);
}

#endif // __KARL__PWM__TIMER__H__

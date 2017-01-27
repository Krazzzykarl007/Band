#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_tim.h>
#include <math.h>	//KK edit

#define NUMPINS 4

#include "Pwm.h"
//#include "gpio.h"

int main(void) {
	// initialize all system components, this should always be done in main()
	SystemInit();

	globalInfo ginfo = getGInfo();

	/* call this function before any other PWM configuration functions */
	initialPWM_LibSetup(&ginfo); // set a bunch of variables located in the Pwm.h library
	initialGPIO_LibSetup(&ginfo);

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

	//GPIO Initializations for Pins

	TIM3->CCR3 = 30;
	TIM3->CCR4 = 15;

    while(1) {

    }

    return 0;
}

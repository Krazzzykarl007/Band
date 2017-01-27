#include <math.h>
#include <unistd.h>
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rtc.h"

#include "GPIO.h"
uint G1;
uint G2;
void myVecNAV_Delay(uint32_t delay);
void GPIO_Initializations();


void myVecNAV_Delay(uint32_t delay)
{
   uint32_t k;
   for(k=0;k< 7*delay;k++){};
}


int main(void)
{
//GPIO and Timer Initializations in GPIO.h
	GPIO_Initializations();

    while(1)
    {
         G1=TIM_GetCounter(TIM1);
         G2=TIM_GetCounter(TIM8);
         myVecNAV_Delay(25);
    }

}

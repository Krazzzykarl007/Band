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
uint G3;
uint G4;
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
         G1=TIM_GetCounter(TIM1);	//ENC 1
         G2=TIM_GetCounter(TIM8);	//ENC 2
         G3=TIM_GetCounter(TIM5);	//ENC 3
         G4=TIM_GetCounter(TIM3);	//ENC 4
         myVecNAV_Delay(25);
    }

}

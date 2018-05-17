#include <stm32f10x.h>


int main(void)
{
	SystemInit();
	
	RCC->APB2ENR = RCC_APB2ENR_IOPCEN;
	
	GPIOC->CRH = GPIO_CRH_MODE13_0;
	GPIOC->ODR = 0;
	
	
	
	while(1);
}
#include <stm32f10x.h>

void wait_1ms(uint16_t u16Factor) // using timer 4
{
	uint16_t i;
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	TIM4->CR1 = 0x0000;
	TIM4->CR2 = 0x0000;
	TIM4->SMCR = 0x0000;
	TIM4->DIER = 0x0000;
	TIM4->CCMR1 = 0x0000;
	TIM4->CCMR2 = 0x0000;
	TIM4->CCER = 0x0000;
	TIM4->PSC = 1;
	TIM4->ARR = 35999;
	TIM4->EGR = TIM_EGR_UG;
	
	TIM4->SR &= ~TIM_SR_UIF;
	TIM4->CR1 |= TIM_CR1_CEN;
	
	for(i=0;i<u16Factor;i++)
	{
		while(!(TIM4->SR & TIM_SR_UIF));
		TIM4->SR &= ~TIM_SR_UIF;
	}
	TIM4->CR1 = 0x0000;
}

void INT_1ms_init(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	
	TIM4->CR1 = 0x0000;
	TIM4->CR2 = 0x0000;
	TIM4->SMCR = 0x0000;
	TIM4->CCMR1 = 0x0000;
	TIM4->CCMR2 = 0x0000;
	TIM4->CCER = 0x0000;
	TIM4->PSC = 1;
	TIM4->ARR = 35999;
	TIM4->DIER = TIM_DIER_UIE;
	TIM4->SR &= ~TIM_SR_UIF;
	TIM4->EGR = TIM_EGR_UG;
	
	//enable int 29 
	NVIC_ClearPendingIRQ(TIM3_IRQn);
	NVIC_EnableIRQ(TIM3_IRQn);
	
	TIM4->CR1 |= TIM_CR1_CEN;
}

void TIM3_IRQHandler(void)
{
	GPIOC->ODR ^= GPIO_ODR_ODR13;
	NVIC_ClearPendingIRQ(TIM3_IRQn);
}

int main(void)
{
	SystemInit();
	
	RCC->APB2ENR = RCC_APB2ENR_IOPCEN;
	
	GPIOC->CRH = GPIO_CRH_MODE13_0;
	GPIOC->ODR = GPIO_ODR_ODR13;
	
	//INT_1ms_init();
	//__enable_irq();
	
	
	//while(1);
	
	while(1)
	{
		GPIOC->ODR ^= GPIO_ODR_ODR13;
		wait_1ms(1000);
	}
	
	while(1)
	{
		GPIOC->BSRR = GPIO_BSRR_BS13;
		wait_1ms(1000);
		GPIOC->BSRR = GPIO_BSRR_BR13;
		wait_1ms(1000);
		
	}
}

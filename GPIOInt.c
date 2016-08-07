#include "GPIOInt.h"
#include "tm4c123gh6pm.h"
#include "tm4c123_registers.h"
void Enable_IRQ(void)
{
  int R2;
	__asm {MOV R2, 0x0; MSR BASEPRI, R2; CPSIE I
}
}

int main(void)
{
  volatile uint32_t RCC;
	RCC = (SYSCTL_RCC_XTAL_16MHZ|SYSCTL_RCC_USESYSDIV|SYSCTL_SYSDIV_10);
	SYSCTL_RCC_R = RCC;
	SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOB|SYSCTL_RCGC2_GPIOD;     //is this the same as =(1<<1)|(1<<3)??
	GPIO_PORTB_DIR_R = 0X01;
	GPIO_PORTB_DEN_R = 0X01;
	GPIO_PORTD_DIR_R = ~0X8;             //  portD bit 0b1000,    PinD3
	GPIO_PORTD_DEN_R = 0x08;             // was this a Book Typo, the same as 0x8?
	GPIO_PORTD_IS_R = 0X08;              //INTERRUPT SENSE  -  level triggered interrupt
	GPIO_PORTD_IBE_R = 0x0;              //disable IBE -  interrupt Both Edge Sense
  GPIO_PORTD_IEV_R = 0x8;              //Int Edge Level -   HIGH/Rising edge
	GPIO_PORTD_ICR_R = 0x08;             //clears any prev interrupt from PD3
	GPIO_PORTD_IM_R = 0x8;               //enable (unmask) PD3 interrupt
	
	NVIC_PRI0_R = 0X60000000;            //NVIC->IP[3] = 0X60; or NVIC->IP[3] = 6<<28;  ; priority = 3
  NVIC_EN0_R = 0X8;                    //NVIC->ISER[0] |= 0X00000008;  enable IRQ3
  Enable_IRQ();                        //global enable IRQs
  
  while(1)  {GPIO_PORTB_DATA_R = 0x0;} //wait for PD3, set PB0 low	
}



void GPIOD_Handler(void)               //ISR for PD3 interrupt
{
  GPIO_PORTB_DATA_R = 0x1;	
}






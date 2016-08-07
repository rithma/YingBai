/******  Lab 4.3 from Ying Bai's  'Practical microcontroller engineering with ARM technology'
********* works in Keil uVision5    
********** lab completed   8.5.2016
*********** by Etienne Stehelin                                                             */


#include <stdint.h>
#include <stdbool.h>
#include "header.h"
#include <inc/hw_memmap.h>
#include <inc/hw_types.h>
#include <driverlib/sysctl.h>
#include <driverlib/gpio.h>
#include "tm4c123_registers.h"

int main (void)
{
	uint32_t Input;
  bool res;
	
	SysCtlClockSet       (SYSCTL_SYSDIV_10|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
	SYSCTL_RCGC2_R =      SYSCTL_RCGC2_GPIOB|SYSCTL_RCGC2_GPIOC|SYSCTL_RCGC2_GPIOD;
        //GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0); 
	GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE,  GPIO_PIN_4);
	GPIOPinTypeGPIOInput (GPIO_PORTD_BASE,GPIO_PIN_3);
	//GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
	
	res = SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB|SYSCTL_PERIPH_GPIOC|SYSCTL_PERIPH_GPIOD);

  if (res == true)
		{
		while(1)
		{
 		Input = GPIO_PORTD_DATA_R;
    if((Input & 0x8)==0x8)                  //if PD3 is high
			{
				GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0x1);  //LED B0 pin high
				GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, 0x10); //speaker pin high
				SysCtlDelay(50000);         //1.25 ms,  400hz    //duty cycle
				GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0x0);  //LED B1 pin low
				GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, 0x0); //speaker pin low
				SysCtlDelay(50000);         //1.25 ms,  400hz    //duty cycle			
		  }
	  }
}
}


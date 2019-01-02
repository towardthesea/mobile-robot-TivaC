#ifndef __STELLARISM4_H__
#define __STELLARISM4_H__

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"

#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"

#include "uartcom.h"

void ButtonHandler(void){
	unsigned long ulStatus;
//	ulStatus = GPIOPinIntStatus(GPIO_PORTF_BASE, true);
	ulStatus = GPIOIntStatus(GPIO_PORTF_BASE, true);
	
	if(ulStatus == 1){
		ulStatus = 0;
		
	}
	
	if(ulStatus == 16){
		ulStatus = 0;

	}
	
//	GPIOPinIntClear(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4);
	GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4);
}

void StellarisInit(void){
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	
//	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY_DD;
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;
	
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4);
	GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	
//	GPIOPinIntEnable(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4);
	GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4);
	GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4, GPIO_FALLING_EDGE);
//	GPIOPortIntRegister(GPIO_PORTF_BASE, ButtonHandler);
	GPIOIntRegister(GPIO_PORTF_BASE, ButtonHandler);
}

#endif

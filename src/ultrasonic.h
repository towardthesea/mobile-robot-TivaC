#ifndef __ULTRASONIC_H__
#define __ULTRASONIC_H__

#include <stdbool.h>
#include <stdint.h>

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"

#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/gpio.h"

void Timer5Handler(void){
	unsigned long ulStatus;
	ulStatus = TimerIntStatus(TIMER5_BASE, true);
	TimerIntClear(TIMER5_BASE, TIMER_TIMA_TIMEOUT);
	
	if(ulStatus){
		
	}
}

void UltrasonicInit(void){
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER5);
//	TimerConfigure(TIMER5_BASE, TIMER_CFG_32_BIT_PER);
	TimerConfigure(TIMER5_BASE, TIMER_CFG_PERIODIC);
	TimerLoadSet(TIMER5_BASE, TIMER_A, SysCtlClockGet()/10);
	TimerIntEnable(TIMER5_BASE, TIMER_TIMA_TIMEOUT);
	TimerIntRegister(TIMER5_BASE, TIMER_A, Timer5Handler);
	TimerEnable(TIMER5_BASE, TIMER_A);
}

#endif

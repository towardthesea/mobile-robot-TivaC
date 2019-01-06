#ifndef __MOTORDRIVER_H__
#define __MOTORDRIVER_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "stdio.h"

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"

#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/gpio.h"

#include "uartcom.h"

#define FORWARD 1
#define BACKWARD 0
#define MOTOR1 1
#define MOTOR2 2
#define MOTOR3 3
#define MOTOR4 4

unsigned long ulTimer4Cnt = 0;

void Motor1Init(void){
	SysCtlPWMClockSet(SYSCTL_PWMDIV_1);
	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_6|GPIO_PIN_7);
	GPIOPinConfigure(GPIO_PB6_T0CCP0);
	GPIOPinConfigure(GPIO_PB7_T0CCP1);
	GPIOPinTypeTimer(GPIO_PORTB_BASE, GPIO_PIN_6|GPIO_PIN_7);
	
	TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR|TIMER_CFG_A_PWM|TIMER_CFG_B_PWM);
	
	TimerLoadSet(TIMER0_BASE, TIMER_BOTH, 4095);

	TimerMatchSet(TIMER0_BASE, TIMER_BOTH, 4094);
	
	TimerEnable(TIMER0_BASE, TIMER_BOTH);
}

void Motor1Wire1(int iDuty){
	if(iDuty == 0) iDuty = 1;
	TimerMatchSet(TIMER0_BASE, TIMER_A, 4095 - iDuty);
}

void Motor1Wire2(int iDuty){
	if(iDuty == 0) iDuty = 1;
	TimerMatchSet(TIMER0_BASE, TIMER_B, 4095- iDuty);
}

void Motor2Init(void){
	SysCtlPWMClockSet(SYSCTL_PWMDIV_1);
	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
	
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_4|GPIO_PIN_5);
	GPIOPinConfigure(GPIO_PB4_T1CCP0);
	GPIOPinConfigure(GPIO_PB5_T1CCP1);
	GPIOPinTypeTimer(GPIO_PORTB_BASE, GPIO_PIN_4|GPIO_PIN_5);
	
	TimerConfigure(TIMER1_BASE, TIMER_CFG_SPLIT_PAIR|TIMER_CFG_A_PWM|TIMER_CFG_B_PWM);
	
	TimerLoadSet(TIMER1_BASE, TIMER_BOTH, 4095);

	TimerMatchSet(TIMER1_BASE, TIMER_BOTH, 4094);
	
	TimerEnable(TIMER1_BASE, TIMER_BOTH);
}

void Motor2Wire1(int iDuty){
	if(iDuty == 0) iDuty = 1;
	TimerMatchSet(TIMER1_BASE, TIMER_A, 4095- iDuty);
}

void Motor2Wire2(int iDuty){
	if(iDuty == 0) iDuty = 1;
	TimerMatchSet(TIMER1_BASE, TIMER_B, 4095 - iDuty);
}

void Motor3Init(void){
	SysCtlPWMClockSet(SYSCTL_PWMDIV_1);
	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
	
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1);
	GPIOPinConfigure(GPIO_PB0_T2CCP0);
	GPIOPinConfigure(GPIO_PB1_T2CCP1);
	GPIOPinTypeTimer(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1);
	
	TimerConfigure(TIMER2_BASE, TIMER_CFG_SPLIT_PAIR|TIMER_CFG_A_PWM|TIMER_CFG_B_PWM);
	
	TimerLoadSet(TIMER2_BASE, TIMER_BOTH, 4095);

	TimerMatchSet(TIMER2_BASE, TIMER_BOTH, 4094);
	
	TimerEnable(TIMER2_BASE, TIMER_BOTH);
}

void Motor3Wire1(int iDuty){
	if(iDuty == 0) iDuty = 1;
	TimerMatchSet(TIMER2_BASE, TIMER_A, 4095- iDuty);
}

void Motor3Wire2(int iDuty){
	if(iDuty == 0) iDuty = 1;
	TimerMatchSet(TIMER2_BASE, TIMER_B, 4095 - iDuty);
}

void Motor4Init(void){
	SysCtlPWMClockSet(SYSCTL_PWMDIV_1);
	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);
	
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_2|GPIO_PIN_3);
	GPIOPinConfigure(GPIO_PB2_T3CCP0);
	GPIOPinConfigure(GPIO_PB3_T3CCP1);
	GPIOPinTypeTimer(GPIO_PORTB_BASE, GPIO_PIN_2|GPIO_PIN_3);
	
	TimerConfigure(TIMER3_BASE, TIMER_CFG_SPLIT_PAIR|TIMER_CFG_A_PWM|TIMER_CFG_B_PWM);
	
	TimerLoadSet(TIMER3_BASE, TIMER_BOTH, 4095);

	TimerMatchSet(TIMER3_BASE, TIMER_BOTH, 4094);
	
	TimerEnable(TIMER3_BASE, TIMER_BOTH);
}

void Motor4Wire1(int iDuty){
	if(iDuty == 0) iDuty = 1;
	TimerMatchSet(TIMER3_BASE, TIMER_A, 4095- iDuty);
}

void Motor4Wire2(int iDuty){
	if(iDuty == 0) iDuty = 1;
	TimerMatchSet(TIMER3_BASE, TIMER_B, 4095 - iDuty);
}

void Moving(int numMotor, int direction, int pwmDuty){	
	switch(numMotor){
		case 1:
			if(direction){
				Motor1Wire1(pwmDuty);
				Motor1Wire2(0);
			}
			else{
				Motor1Wire1(0);
				Motor1Wire2(pwmDuty);
			}
			break;
		case 2:
			if(direction){
				Motor2Wire1(pwmDuty);
				Motor2Wire2(0);
			}
			else{
				Motor2Wire1(0);
				Motor2Wire2(pwmDuty);
			}
			break;
		case 3:
			if(direction){
				Motor3Wire1(pwmDuty);
				Motor3Wire2(0);
			}
			else{
				Motor3Wire1(0);
				Motor3Wire2(pwmDuty);
			}
			break;
		case 4:
			if(direction){
				Motor4Wire1(pwmDuty);
				Motor4Wire2(0);
			}
			else{
				Motor4Wire1(0);
				Motor4Wire2(pwmDuty);
			}
			break;
	}
}

unsigned long VoltToDuty(float Volt){
	float Volt_Ref = 3.35;
	
	return (unsigned long)(Volt * 1000 * 4096 / (Volt_Ref * 1000));
}

unsigned long VoltPercent(int iPercent){
	float Volt = 3.35 * iPercent / 100;
	
	return VoltToDuty(Volt);
}

//tBoolean step = 0;
_Bool step = 0;
unsigned long val1 = 0, val2 = 0;
unsigned long rps1, rps2;
const int freqEncoderCounter = 1;
const int pprEncoder = 10;	// Number of pulse per round of encoder
const float radius = 0.065;
const float L_base = 0.085;
float vel = 0, omega = 0;	// Linear and Rotational velocity of robot

void TimerHandler(void)
{
	unsigned long ulStatus;
	ulStatus = TimerIntStatus(TIMER4_BASE, true);
	TimerIntClear(TIMER4_BASE, TIMER_TIMA_TIMEOUT);
	
	if(ulStatus){
		if(!step)
		{
			val1 = val2 = 0;
		}
		else
		{
//			rps1 = val1 * 200 / 334;
//			rps2 = val2 * 200 / 334;
			rps1 = val1 * freqEncoderCounter / pprEncoder;
			rps2 = val2 * freqEncoderCounter / pprEncoder;
		}
		step = step ^ 1;
	}
}

void velocityCompute(void)
{
	vel = (rps1*radius + rps2*radius)/2.0;
	omega = (-rps1*radius + rps2*radius)/(2.0*L_base);
}

int spinCompute(float vel_set, float omega_set, int wheel)
{
	int rps1_set = 0, rps2_set = 0;
	rps1_set = (int)(vel_set - omega_set*L_base)/radius;
	rps2_set = (int)(vel_set + omega_set*L_base)/radius;

	if (wheel == 1)
		return rps1_set;
	else if (wheel == 2)
		return rps2_set;
	else
		return 0;
}

void EncoderInterrupt(void)
{
	unsigned long ulStatus;
//	ulStatus = GPIOPinIntStatus(GPIO_PORTA_BASE, true);
//	GPIOPinIntClear(GPIO_PORTA_BASE, GPIO_PIN_5|GPIO_PIN_7);
	ulStatus = GPIOIntStatus(GPIO_PORTA_BASE, true);
	GPIOIntClear(GPIO_PORTA_BASE, GPIO_PIN_5|GPIO_PIN_7);
	
	if(ulStatus == 128)	// PIN_7
	{
		val1++;
	}
	
	if(ulStatus == 32)	// PIN_5
	{
		val2++;
	}

	if(ulStatus == 160)	// both PIN_5 & PIN_7
	{
		val1++;
		val2++;
	}
}

void EncoderInit(void){
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER4);
//	TimerConfigure(TIMER4_BASE, TIMER_CFG_32_BIT_PER);
	TimerConfigure(TIMER4_BASE, TIMER_CFG_PERIODIC);
//	TimerLoadSet(TIMER4_BASE, TIMER_A, SysCtlClockGet()/200);
	TimerLoadSet(TIMER4_BASE, TIMER_A, SysCtlClockGet()/freqEncoderCounter);
	TimerIntEnable(TIMER4_BASE, TIMER_TIMA_TIMEOUT);
	TimerIntRegister(TIMER4_BASE, TIMER_A, TimerHandler);
	TimerEnable(TIMER4_BASE, TIMER_A);
	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_5|GPIO_PIN_7);
	GPIOPadConfigSet(GPIO_PORTA_BASE, GPIO_PIN_5|GPIO_PIN_7, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);

//	GPIOPinIntEnable(GPIO_PORTA_BASE, GPIO_PIN_5|GPIO_PIN_7);
	GPIOIntEnable(GPIO_PORTA_BASE, GPIO_PIN_5|GPIO_PIN_7);
	GPIOIntTypeSet(GPIO_PORTA_BASE, GPIO_PIN_5|GPIO_PIN_7, GPIO_FALLING_EDGE);

//	GPIOPortIntRegister(GPIO_PORTA_BASE, EncoderInterrupt);
	GPIOIntRegister(GPIO_PORTA_BASE, EncoderInterrupt);
}

float Set_Point;
float Error_Sum, Error_Now, Error_Del, Error_Last1, Error_Last2;
int Output1, Output2;
float Kp, Ki, Kd;

void PIDInit(float p, float i, float d){
	Set_Point = 0;
	Error_Sum = Error_Del = Error_Now = Error_Last1 = Error_Last2 = 0;
	Output1 = Output2 = 0;
	
	Kp = p;
	Ki = i;
	Kd = d;
}

int PIDController(float Set_Point, int rps, int Output, float Error){	
	
	Error_Now = Set_Point - rps;
	Error_Sum = Error_Now + Error;
	Error_Del = Error_Now - Error;
	Error = Error_Now;
		
	Output += (float)(Kp*Error_Now) + (float)(Ki*Error_Sum) + (float)(Kd*Error_Del);
		
	if(Output > 4095) Output = 4095;
	if(Output < 0) Output = 0;
	
	return Output;
}

#endif

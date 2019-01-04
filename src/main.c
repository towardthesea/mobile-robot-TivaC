#include <stdbool.h>
#include <stdint.h>

#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/can.h"

#include "driverlib/systick.h"

#include "uartcom.h"
#include "stellarism4.h"
#include "motordriver.h"
#include "CPUtemp.h"
#include "ultrasonic.h"
#include "buttons.h"
#include "rgb.h"

#define LED_RED GPIO_PIN_1
#define LED_BLUE GPIO_PIN_2
#define LED_GREEN GPIO_PIN_3

unsigned long systickCnt = 0;

int setPWMduty1, setPWMduty2;
int setRPS1, setRPS2;
int iread = 0;

void SysTickHandler(void);

int main(void){
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LED_RED|LED_BLUE|LED_GREEN);

	ROM_GPIOPinWrite(GPIO_PORTF_BASE, LED_RED|LED_GREEN|LED_BLUE, LED_RED);
	ROM_SysCtlDelay(5000000);
	ROM_GPIOPinWrite(GPIO_PORTF_BASE, LED_RED|LED_GREEN|LED_BLUE, 0);
	ROM_SysCtlDelay(5000000);
	ROM_GPIOPinWrite(GPIO_PORTF_BASE, LED_RED|LED_GREEN|LED_BLUE, LED_GREEN);
	ROM_SysCtlDelay(5000000);
	ROM_GPIOPinWrite(GPIO_PORTF_BASE, LED_RED|LED_GREEN|LED_BLUE, 0);
	ROM_SysCtlDelay(5000000);
	ROM_GPIOPinWrite(GPIO_PORTF_BASE, LED_RED|LED_GREEN|LED_BLUE, LED_BLUE);
	ROM_SysCtlDelay(5000000);
	ROM_GPIOPinWrite(GPIO_PORTF_BASE, LED_RED|LED_GREEN|LED_BLUE, 0);
	ROM_SysCtlDelay(5000000);

	UART0Init();
	StellarisInit();

	Motor3Init();
	Motor4Init();

	EncoderInit();
	PIDInit(.4, .2, .1);
	setPWMduty1 = setPWMduty2 = 1000;

	UltrasonicInit();
//
//	CPUTempInit();
//
	SysTickPeriodSet(SysCtlClockGet()/1000);
	SysTickEnable();
	SysTickIntRegister(SysTickHandler);
	SysTickIntEnable();

	while(1){
		if(dAvail){
			dAvail = 0;
			UART0SendStringWithoutEndLine("receive ");
			if (RXcmd == 0)
			{
				setPWMduty1 = setPWMduty2 = atoi(RXbuffer);
				itoa(setPWMduty1, TXbuffer);
			}
			else if (RXcmd == 1)
			{
				setRPS1 = setRPS2 = atoi(RXbuffer);
				itoa(setRPS1, TXbuffer);
			}
			UART0SendString(TXbuffer);
		}
//		Moving(MOTOR3, FORWARD, Output1);
//		Moving(MOTOR4, FORWARD, Output2);

//		Moving(MOTOR3, BACKWARD, Output1);
//		Moving(MOTOR4, BACKWARD, Output2);
		Moving(MOTOR3, BACKWARD, setPWMduty1);
		Moving(MOTOR4, BACKWARD, setPWMduty2);
	}
}

void SysTickHandler(void){
	systickCnt++;

	if(systickCnt % 20 == 0)
	{
		Output1 = PIDController(setRPS1, rps1, Output1, Error_Last1);
		Output2 = PIDController(setRPS2, rps2, Output2, Error_Last2);

		// TODO: convert Output to setPWMduty
		if (RXcmd==1)
		{
			setPWMduty1 = Output1;
			setPWMduty2 = Output2;
		}

		if (RXcmd==0)
			UART0SendStringWithoutEndLine("setPMW ");
		else if(RXcmd==1)
			UART0SendStringWithoutEndLine("setRPS ");
		UART0SendStringWithoutEndLine(RXbuffer);
		UART0SendStringWithoutEndLine(" m-rps ");
		itoa(rps1, TXbuffer);
		UART0SendStringWithoutEndLine(TXbuffer);
		UART0SendStringWithoutEndLine(" ");
		itoa(rps2, TXbuffer);

		if (RXcmd == 0)
			UART0SendString(TXbuffer);
		else if (RXcmd == 1)
		{
			UART0SendStringWithoutEndLine(TXbuffer);
			UART0SendStringWithoutEndLine(" Output ");
			itoa(Output1, TXbuffer);
			UART0SendStringWithoutEndLine(TXbuffer);
			UART0SendStringWithoutEndLine(" ");
			itoa(Output2, TXbuffer);
			UART0SendString(TXbuffer);
		}
	}

	if(systickCnt == 1000){
		systickCnt = 0;
		GPIOPinWrite(GPIO_PORTF_BASE, LED_GREEN, GPIOPinRead(GPIO_PORTF_BASE, LED_GREEN)^8);
//		readTemp();
	}
}

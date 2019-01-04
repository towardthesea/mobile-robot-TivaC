#ifndef __UARTCOM_H__
#define __UARTCOM_H__

#include <stdbool.h>
#include <stdint.h>

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"

#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"

#include <string.h>
#include <stdlib.h>
#include "stdio.h"

char txt[20] = "UART0 Start OK!";
int i;
char RXbuffer[80], TXbuffer[80];
int bufIndex = 0, RXcmd = 0;
//tBoolean dAvail = 0;
_Bool dAvail = 0;

static void reverse( char s[] )
{
  int i, j ;
  char c ;

  for ( i = 0, j = strlen(s)-1 ; i < j ; i++, j-- )
  {
    c = s[i] ;
    s[i] = s[j] ;
    s[j] = c ;
  }
}

extern void itoa( unsigned long n, char s[] )
{
  int i, sign ;

  if ( (sign = n) < 0 )  /* record sign */
  {
    n = -n;          /* make n positive */
  }

  i = 0;
  do
  {       /* generate digits in reverse order */
    s[i++] = n % 10 + '0';   /* get next digit */
  } while ((n /= 10) > 0) ;     /* delete it */

  if (sign < 0 )
  {
    s[i++] = '-';
  }

  s[i] = '\0';

  reverse( s ) ;
}

void UART0IntHandler(void){	
	UARTIntClear(UART0_BASE, UART_INT_RX|UART_INT_RT);
	
	while(UARTCharsAvail(UART0_BASE)){
		char c = UARTCharGet(UART0_BASE);
		if(c == 13 || c == 10) break;
		RXbuffer[bufIndex] = c;
		bufIndex++;
	}
		
	RXbuffer[bufIndex] = '\0';
	if(RXbuffer[0] == 'r')	// set rps
	{
//		bufIndex = 1;
		memmove(RXbuffer, RXbuffer+1, strlen(RXbuffer+1)+1);
		RXcmd = 1;
	}
//	else
	bufIndex = 0;
	dAvail = 1;
}

void UART0SendStringWithoutEndLine(char* txt){
	for(i = 0; txt[i] != '\0'; i++) UARTCharPut(UART0_BASE, txt[i]);
}

void UART0SendString(char* txt){
	for(i = 0; txt[i] != '\0'; i++) UARTCharPut(UART0_BASE, txt[i]);
	UARTCharPut(UART0_BASE, 13);
	UARTCharPut(UART0_BASE, 10);
}

void UART0Init(void){
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	
	GPIOPinConfigure(GPIO_PA0_U0RX);
	GPIOPinConfigure(GPIO_PA1_U0TX);
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0|GPIO_PIN_1);
	
	UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
	                    UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
											
	UARTIntEnable(UART0_BASE, UART_INT_RX|UART_INT_RT);
	UARTIntRegister(UART0_BASE, UART0IntHandler);
	
	UART0SendString(txt);
}

#endif

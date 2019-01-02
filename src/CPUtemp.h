#ifndef __CPUTEMP_H__
#define __CPUTEMP_H__

#include <stdbool.h>
#include <stdint.h>

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"

#include "driverlib/sysctl.h"
#include "driverlib/adc.h"

//unsigned long ulADC0Value[4];
uint32_t ulADC0Value[4];
unsigned long ulTempAvg;
unsigned long ulTempValueC;

void CPUTempInit(void){
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

//	SysCtlADCSpeedSet(SYSCTL_ADCSPEED_125KSPS); // 250
//	ADCClockConfigSet(ADC0_BASE, ADC_CTL_TS, );

	ADCSequenceDisable(ADC0_BASE, 1);
	ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_TS);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_TS);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_TS);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 3, ADC_CTL_TS | ADC_CTL_IE | ADC_CTL_END);
	ADCSequenceEnable(ADC0_BASE, 1);
}

void readTemp(void){
	ADCIntClear(ADC0_BASE, 1);
	ADCProcessorTrigger(ADC0_BASE, 1);
  
  while(!ADCIntStatus(ADC0_BASE, 1, false))
  {    
  }

  ADCSequenceDataGet(ADC0_BASE, 1, ulADC0Value);
  ulTempAvg = (ulADC0Value[0] + ulADC0Value[1] + ulADC0Value[2] + ulADC0Value[3] + 2)/4;
  ulTempValueC = (1475 - ((2475 * ulTempAvg)) / 4096)/10;
}

#endif

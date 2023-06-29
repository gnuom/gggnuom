
#define	__EXT_GETADC_
#include "Globals.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
void GetADC_Init(void)
{
	// 设置ADC的运行模式
	ADC_ConfigRunMode(ADC_CLK_DIV_4, ADC_RESULT_LEFT);	// 设置ADC时钟为系统时钟的256分频，ADC结果为左对齐
	ADC_DisableLDO();									// LDO禁止，ADC参考电压为电源电压

	// 设置ADC转换通道
	GPIO_SET_MUX_MODE(cnPortBoilerNTC_CFG, cnPortBoilerNTC_MUX);
	//GPIO_SET_MUX_MODE(cnPortPump_CFG, cnPortPump_MUX);

	//开启ADC
	ADC_EnableChannel(cnADC_chnBoilerNTC);	
	ADC_Start();
}

uint16_t Read_ADC(uint8_t chn)
{
	uint8_t i;
	uint16_t ADCMin, ADCMax;
	uint16_t ADCSum;
	uint16_t ADCValue;

	//IRQ_ALL_DISABLE();

	ADC_EnableChannel(chn);
	_nop_();
	_nop_();
	_nop_();
	_nop_();

	ADCMax = 0;
	ADCMin = 0xFFFF;
	ADCSum = 0;
	for(i=0; i<10; i++)
	{
	    _nop_();
	    _nop_();
		ADC_GO();								//开始转换
		while(ADC_IS_BUSY) _nop_();
	    ADCValue = ADC_GetADCResult();
		ADCSum += ADCValue;
		if(ADCValue > ADCMax)
			ADCMax = ADCValue;
		if(ADCValue < ADCMin)
			ADCMin = ADCValue;
	}

	ADCSum -= ADCMax;
	ADCSum -= ADCMin;
	ADCSum = ADCSum >> 3;

	//IRQ_ALL_ENABLE();

	#if	0//def cnTestHeat
	ADCSum = 372;
	#endif
	
	return ADCSum;
}




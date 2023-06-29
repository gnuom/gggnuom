
#define	__EXT_GETADC_
#include "Globals.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
void GetADC_Init(void)
{
	// ����ADC������ģʽ
	ADC_ConfigRunMode(ADC_CLK_DIV_4, ADC_RESULT_LEFT);	// ����ADCʱ��Ϊϵͳʱ�ӵ�256��Ƶ��ADC���Ϊ�����
	ADC_DisableLDO();									// LDO��ֹ��ADC�ο���ѹΪ��Դ��ѹ

	// ����ADCת��ͨ��
	GPIO_SET_MUX_MODE(cnPortBoilerNTC_CFG, cnPortBoilerNTC_MUX);
	//GPIO_SET_MUX_MODE(cnPortPump_CFG, cnPortPump_MUX);

	//����ADC
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
		ADC_GO();								//��ʼת��
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




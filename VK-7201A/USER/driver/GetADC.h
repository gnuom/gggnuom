
#ifndef	__H_GETADC_
#define	__H_GETADC_

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef	__EXT_GETADC_
#define	GETADC_EXT
#else
#define GETADC_EXT		extern
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum {
	cnADC_NULL = 0,
	cnADC_BoilerNTC,
	//cnADC_Pump,

	cnADC_Max
}ADC_CHN_T;

#if 0
#define cnPortBoilerNTC_CFG		P10CFG
#define	cnPortBoilerNTC_MUX		GPIO_P10_MUX_AN8
#define	cnADC_chnBoilerNTC		ADC_CH_8		// 锅炉NTC
#else
#define cnPortBoilerNTC_CFG		P51CFG
#define	cnPortBoilerNTC_MUX		GPIO_P51_MUX_AN40
#define	cnADC_chnBoilerNTC		ADC_CH_40		// 锅炉NTC     P20 AN16 -> P51 AN40
#endif
//#define cnPortPump_CFG			P24CFG
//#define cnPortPump_MUX			GPIO_P24_MUX_AN20
//#define cnADC_chnPump			ADC_CH_20		// 水泵工作电流<缺水检测>


#define Read_BoilerNTC_ADC()	Read_ADC(cnADC_chnBoilerNTC)
//#define Read_Pump_ADC()			Read_ADC(cnADC_chnPump)


///////////////////////////////////////////////////////////////////////////////////////////////////
GETADC_EXT void GetADC_Init(void);
GETADC_EXT uint16_t Read_ADC(uint8_t chn);



#endif



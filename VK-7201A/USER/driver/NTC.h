
#ifndef	__H_NTC_
#define	__H_NTC_

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef	__EXT_NTC_
#define	NTC_EXT
#else
#define NTC_EXT					extern
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
enum {
	cnNTC_Err_OK = 0,

	cnNTC_Err = 0xC8,				// NTC错误编码起始
	cnNTC_Err_RxShort = 0xFB,		// 短路：NTC电阻很小
	cnNTC_Err_RxOpen = 0xFC,		// 开路：NTC电阻很大

	cnNTC_Err_TempHigh = 0xFD,		// 超高温
	cnNTC_Err_TempLow = 0xFE,		// 超低温

	cnNTC_Err_Max
};


#define cnGetNTCNum				200	//50	//85
typedef struct {
	uint8_t NTCErr;					// NTC错误代码
	uint8_t TempHighCnt;			// 高温计数器
	uint8_t TempLowCnt;				// 低温计数器
	uint8_t temp;					// cnGetNTCNum*cnTBaseT_10ms=100ms平均温度
	uint8_t tempBuf[cnGetNTCNum];	// cnGetNTCNum个温度缓存
}Temp_NTC_t;
#define cnTempOffset			1	// 温度误差±2℃
NTC_EXT Temp_NTC_t RAM_xDATA tempNTC;
#define GetTempNTC()			(tempNTC.temp)

#define IsNTCErr()				(tempNTC.NTCErr > cnNTC_Err)
#define IsNTCBroken()			((tempNTC.NTCErr == cnNTC_Err_RxShort) || (tempNTC.NTCErr == cnNTC_Err_RxOpen))
#define IsNTCTempHi()			(tempNTC.NTCErr == cnNTC_Err_TempHigh)


///////////////////////////////////////////////////////////////////////////////////////////////////
NTC_EXT void NTC_Init(void);
NTC_EXT void NTC_Run_Task(void);

#endif






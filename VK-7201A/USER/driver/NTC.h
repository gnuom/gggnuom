
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

	cnNTC_Err = 0xC8,				// NTC���������ʼ
	cnNTC_Err_RxShort = 0xFB,		// ��·��NTC�����С
	cnNTC_Err_RxOpen = 0xFC,		// ��·��NTC����ܴ�

	cnNTC_Err_TempHigh = 0xFD,		// ������
	cnNTC_Err_TempLow = 0xFE,		// ������

	cnNTC_Err_Max
};


#define cnGetNTCNum				200	//50	//85
typedef struct {
	uint8_t NTCErr;					// NTC�������
	uint8_t TempHighCnt;			// ���¼�����
	uint8_t TempLowCnt;				// ���¼�����
	uint8_t temp;					// cnGetNTCNum*cnTBaseT_10ms=100msƽ���¶�
	uint8_t tempBuf[cnGetNTCNum];	// cnGetNTCNum���¶Ȼ���
}Temp_NTC_t;
#define cnTempOffset			1	// �¶�����2��
NTC_EXT Temp_NTC_t RAM_xDATA tempNTC;
#define GetTempNTC()			(tempNTC.temp)

#define IsNTCErr()				(tempNTC.NTCErr > cnNTC_Err)
#define IsNTCBroken()			((tempNTC.NTCErr == cnNTC_Err_RxShort) || (tempNTC.NTCErr == cnNTC_Err_RxOpen))
#define IsNTCTempHi()			(tempNTC.NTCErr == cnNTC_Err_TempHigh)


///////////////////////////////////////////////////////////////////////////////////////////////////
NTC_EXT void NTC_Init(void);
NTC_EXT void NTC_Run_Task(void);

#endif






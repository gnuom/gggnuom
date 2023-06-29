
#define	__EXT_STATION_
#include	"Globals.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
volatile uint8_t RAM_DATA FuncNum1st = cnFuncNumInit;
volatile uint8_t RAM_DATA FuncNum2nd = cnFuncNumInit;
volatile uint8_t RAM_DATA FuncNum3rd = cnFuncNumInit;

/************************************************************
�������������ù���ģʽ
*************************************************************/
void SetWorkMode(uint8_t mode)
{
	FuncNum3rd = FuncNum2nd;
	FuncNum2nd = FuncNum1st;
	FuncNum1st = mode;
}

/************************************************************
�����������ָ�ԭ����ģʽ
*************************************************************/
void ResumeWorkMode(void)
{
	FuncNum1st = FuncNum2nd;
	FuncNum2nd = FuncNum3rd;
}


/************************************************************
�����������պ���
*************************************************************/
RET_CODE NullRoutine(MsgValue_t value)	
{
	value = value;
	return cnFailure;
}


//////////////////////////////////////////////////////////////////
RET_CODE StationRun(uint8_t Msg, MsgValue_t MsgValue)
{
	RET_CODE retCode = cnFailure;

	switch(FuncNum1st)
	{
	case cnFuncNumInit:			// �ϵ��ʼ��
		retCode = StationRun_Init(Msg, MsgValue);
		break;
	case cnFuncNumIdle:			// Idle����ģʽ
		retCode = StationRun_Idle(Msg, MsgValue);
		break;
	case cnFuncNumWorking:		// Working����ģʽ
		retCode = StationRun_Working(Msg, MsgValue);
		break;
	case cnFuncNumEmergency:	// Emergency�����¼�
		retCode = StationRun_Emergency(Msg, MsgValue);
		break;
		
	default:
		return cnFailure;
	}

	//cnFuncNumCommon,			// ��ģʽ���ܺţ�ֻΪ��������Ϣ
	if(retCode == cnNoRespond)
	{
		retCode = StationRun_Common(Msg, MsgValue);
	}

	return retCode;
}




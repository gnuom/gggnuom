
#define	__EXT_STATION_
#include	"Globals.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
volatile uint8_t RAM_DATA FuncNum1st = cnFuncNumInit;
volatile uint8_t RAM_DATA FuncNum2nd = cnFuncNumInit;
volatile uint8_t RAM_DATA FuncNum3rd = cnFuncNumInit;

/************************************************************
公共函数：设置工作模式
*************************************************************/
void SetWorkMode(uint8_t mode)
{
	FuncNum3rd = FuncNum2nd;
	FuncNum2nd = FuncNum1st;
	FuncNum1st = mode;
}

/************************************************************
公共函数：恢复原工作模式
*************************************************************/
void ResumeWorkMode(void)
{
	FuncNum1st = FuncNum2nd;
	FuncNum2nd = FuncNum3rd;
}


/************************************************************
公共函数：空函数
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
	case cnFuncNumInit:			// 上电初始化
		retCode = StationRun_Init(Msg, MsgValue);
		break;
	case cnFuncNumIdle:			// Idle待机模式
		retCode = StationRun_Idle(Msg, MsgValue);
		break;
	case cnFuncNumWorking:		// Working工作模式
		retCode = StationRun_Working(Msg, MsgValue);
		break;
	case cnFuncNumEmergency:	// Emergency紧急事件
		retCode = StationRun_Emergency(Msg, MsgValue);
		break;
		
	default:
		return cnFailure;
	}

	//cnFuncNumCommon,			// 非模式功能号，只为处理公共消息
	if(retCode == cnNoRespond)
	{
		retCode = StationRun_Common(Msg, MsgValue);
	}

	return retCode;
}




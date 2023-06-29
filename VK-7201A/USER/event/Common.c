
#define	__EXT_COMMON_
#include "Globals.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
void Common_Init(void)
{
	ResetWorkingPara();
}

void Common_Run_Task(void)
{
}


///////////////////////////////////////////////////////////////////////////////////////////////////
static RET_CODE Common_MsgFunc_Key_Power(MsgValue_t MsgValue)
{
	MsgValue = MsgValue;

	return cnSuccess;
}

static RET_CODE Common_MsgFunc_Key_Menu(MsgValue_t MsgValue)
{
	MsgValue = MsgValue;

	return cnSuccess;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
// cnFuncNumCommon,				// Commonģʽ
RET_CODE StationRun_Common(uint8_t Msg, MsgValue_t MsgValue)
{
	RET_CODE retCode = cnFailure;

	switch(Msg)
	{
	case cnMsgKeyPower:
		retCode = Common_MsgFunc_Key_Power(MsgValue);
		break;
	case cnMsgKeyMenu:
		retCode = Common_MsgFunc_Key_Menu(MsgValue);
		break;
		
	default:
		retCode = cnNoRespond;
		break;
	}

	return retCode;
}



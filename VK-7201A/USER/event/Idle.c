
#define	__EXT_IDLE_
#include "Globals.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
static uint16_t IdleRunTmr;

void Idle_Con(void)
{
	Heater_Init();
	TurnOffAllLed();

	IdleRunTmr = 0;
	SetWorkMode(cnFuncNumIdle);
}

void Idle_De(void)
{
}

void Idle_Run_Task(void)
{
	if(!IsCurWorkModeIdle())
	{
		IdleRunTmr = 0;
		return;
	}

	++IdleRunTmr;
	if(IdleRunTmr > cnIdleRunT)
	{
		IdleRunTmr = 0;

		//...
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////
static RET_CODE Idle_MsgFunc_Key_Power(MsgValue_t MsgValue)
{
	if(Get_Key_IsRelease(MsgValue))
	{
		Set_Key_Processed();

		Idle_De();
		Working_Con();
	}
	else if(Get_Key_IsPressed(MsgValue, cnKeyPressedT_5s))
	{
		Set_Key_Processed();

		//...
	}
	
	return cnSuccess;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// cnFuncNumIdle,				// Idle´ý»úÄ£Ê½
RET_CODE StationRun_Idle(uint8_t Msg, MsgValue_t MsgValue)
{
	RET_CODE retCode = cnFailure;

	switch(Msg)
	{
	case cnMsgKeyPower:
		retCode = Idle_MsgFunc_Key_Power(MsgValue);
		break;
	case cnMsgKeyMenu:
		retCode = NullRoutine(MsgValue);
		break;
		
	default:
		retCode = cnNoRespond;
		break;
	}

	return retCode;
}



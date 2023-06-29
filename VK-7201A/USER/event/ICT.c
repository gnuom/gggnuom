
#define	__EXT_ICT_
#include "Globals.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
#define cnICTRunBaseT		cnTBaseT_200ms
static uint8_t RAM_xDATA ICTRunStep, ICTRunTmr;
static bool_t bICTKey_Power = FALSE;
static bool_t bICTKey_6oz = FALSE;
static bool_t bICTKey_8oz = FALSE;
static bool_t bICTKey_10oz = FALSE;
static bool_t bICTKey_12oz = FALSE;

void ICT_Con(void)
{
	bICTKey_Power = FALSE;
	bICTKey_6oz = FALSE;
	bICTKey_8oz = FALSE;
	bICTKey_10oz = FALSE;
	bICTKey_12oz = FALSE;

	ICTRunTmr = 0;
	ICTRunStep = cnICTStep_Start;
	TurnOffAllLed();
	
	SetWorkMode(cnFuncNumICT);
}


void ICT_De(void)
{
	//LedConfig();
}

void ICT_Run_Task(void)
{
	uint16_t datDigTube = 0;
	bool_t bShowICTDat = TRUE;
	
	if(IsCurWorkModeICT())
	{
		switch(ICTRunStep)
		{
		case cnICTStep_Start:			// ICT测试开始：打开所有显示
			{
				TurnOnAllLed();

				++ICTRunTmr;
				if(ICTRunTmr >= (1000UL/cnICTRunBaseT))
				{
					ICTRunTmr = 0;
					TurnOffAllLed();
					ICTRunStep = cnICTStep_KeyPressed;
				}
			}
			break;
		
		case cnICTStep_KeyPressed:
		default:
			{
				if(IsLockSWOpen())
					TurnOnLedWLackFlash100ms();
				else
					TurnOnLedWLack();

				if(IsNTCErr())
					TurnOnLedTempHiFlash100ms();
				else
					TurnOnLedTempHi();
			}
			break;
		}

	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
static RET_CODE ICT_MsgFunc_Key_Power(uint16_t MsgValue)
{
	if(ICTRunStep != cnICTStep_KeyPressed)
		return cnSuccess;
	
	if(Get_Key_IsRelease(MsgValue))
	{
		Set_Key_Processed();
		
		Heat_Stop();
		Pump_Stop();

		bICTKey_Power = ~bICTKey_Power;
		if(bICTKey_Power)
		{
			TurnOnLedPowerR();
		}
		else
		{
			TurnOffLedPowerR();
		}
	}
	else if(Get_Key_IsPressed(MsgValue, cnKeyPressedT_3s))
	{
		Set_Key_Processed();

		ICTRunTmr = 0;
		ICTRunStep = cnICTStep_Start;
		TurnOffAllLed();
	}

	return cnSuccess;
}

static RET_CODE ICT_MsgFunc_Key_6oz(uint16_t MsgValue)
{
	if(ICTRunStep != cnICTStep_KeyPressed)
		return cnSuccess;
		
	if(Get_Key_IsRelease(MsgValue))
	{
		Set_Key_Processed();

		bICTKey_6oz = ~bICTKey_6oz;
		if(bICTKey_6oz)
		{
			TurnOnLed6ozB();
		}
		else
		{
			TurnOffLed6ozB();
		}
	}
	else if(Get_Key_IsPressed(MsgValue, cnKeyPressedT_3s))
	{
		Set_Key_Processed();

		// 加热
	}

	return cnSuccess;
}

static RET_CODE ICT_MsgFunc_Key_8oz(uint16_t MsgValue)
{
	if(ICTRunStep != cnICTStep_KeyPressed)
		return cnSuccess;
		
	if(Get_Key_IsRelease(MsgValue))
	{
		Set_Key_Processed();

		bICTKey_8oz = ~bICTKey_8oz;
		if(bICTKey_8oz)
		{
			TurnOnLed8ozB();
		}
		else
		{
			TurnOffLed8ozB();
		}
	}

	return cnSuccess;
}

static RET_CODE ICT_MsgFunc_Key_10oz(uint16_t MsgValue)
{
	if(ICTRunStep != cnICTStep_KeyPressed)
		return cnSuccess;
		
	if(Get_Key_IsRelease(MsgValue))
	{
		Set_Key_Processed();

		bICTKey_10oz = ~bICTKey_10oz;
		if(bICTKey_10oz)
		{
			TurnOnLed10ozB();
		}
		else
		{
			TurnOffLed10ozB();
		}
	}

	return cnSuccess;
}

static RET_CODE ICT_MsgFunc_Key_12oz(uint16_t MsgValue)
{
	if(ICTRunStep != cnICTStep_KeyPressed)
		return cnSuccess;
		
	if(Get_Key_IsRelease(MsgValue))
	{
		Set_Key_Processed();

		bICTKey_12oz = ~bICTKey_12oz;
		if(bICTKey_12oz)
		{
			TurnOnLed12ozB();
		}
		else
		{
			TurnOffLed12ozB();
		}
	}
	else if(Get_Key_IsPressed(MsgValue, cnKeyPressedT_3s))
	{
		Set_Key_Processed();

		// 水泵
	}

	return cnSuccess;
}

static RET_CODE ICT_MsgFunc_Dct_LockSW(uint16_t MsgValue)
{
	MsgValue = MsgValue;

	if(IsLockSWOpen())
		TurnOnLedWLackFlash100ms();
	else
		TurnOnLedWLack();
	
	return cnSuccess;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
On_Command ROM_DATA ICTTable[]=
{
	{ cnMsgKeyPower,			ICT_MsgFunc_Key_Power },
	{ cnMsgKey6oz,				ICT_MsgFunc_Key_6oz },
	{ cnMsgKey8oz,				ICT_MsgFunc_Key_8oz },
	{ cnMsgKey10oz,				ICT_MsgFunc_Key_10oz },
	{ cnMsgKey12oz,				ICT_MsgFunc_Key_12oz },

	{ cnMsgDct_LockSW,			ICT_MsgFunc_Dct_LockSW },
	{ cnMsgKeyCmbICT,			NullRoutine },
	{ cnMsgKeyCmbFlush,			NullRoutine },
	
	{ cnMsgMax, 			NULL }
};



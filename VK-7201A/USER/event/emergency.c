
#define	__EXT_EMERGENCY_
#include "Globals.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
#define	cnEmergencyRunT_NTCBroken			(1*60UL*(1000UL/cnTBaseT_200ms))
#define cnEmergencyRunT_TempHi				(3*60UL*(1000UL/cnTBaseT_200ms))

static uint16_t EmergencyRunTmr;
Emergency_T emergencyType;
void Emergency_Con(void)
{
	Heat_Stop();

	SetWorkMode(cnFuncNumEmergency);
}

void Emergency_NTCCon(void)
{
	TurnOnLedPowerFlash300ms();

	emergencyType = cnEmergencyType_NTCBroken;
	EmergencyRunTmr = cnEmergencyRunT_NTCBroken;
	Emergency_Con();
}

void Emergency_TempHiCon(void)
{
	TurnOnLedPower();
	TurnOnLedCookedAllFlash300ms();
	TurnOnLedCookedMedFlash300ms();
	TurnOnLedCookedHotFlash300ms();
	TurnOnLedSteamFlash300ms();
	TurnOnLedCookingFlash300ms();

	emergencyType = cnEmergencyType_TempHi;
	EmergencyRunTmr = cnEmergencyRunT_TempHi;
	Emergency_Con();
}

void Emergency_De(void)
{
	TurnOffAllLed();
	TurnOnLedPower();

	EmergencyRunTmr = 0;
	emergencyType = cnEmergencyType_Null;
}

enum {
	cnEmergency_ToNothing = 0,
	cnEmergency_ToIdleMode,
	cnEmergency_ToResumeWorkMode,

	cnEmergency_ToMax
};
void Emergency_Run_Task(void)
{
	uint8_t ToSomeWorkMode;

	if(IsCurWorkModeEmergency())
	{
		Heat_Stop();

		ToSomeWorkMode = cnEmergency_ToNothing;
		if(EmergencyRunTmr == 0)
			ToSomeWorkMode = cnEmergency_ToIdleMode;
		else
		{
			--EmergencyRunTmr;
		
			switch(emergencyType)
			{
			case cnEmergencyType_NTCBroken:
				{
					if(!IsNTCBroken())
						ToSomeWorkMode = cnEmergency_ToIdleMode;
				}
				break;
			case cnEmergencyType_TempHi:
				{
					if(!IsHeaterTempHi())
						ToSomeWorkMode = cnEmergency_ToIdleMode;
				}
				break;
			default:
				break;
			}
		}

		if(ToSomeWorkMode == cnEmergency_ToIdleMode)
		{
			Emergency_De();
			Idle_Con();
		}
		else if(ToSomeWorkMode == cnEmergency_ToResumeWorkMode)
		{
			Emergency_De();
			ResumeWorkMode();
			switch(GetCurWorkMode())
			{
			case cnFuncNumWorking:
				Working_Con();
				break;
			default:
				Idle_Con();
				break;
			}
		}
	}
}

static RET_CODE Emergency_MsgFunc_Key_Power(MsgValue_t MsgValue)
{
	if(Get_Key_IsRelease(MsgValue))
	{
		Set_Key_Processed();

		Emergency_De();
		Idle_Con();
	}
	
	return cnSuccess;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// cnFuncNumEmergency,				// ½ô¼±Ä£Ê½
RET_CODE StationRun_Emergency(uint8_t Msg, MsgValue_t MsgValue)
{
	RET_CODE retCode = cnFailure;

	switch(Msg)
	{
	case cnMsgKeyPower:
		retCode = Emergency_MsgFunc_Key_Power(MsgValue);
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



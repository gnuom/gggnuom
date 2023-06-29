
#define	__EXT_WORKING_
#include "Globals.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
#define cnWorkingRunTBase			cnTBaseT_100ms
#define	cnWorkingRunT				(3*60UL*60UL*(1000UL/cnWorkingRunTBase))	// 分钟
#define cnWorkingSelectT			(5*60UL*(1000UL/cnWorkingRunTBase))		// 
#define cnWorkingEndingT			(3*60UL*(1000UL/cnWorkPHTBase))		// 


static uint32_t WorkingRunTmr;
bool_t bIsWorkingStop;

Working_t RAM_xDATA Working;

#define cnTBoil			98		// 沸点温度

///////////////////////////////////////////////////////////////////////////////////////////////////
// 因为蛋清凝固的温度是70+°C，蛋黄凝固的温度是60+°C，所以控制在水温60-70°C之间即可做出温泉蛋
static ROM_DATA WorkPara_t WorkingPara_Tab[cnWorkType_Max][4] = {
//		PreHeat				cooking1			cooking2			cooking3
	{ { 0, 0 },				{ 0, 0 },			{ 0, 0 }, 			{ 0, 0 } },	// cnWorkType_Null
	{ { 99, (15*60UL) },	{ 99, (9*60UL) },	{ 0, 0 }, 			{ 0, 0 } },	// cnWorkType_CookedAll,	// 全熟
	{ { 99, (15*60UL) },	{ 99, (5*60UL) },	{ 0, 0 }, 			{ 0, 0 } },	// cnWorkType_CookedMed,	// 半熟
	{ { 63, (15*60UL) },	{ 63, (6*60UL) },	{ 70, (12*60UL) }, 	{ 0, 0 } },	// cnWorkType_CookedHot,	// 温泉蛋
	{ { 68, (15*60UL) },	{ 68, (60*60UL) },	{ 0, 0 }, 			{ 0, 0 } },	// cnWorkType_Steam,		// 蒸鸡胸肉
	{ { 99, (15*60UL) },	{ 99, (20*60UL) },	{ 0, 0 }, 			{ 0, 0 } },	// cnWorkType_Cooking,		// 蒸煮蔬菜
};

static void GetWorkingTempTimePara(uint8_t type, uint8_t cook)
{
	Working.para.temp = WorkingPara_Tab[type][cook].temp;
	Working.para.tmrms = WorkingPara_Tab[type][cook].tmrms * (1000UL/cnWorkPHTBase);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void Working_Con(void)
{
	TurnOnLedPower();

	Working.status = cnWorkStatus_Select;
	if(!IsWorkingTypeValid())
		Working.type = cnWorkType_CookedAll;
	
	GetWorkingTempTimePara(Working.type, 0);
	TurnOffHeater();

	WorkingRunTmr = 0;
	bIsWorkingStop = FALSE;
	SetWorkMode(cnFuncNumWorking);
}

void Working_De(void)
{
	// 存储总出水量
	bIsWorkingStop = FALSE;
	ResetWorkingPara();
	Working.status = cnWorkStatus_Stop;
	TurnOffHeater();
}

void Working_Run_Task(void)
{
	if(!IsCurWorkModeWorking())
	{
		WorkingRunTmr = 0;
		return;
	}

	++WorkingRunTmr;
	if((bIsWorkingStop == TRUE) || (WorkingRunTmr > cnWorkingRunT)
		|| ((Working.status == cnWorkStatus_Select) && (WorkingRunTmr > cnWorkingSelectT)))
	{	
		// 工作cnWorkingRunT，强制待机:停止加热和出水
		Working_De();
		Idle_Con();
		return;
	}

	if(IsNTCBroken())
	{
		Emergency_NTCCon();
		return;
	}	
	else if(IsHeaterTempHi())
	{
		Emergency_TempHiCon();
		return;
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////
static void Working_ShowStatusDoing(void)
{
	TurnOnLedPower();
	
	switch(Working.status)
	{
	case cnWorkStatus_PreHeat:				// 先加热
	case cnWorkStatus_Ready: 				// 温度已经达到
	case cnWorkStatus_DoCooking1:			// 正在煮蛋: 第一阶段
	case cnWorkStatus_DoCooking2:			// 正在煮蛋: 第二阶段
	case cnWorkStatus_DoCooking3:			// 正在煮蛋: 第三阶段
		{
			if(Working.type == cnWorkType_CookedAll)	// 全熟
				TurnOnLedCookedAllBreath();
			else
				TurnOffLedCookedAll();
			if(Working.type == cnWorkType_CookedMed)	// 半熟
				TurnOnLedCookedMedBreath();
			else
				TurnOffLedCookedMed();
			if(Working.type == cnWorkType_CookedHot)	// 温泉蛋
				TurnOnLedCookedHotBreath();
			else
				TurnOffLedCookedHot();
			if(Working.type == cnWorkType_Steam)		// 蒸
				TurnOnLedSteamBreath();
			else
				TurnOffLedSteam();
			if(Working.type == cnWorkType_Cooking)		// 蒸煮
				TurnOnLedCookingBreath();
			else
				TurnOffLedCooking();
		}
		break;

	case cnWorkStatus_Ending:
		{
			if(Working.type == cnWorkType_CookedAll)	// 全熟
				TurnOnLedCookedAllFlash500ms();
			else
				TurnOffLedCookedAll();
			if(Working.type == cnWorkType_CookedMed)	// 半熟
				TurnOnLedCookedMedFlash500ms();
			else
				TurnOffLedCookedMed();
			if(Working.type == cnWorkType_CookedHot)	// 温泉蛋
				TurnOnLedCookedHotFlash500ms();
			else
				TurnOffLedCookedHot();
			if(Working.type == cnWorkType_Steam)		// 蒸
				TurnOnLedSteamFlash500ms();
			else
				TurnOffLedSteam();
			if(Working.type == cnWorkType_Cooking)		// 蒸煮
				TurnOnLedCookingFlash500ms();
			else
				TurnOffLedCooking();
		}
		break;

	case cnWorkStatus_Stop: 			// 停止出水/加热 
	case cnWorkStatus_Select:
	default:
		{
			if(Working.type == cnWorkType_CookedAll)	// 全熟
				TurnOnLedCookedAll();
			else
				TurnOffLedCookedAll();
			if(Working.type == cnWorkType_CookedMed)	// 半熟
				TurnOnLedCookedMed();
			else
				TurnOffLedCookedMed();
			if(Working.type == cnWorkType_CookedHot)	// 温泉蛋
				TurnOnLedCookedHot();
			else
				TurnOffLedCookedHot();
			if(Working.type == cnWorkType_Steam)		// 蒸
				TurnOnLedSteam();
			else
				TurnOffLedSteam();
			if(Working.type == cnWorkType_Cooking)		// 蒸煮
				TurnOnLedCooking();
			else
				TurnOffLedCooking();
		}
		break;
	}
}

static void Working_HeatTemp_Adjust(void)
{
	uint8_t temp, tempMin, tempMax;

	if(Working.para.temp == 0)
	{
		TurnOffHeater();
		return;
	}	

	tempMin = Working.para.temp - cnTempOffset;
	tempMax = Working.para.temp + cnTempOffset - 1;
	temp = GetTempNTC();	// - 1;
	//temp = 93;
	
	if(IsHeaterOn())
	{
		if(temp >= tempMax)
		{
			TurnOffHeater();
			if(Working.status == cnWorkStatus_PreHeat)
			{
				TurnOffHeater();
				Working.status = cnWorkStatus_Ready;
			}
		}	
	}
	else
	{
		if(temp <= tempMin)
		{
			TurnOnHeater();
			if(Working.status == cnWorkStatus_Ready)
				Working.status = cnWorkStatus_PreHeat;
		}
		else
		{
			if(Working.status == cnWorkStatus_PreHeat)
			{
				TurnOffHeater();
				Working.status = cnWorkStatus_Ready;
			}
		}
	}
}

void Working_PumpHeat_Run_Task(void)
{
	if(!IsCurWorkModeWorking())
		return;

	// Led显示
	Working_ShowStatusDoing();

	switch(Working.status)
	{
	case cnWorkStatus_PreHeat:
		{
			if(Working.para.tmrms == 0)
				Working.status = cnWorkStatus_Ready;
			else
			{
				--Working.para.tmrms;
				Working_HeatTemp_Adjust();
			}	
		}	
		break;
		
	case cnWorkStatus_Ready:
		{
			Working_HeatTemp_Adjust();
			Working.status = cnWorkStatus_DoCooking1;
			GetWorkingTempTimePara(Working.type, Working.status-cnWorkStatus_Ready);
		}	
		break;

	case cnWorkStatus_DoCooking1:	
		{
			if(Working.para.tmrms == 0)
			{
				Working.status = cnWorkStatus_DoCooking2;
				GetWorkingTempTimePara(Working.type, Working.status-cnWorkStatus_Ready);
			}	
			else
			{
				--Working.para.tmrms;
				Working_HeatTemp_Adjust();
			}	
		}
		break;
	
	case cnWorkStatus_DoCooking2:
		{
			if(Working.para.tmrms == 0)
			{
				Working.status = cnWorkStatus_DoCooking3;
				GetWorkingTempTimePara(Working.type, Working.status-cnWorkStatus_Ready);
			}	
			else
			{
				--Working.para.tmrms;
				Working_HeatTemp_Adjust();
			}	
		}
		break;
		
	case cnWorkStatus_DoCooking3:
		{
			if(Working.para.tmrms == 0)
			{
				TurnOffHeater();

				Working.para.temp = 0;
				Working.para.tmrms = cnWorkingEndingT;
				Working.status = cnWorkStatus_Ending;
			}	
			else
			{
				--Working.para.tmrms;
				Working_HeatTemp_Adjust();
			}	
		}
		break;

	case cnWorkStatus_Ending:
		{
			if(Working.para.tmrms == 0)
			{
				bIsWorkingStop = TRUE;
				Working.status = cnWorkStatus_Stop;
			}
			else
			{
				if((Working.para.tmrms%(20*(1000UL/cnWorkPHTBase))) == 0)
					SetBuzzerRunTime(cnBzToneDone);
			
				--Working.para.tmrms;
				TurnOffHeater();
			}
		}	
		break;

	case cnWorkStatus_Stop:
	case cnWorkStatus_Select:
	default:
		{
			TurnOffHeater();
		}
		break;
	}
}



///////////////////////////////////////////////////////////////////////////////////////////////////
static RET_CODE Working_MsgFunc_Key_Power(MsgValue_t MsgValue)
{
	WorkingRunTmr = 0;
	
	if(Get_Key_IsRelease(MsgValue))
	{
		Set_Key_Processed();

		switch(Working.status)
		{
		case cnWorkStatus_Select:			// 选择功能
			{
				Working.status = cnWorkStatus_PreHeat;
				GetWorkingTempTimePara(Working.type, 0);
			}
			break;
			
		case cnWorkStatus_Stop:				// 停止加热 
		case cnWorkStatus_PreHeat:			// 先加热
		case cnWorkStatus_Ready:			// 温度已经达到
		case cnWorkStatus_DoCooking1:		// 正在煮蛋: 第一阶段
		case cnWorkStatus_DoCooking2:		// 正在煮蛋: 第二阶段
		case cnWorkStatus_DoCooking3:		// 正在煮蛋: 第三阶段
		case cnWorkStatus_Ending:			// 结束
		default:
			{
				TurnOffHeater();
				bIsWorkingStop = FALSE;
				Working.status = cnWorkStatus_Select;
			}
			break;
		}
	}
	else if(Get_Key_IsPressed(MsgValue, cnKeyPressedT_3s))
	{
		Set_Key_Processed();

		Working_De();
		Idle_Con();
	}
	
	return cnSuccess;
}


static RET_CODE Working_MsgFunc_Key_Menu(MsgValue_t MsgValue)
{
	WorkingRunTmr = 0;

	if(Get_Key_IsRelease(MsgValue))
	{
		Set_Key_Processed();

		if(Working.status == cnWorkStatus_Select)
		{
			++Working.type;
			if(Working.type >= cnWorkType_Max)
				Working.type = cnWorkType_CookedAll;
		}	
	}

	return cnSuccess;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// cnFuncNumWorking,				// Working模式
RET_CODE StationRun_Working(uint8_t Msg, MsgValue_t MsgValue)
{
	RET_CODE retCode = cnFailure;

	switch(Msg)
	{
	case cnMsgKeyPower:
		retCode = Working_MsgFunc_Key_Power(MsgValue);
		break;
	case cnMsgKeyMenu:
		retCode = Working_MsgFunc_Key_Menu(MsgValue);
		break;
		
	default:
		retCode = cnNoRespond;
		break;
	}

	return retCode;
}


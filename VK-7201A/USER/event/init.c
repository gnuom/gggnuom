
#define	__EXT_INIT_
#include "Globals.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
#define  cnInitTaskRunT		cnTBaseT_100ms
static uint8_t RAM_xDATA InitRunTimer = 0;

static void WDT_Config(void)
{
	// (1)开启WDT溢出时间
	WDT_ConfigOverflowTime(WDT_CLK_67108864);	// Fsys=24Mhz -> Twdt = 67108864/24 = 2796.2027ms
	// (2)禁止WDT溢出中断
	WDT_DisableOverflowInt();

	WDT_EnableWDTReset();			//使能WDT复位芯片
}



/************************************************************
 初始化模式构建：
*************************************************************/
void Init_Con(void)
{
	SYS_DisableSoftwareReset();			//清零使能位
	
	SysTime_Config();
	Debug_Init();

	Led_Init();
	Key_Init();
	NTC_Init();
	Heater_Init();
	Buzzer_Init();

	Common_Init();
	
	WDT_Config();

	SetBuzzerRunTime(cnBzToneKeyPress);
	InitRunTimer = 0;
	SetWorkMode(cnFuncNumInit);
}

/************************************************************
 初始化模式析构：
*************************************************************/
void Init_De(void)
{
	//TurnOnHalfAllLed();
}

/************************************************************
 初始化模式调度：100ms 调度
*************************************************************/
void Init_Run_Task(void)
{
	if(IsCurWorkModeInit())
	{
		TurnOnAllLed();

		Heat_Stop();

		if((++InitRunTimer) >= 5)	// (1000UL/cnTBaseT_200ms))
		{
			Init_De();
			Idle_Con();
		}
	}
}



///////////////////////////////////////////////////////////////////////////////////////////////////
RET_CODE StationRun_Init(uint8_t Msg, MsgValue_t MsgValue)
{
	RET_CODE retCode = cnFailure;
	MsgValue = MsgValue;

	switch(Msg)
	{
	default:
		retCode = cnSuccess;
		break;
	}

	return retCode;
}



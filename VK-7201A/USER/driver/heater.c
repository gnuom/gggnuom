
#define	__EXT_HEATER_
#include "Globals.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
bool_t bHeaterOn;

#define cnAlarmTempWHi			105		// 高温报警时加热体上的温度
#define cnAlarmTempWLow			55		// 高温报警回落时加热体上的温度

#define cnTempCheckT			(1*(1000UL/cnTBaseT_100ms))
bool_t bTempHi, bResetTempHiCheck;
uint8_t TempHiCheckTmr, TempHiCheckCnt;

void Heater_Init(void)
{
	SetPortHeaterAsOut();
	TurnOffHeater();

	ClrHeaterTempHi();
	bResetTempHiCheck = FALSE;
	TempHiCheckTmr = cnTempCheckT;
	TempHiCheckCnt = 0;
}

void Heater_Run_Task(void)
{
	/* 
		"ANY CASE heater temperature hits 125C: Red Color  on;
		After 60s: Red Color off
		OR if heater temperature goes below 75C: Red Color off"
	*/
	if(IsHeaterTempHi())
	{
		Heater_Off();
		if(GetTempNTC() < cnAlarmTempWLow)
			++TempHiCheckCnt;
	}
	else
	{
		if(IsNTCTempHi() || (GetTempNTC() > cnAlarmTempWHi))
			++TempHiCheckCnt;

		
		if(bHeaterOn)
			Heater_On();
		else
			Heater_Off();
	}

	if(TempHiCheckTmr == 0)
	{
		if(bResetTempHiCheck)
		{
			bResetTempHiCheck = FALSE;
			TempHiCheckCnt = 0;
		}
	
		if(IsHeaterTempHi())
		{
			if(TempHiCheckCnt > (cnTempCheckT*4/5))
				ClrHeaterTempHi();
			else
				SetHeaterTempHi();
		}
		else
		{
			if(TempHiCheckCnt > (cnTempCheckT*4/5))
				SetHeaterTempHi();
			else
				ClrHeaterTempHi();
		}	

	
		TempHiCheckTmr = cnTempCheckT;
		TempHiCheckCnt = 0;
	}

	--TempHiCheckTmr;
}




#define	__EXT_DEBUG_
#include "Globals.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef cnDebug_Print

///////////////////////////////////////////////////////////////////////////////////////////////////
static uint8_t RAM_iDATA RxStep, RxLevelCnt, RxBuf, RxBitNum, RxBufTmp;
static uint8_t RAM_iDATA TxStep, TxLevelCnt, TxBuf, TxBitNum;
static bool_t bGotoSending;
static void TMR4_Config(void)
{
	RxStep = cnRxStep_WaitStartH;
	RxLevelCnt = 0;
	RxBuf = 0;
	RxBufTmp = 0;
	RxBitNum = 0;

	bGotoSending = FALSE;
	TxStep = cnTxStep_WaitStart;
	TxLevelCnt = 0;
	TxBuf = 0;
	TxBitNum = 0;

	// (1)设置Timer的运行模式
	TMR_ConfigRunMode(TMR4, TMR_MODE_TIMING, TMR_TIM_AUTO_8BIT);	
	// (2)设置Timer 运行时钟
	TMR_ConfigTimerClk(TMR4, TMR_CLK_DIV_12);					// Fsys = 24Mhz，Ftimer = 2Mhz,Ttmr=0.5us
	// (3)设置Timer周期
	TMR_ConfigTimerPeriod(TMR4, 256-208, 256-208); 				// 200*0.5us = 100us,递增计数
		
	// (4)开启中断
	TMR_EnableOverflowInt(TMR4);

	// (5)设置Timer中断优先级
	IRQ_SET_PRIORITY(IRQ_TMR4, IRQ_PRIORITY_HIGH);

	// (6)开启Timer
	TMR_Start(TMR4);
}


// ____    __    __    __    __    ____   
//     |  |  |  |  |  |  |  |  |  |   
//     |0 |1 |2 |3 |4 |5 |6 |7 |8 |9   
//     |__|  |__|  |__|  |__|  |__|   
//               
static void Timer4_IRQHandler(void)      interrupt TMR4_VECTOR 
{
	//P_TX = ~P_TX;
	//return;

	// TX
	if(bGotoSending == FALSE)
	{
		P_TX = 1;
		TxStep = cnTxStep_WaitStart;
		TxLevelCnt = 0;
	}
	else
	{
		++TxLevelCnt;
		if(TxStep == cnTxStep_WaitStart)
		{
			P_TX = 1;
			if(TxLevelCnt >=2)
			{
				TxLevelCnt = 0;
				TxStep = cnTxStep_SendStartBit;
			}
		}
		else if(TxStep == cnTxStep_SendStartBit)
		{
			P_TX = 0;
			if(TxLevelCnt >= 4)
			{
				TxLevelCnt = 0;
				TxBitNum = 0;
				TxStep = cnTxStep_SendBit;
			}
		}
		else if(TxStep == cnTxStep_SendBit)
		{
			P_TX = TxBuf & 0x01;
			if(TxLevelCnt >= 4)
			{
				TxLevelCnt = 0;

				++TxBitNum;
				if(TxBitNum >= 8)
					TxStep = cnTxStep_SendEndBit;
				else
					TxBuf >>= 1;
			}
		}
		else
		{
			P_TX = 1;
			if(TxLevelCnt >= 4)
			{
				TxStep = cnTxStep_WaitStart;
				TxLevelCnt = 0;
				bGotoSending = FALSE;
			}	
		}
	}
	
/*
	// RX
	if(RxStep == cnRxStep_WaitStartH)
	{
		if(P_RX)
		{
			RxLevelCnt = 0;
			RxStep = cnRxStep_WaitStartBit;
		}
	}
	else if(RxStep == cnRxStep_WaitStartBit)
	{
		if(P_RX)
			RxLevelCnt = 0;
		else
		{
			if((++RxLevelCnt) >= 2)
			{
				RxLevelCnt = 0;
				RxBuf = 0;
				RxBitNum = 0;
				RxStep = cnRxStep_GetBit;
			}
		}
	}
	else if(RxStep == cnRxStep_GetBit)
	{
		if((++RxLevelCnt) >= 4)
		{
			RxLevelCnt = 0;
			if(P_RX)
				RxBuf |= 0x80;
	
			++RxBitNum;
			if(RxBitNum >= 8)
				RxStep = cnRxStep_WaitEndBit;
			else
				RxBuf >>= 1;
		}
	}
	else //if(RxStep == cnRxStep_WaitEndBit)
	{
		RxBitNum = 0;
	
		if((++RxLevelCnt) >= 4)
		{
			RxLevelCnt = 0;
	
			if(P_RX)
			{
				RxBufTmp = RxBuf;
			}
	
			RxStep = cnRxStep_WaitStartH;
		}
	}
*/	
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void GpioUart_Init(void)
{
	SetTXPortDirOut();
	SetRXPortDirIn();

	TMR4_Config();
}

void GpioUart_Send(uint8_t dat)
{
	while(bGotoSending)
	{
		ClearWDT();
	}

	TxBuf = dat;
	bGotoSending = TRUE;
}

uint8_t GpioUart_Recv(void)
{
	return RxBufTmp;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
uint16_t RAM_DATA debugTmr, debugLowCnt;

void Debug_Init(void)
{
	GpioUart_Init();

	debugTmr = 0; 
	debugLowCnt = 0;
}

void SetDebugTimerCnt(uint16_t cnt)
{
	cnt = cnt;
/*
	if(debugTmr > 0)
		return;

	debugLowCnt = cnt;
	debugTmr = 100;			// 500ms
*/	
}

void Debug_Run_Task(void)
{

	if(debugTmr == 0)
	{
		//if(IsCurWorkModeWorking())
		//	debugTmr = 0.2 * (1000UL / cnTBaseT_100ms);
		//else if(IsCurWorkModeEmergency())		
		//	debugTmr = 0.5 * (1000UL / cnTBaseT_100ms);
		//else
			debugTmr = 1 * (1000UL / cnTBaseT_100ms);
		

		#if 1
		//debug_print(0x00);
		debug_print(GetCurWorkMode());
		#endif

		//debug_print(0x03);
		debug_print(Working.status);

		//debug_print(0x04);
		debug_print(IsHeaterOn());
		//debug_print(Working.tempDo);
		debug_print(GetTempNTC());

		//debug_print(0x06);
		//debug_print((uint8_t)KeyFlag);
	}
	else	
		--debugTmr;
}

#else
void Debug_Init(void)
{
}

void SetDebugTimerCnt(uint16_t cnt)
{
	cnt = cnt;
}

void GpioUart_Send(uint8_t dat)
{
	dat = dat;
}

void Debug_Run_Task(void)
{
}

#endif



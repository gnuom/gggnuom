
#define __EXT_TIME_
#include "Globals.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
bool_t bTime1ms;
bool_t bTime5ms;
bool_t bTime10ms;
bool_t bTime100ms;
bool_t bTime200ms;
bool_t bTime500ms;
bool_t bTime1s;


uint32_t RAM_DATA sysTotalTick;

static volatile uint8_t u8Time5ms;
static volatile uint8_t u8Time10ms;
static volatile uint8_t u8Time100ms;
static volatile uint8_t u8Time200ms;
static volatile uint8_t u8Time500ms;
static volatile uint8_t u8Time1s;

#define	cnSysTickT			(65536UL - 2000)	//Fsys = 24Mhz，Ftimer = 2Mhz,Ttmr=0.5us

///////////////////////////////////////////////////////////////////////////////////////////////////
void SysTime_Config(void)
{
	bTime1ms = 0;
	bTime5ms = 0;
	bTime10ms = 0;
	bTime100ms = 0;
	bTime200ms = 0;
	bTime500ms = 0;
	bTime1s = 0;

	u8Time5ms = 0;
	u8Time10ms = 0;
	u8Time100ms = 0;
	u8Time200ms = 0;
	u8Time500ms = 0;
	u8Time1s = 0;

	sysTotalTick = 0;
	
	//设置Timer的运行模式 1
	TMR_ConfigRunMode(TMR0, TMR_MODE_TIMING, TMR_TIM_16BIT);	
	//设置Timer 运行时钟: Fsys = 24Mhz，Ftimer = 2Mhz,Ttmr=0.5us
	TMR_ConfigTimerClk(TMR0, TMR_CLK_DIV_12);						
	//设置Timer周期:2000*0.5us = 1000us,递增计数
	TMR_ConfigTimerPeriod(TMR0, (uint8_t)(cnSysTickT >> 8), (uint8_t)(cnSysTickT & 0x00ff));
	//开启中断
	TMR_EnableOverflowInt(TMR0);
	//设置Timer中断优先级
	IRQ_SET_PRIORITY(IRQ_TMR0, IRQ_PRIORITY_HIGH);
	//开启Timer
	TMR_Start(TMR0);
}


/******************************************************************************
 ** \brief	 Timer 0 interrupt service function
 **
 ** \param [in]  none   
 **
 ** \return none
******************************************************************************/
void Timer0_IRQHandler(void) interrupt TMR0_VECTOR 
{
	TH0 = (uint8_t)(cnSysTickT >> 8);
	TL0 = (uint8_t)(cnSysTickT & 0x00ff);

	++sysTotalTick;		// 自上电后就开始累积，单位为1ms

	//pBuzzer_Power = ~pBuzzer_Power;
		
	bTime1ms = TRUE;
	u8Time5ms++;
	if(u8Time5ms >= 5)
	{
		u8Time5ms = 0;
		bTime5ms = TRUE;
	}

	u8Time10ms++;
	if(u8Time10ms >= 10)
	{
		u8Time10ms = 0;
		bTime10ms = TRUE;

		u8Time100ms++;
		if(u8Time100ms >= 10)
		{
			u8Time100ms = 0;
			bTime100ms = TRUE;

			u8Time200ms++;
			if(u8Time200ms >= 2)
			{
				u8Time200ms = 0;
				bTime200ms = TRUE;
			}

			u8Time500ms++;
			if(u8Time500ms >= 5)
			{
				u8Time500ms = 0;
				bTime500ms = TRUE;
			}

			u8Time1s++;
			if(u8Time1s >= 10)
			{
				u8Time1s = 0;
				bTime1s = TRUE;
			}
		}
	}
}


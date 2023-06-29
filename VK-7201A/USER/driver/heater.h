
#ifndef	__H_HEATER_
#define	__H_HEATER_

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef	__EXT_HEATER_
#define	HEATER_EXT
#else
#define HEATER_EXT				extern
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
#define	cnHeaterOn				1
#define	cnHeaterOff				0

#define	portHeater				P21   //P20
// 数字IO口	// 配置为输出口	// 使能弱上拉	// 禁止弱下拉
#define	SetPortHeaterAsOut()	do{ GPIO_SET_MUX_MODE(P21CFG, GPIO_MUX_GPIO); \
									GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_1); \
									GPIO_ENABLE_UP(P2UP, GPIO_PIN_1); \
								  }while(0)
								  
#define	Heater_On()				do{ portHeater = cnHeaterOn; }while(0)
#define	Heater_Off()			do{ portHeater = cnHeaterOff; }while(0)


///////////////////////////////////////////////////////////////////////////////////////////////////
HEATER_EXT bool_t bHeaterOn;

#define IsHeaterOn()			(bHeaterOn == TRUE)
#ifdef cnDebug_OffHeater
#define	TurnOnHeater()			do{ Heater_Off(); bHeaterOn = TRUE; }while(0)
#else
#define	TurnOnHeater()			do{ Heater_On(); bHeaterOn = TRUE; }while(0)
#endif
#define	TurnOffHeater()			do{ Heater_Off(); bHeaterOn = FALSE; }while(0)
#define Heat_Stop()				do{ Heater_Off(); bHeaterOn = FALSE; }while(0)


#define cnTempHiCheckT			(1*(1000UL/cnTBaseT_100ms))
#define cnTempHiDelayCheckT		(8*(1000UL/cnTBaseT_100ms))
HEATER_EXT bool_t bTempHi, bResetTempHiCheck;
#define ClrHeaterTempHi()		do{ bTempHi = FALSE; }while(0)
#define SetHeaterTempHi()		do{ bTempHi = TRUE; }while(0)
#define IsHeaterTempHi()		(bTempHi == TRUE)

HEATER_EXT uint8_t TempHiCheckTmr, TempHiCheckCnt;
#define ResetTempHiCheck()		do{ ClrHeaterTempHi(); \
									bResetTempHiCheck = TRUE; \
									TempHiCheckCnt = 0; \
									TempHiCheckTmr = cnTempHiDelayCheckT; }while(0)


///////////////////////////////////////////////////////////////////////////////////////////////////
HEATER_EXT void Heater_Init(void);
HEATER_EXT void Heater_Run_Task(void);

#endif



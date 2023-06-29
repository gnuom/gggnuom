
#ifndef	__H_BUZZERDRV_
#define	__H_BUZZERDRV_

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef	__EXT_BUZZERDRV_
#define	BUZZERDRV_EXT
#else
#define BUZZERDRV_EXT		extern
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
#if 0
#define PORT_BUZ_POWER		GPIO2
#define PIN_BUZ_POWER		GPIO_PIN_1
#define CFG_BUZ_POWER		P21CFG
#define PortTRIS_BUZ_POWER	P2TRIS

#define	pBuzzer_Power		P21

#else
#define PORT_BUZ_POWER		GPIO1
#define PIN_BUZ_POWER		GPIO_PIN_0
#define CFG_BUZ_POWER		P10CFG
#define PortTRIS_BUZ_POWER	P1TRIS

#define	pBuzzer_Power		P10
#endif
//#define	pbuzzer_Osc			P06

#define	BuzzerCtrlOn()		do{ pBuzzer_Power = 0; }while(0)
#define	BuzzerCtrlOff()		do{ pBuzzer_Power = 1; }while(0)
#define	BuzzerSwap()		//do{ pbuzzer_Osc = ~pbuzzer_Osc; }while(0)
#define	BuzzerSet(level)	//do{ pbuzzer_Osc = level; }while(0)

#define	cnBuzzerL			0
#define	cnBuzzerH			1

enum {
	cnBzToneOff = 0,
	cnBzTonePowerOn,
	cnBzTonePowerOff,
	cnBzToneKeyPress,
	cnBzToneCancel,
	cnBzToneDone,

	cnBzTone_max,
};

typedef struct {
	uint8_t bzTone;
	uint16_t bzCtrlOnT;
	uint16_t bzOnT;
}BzTone_FMT;

BUZZERDRV_EXT bool_t bBuzzerOn;
#define	IsBuzzerOn()		(bBuzzerOn == TRUE)
#define	BuzzerOn()			do{ bBuzzerOn = TRUE; \
								BuzzerCtrlOn(); \
								BUZ_EnableBuzzer(); } while(0)
#define	BuzzerOff()			do{ bBuzzerOn = FALSE; \
								BuzzerCtrlOff(); \
								BUZ_DisableBuzzer(); \
								BuzzerSet(cnBuzzerL); } while(0)

/*
Tf(Buz)：频率给定持续时间（ms） 
Tv(Buz_C)：电压给定持续时间（ms） 
	  F：输出频率（KHz））
*/			  
#define	cnBzTIntv		1

#define SetBuzzerRunDone()	do{ SetBuzzerRunTime(cnBzToneDone); }while(0)

///////////////////////////////////////////////////////////////////////////////////////////////////
BUZZERDRV_EXT void Buzzer_Init(void);
BUZZERDRV_EXT void SetBuzzerRunTime(uint8_t bzTone);
BUZZERDRV_EXT void Buzzer_Run_Task(void);

#endif



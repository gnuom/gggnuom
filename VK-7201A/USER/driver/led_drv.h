
#ifndef	__H_LED_
#define	__H_LED_

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef	__EXT_LED_
#define	LED_EXT
#else
#define LED_EXT		extern
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
#define	cnLedOn						0
#define	cnLedOff					1



#define cnLedCom_EPWM				PWM2
#define cnLedCom_chnEPWM_MSK		PWM_CH_2_MSK
#define cnLedCom_PortCFG			P22CFG
#define cnLedCom_PortMUX			GPIO_P22_MUX_PG2   //P00

#define cnLedComPWMDutyStep			5
#define cnLedComPWMDutyMin			0
#define cnLedComPWMDutyMax			(1000UL)
#define cnLedComPWMPeriodNum		(4800UL)	//(0x12C0)
#define SetLedComPWM_Duty(duty)		do{	PWM_ConfigChannelDuty(cnLedCom_EPWM, \
										(cnLedComPWMPeriodNum*(cnLedComPWMDutyMax-duty)/1000UL)); }while(0)
#define LedComPWM_Stop()			do{ PWM_ConfigChannelDuty(cnLedCom_EPWM, 0); \
										PWM_Stop(cnLedCom_chnEPWM_MSK); \
										}while(0)

#define	LedCom_On()					do{ LedBreathDuty = cnLedComPWMDutyMax; \
										SetLedComPWM_Duty(cnLedComPWMDutyMax); }while(0)
#define	LedCom_Off()				do{ LedBreathDuty = cnLedComPWMDutyMin; \
										SetLedComPWM_Duty(cnLedComPWMDutyMin); }while(0)




#define	portLedPower				  P52   //P7
#define portLedCookedAll			P05
#define portLedCookedMed			P04
#define portLedCookedHot			P03
#define portLedSteam				  P02
#define portLedCooking				P07   //P01
#define	SetPortAllLedAsOut()		do{ GPIO_SET_MUX_MODE(P52CFG, GPIO_MUX_GPIO); \    
										GPIO_ENABLE_OUTPUT(P5TRIS, GPIO_PIN_2); \
										GPIO_SET_MUX_MODE(P07CFG, GPIO_MUX_GPIO); \
										GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_7); \
										GPIO_SET_MUX_MODE(P02CFG, GPIO_MUX_GPIO); \
										GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_2); \
										GPIO_SET_MUX_MODE(P03CFG, GPIO_MUX_GPIO); \
										GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_3); \
										GPIO_SET_MUX_MODE(P04CFG, GPIO_MUX_GPIO); \
										GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_4); \
										GPIO_SET_MUX_MODE(P05CFG, GPIO_MUX_GPIO); \
										GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_5); \
								  		}while(0)
								  		
#define LedPower_On()				do{ portLedPower = cnLedOn; }while(0)
#define LedPower_Off()				do{ portLedPower = cnLedOff; }while(0)
#define LedCookedAll_On()			do{ portLedCookedAll = cnLedOn; }while(0)
#define LedCookedAll_Off()			do{ portLedCookedAll = cnLedOff; }while(0)
#define LedCookedMed_On()			do{ portLedCookedMed = cnLedOn; }while(0)
#define LedCookedMed_Off()			do{ portLedCookedMed = cnLedOff; }while(0)
#define LedCookedHot_On()			do{ portLedCookedHot = cnLedOn; }while(0)
#define LedCookedHot_Off()			do{ portLedCookedHot = cnLedOff; }while(0)
#define LedSteam_On()				do{ portLedSteam = cnLedOn; }while(0)
#define LedSteam_Off()				do{ portLedSteam = cnLedOff; }while(0)
#define LedCooking_On()				do{ portLedCooking = cnLedOn; }while(0)
#define LedCooking_Off()			do{ portLedCooking = cnLedOff; }while(0)


///////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum {
	cnLedPower = 0,
	cnLedCookedAll,					// »´ Ï
	cnLedCookedMed,					// ∞Î Ï 
	cnLedCookedHot,					// Œ¬»™µ∞
	cnLedSteam,						// ’Ù
	cnLedCooking,					// ’Ù÷Û

	cnLed_Max
}Led_T;
#define cnLed_Start				cnLedPower

typedef enum {
	cnLedStatus_Off = 0,			// √
	cnLedStatus_On,					// ¡¡
	cnLedStatus_Flash_500ms,		// ¬˝…¡À∏
	cnLedStatus_Flash_300ms,		// øÏ…¡À∏
	cnLedStatus_Flash_100ms,		// øÏ…¡À∏
	cnLedStatus_Flash_2times,		// …¡À∏2¥Œ

	cnLedStatus_Breath,				// ∫ÙŒ¸µ∆–ßπ˚

	cnLedStatus_Max
}LedStatus_T;

typedef struct {
	LedStatus_T status;
	LedStatus_T statusTmp;
	uint8_t runTmr;
	uint8_t runTmrTmp;
	uint8_t OnOff;
	uint8_t flashCnt;
}LedPara_t;

LED_EXT uint16_t LedBreathDuty;
LED_EXT LedPara_t RAM_xDATA ledPara[cnLed_Max];
#define	TurnOnLedPower()					do{ SetLedStatus(cnLedPower, cnLedStatus_On); }while(0)
#define	TurnOffLedPower()					do{ SetLedStatus(cnLedPower, cnLedStatus_Off); }while(0)
#define	TurnOnLedPowerFlash500ms()			do{ SetLedStatus(cnLedPower, cnLedStatus_Flash_500ms); }while(0)
#define	TurnOnLedPowerFlash300ms()			do{ SetLedStatus(cnLedPower, cnLedStatus_Flash_300ms); }while(0)
#define	TurnOnLedPowerFlash100ms()			do{ SetLedStatus(cnLedPower, cnLedStatus_Flash_100ms); }while(0)
#define	TurnOnLedPowerFlash2times()			do{ SetLedStatus(cnLedPower, cnLedStatus_Flash_2times); }while(0)
#define	TurnOffLedPowerFlash2times()		do{ ledPara[cnLedPower].flashCnt = 0; TurnOffLedPower(); }while(0)
#define TurnOnLedPowerBreath()				do{ SetLedStatus(cnLedPower, cnLedStatus_Breath); }while(0)

#define	TurnOnLedCookedAll()				do{ SetLedStatus(cnLedCookedAll, cnLedStatus_On); }while(0)
#define	TurnOffLedCookedAll()				do{ SetLedStatus(cnLedCookedAll, cnLedStatus_Off); }while(0)
#define	TurnOnLedCookedAllFlash500ms()		do{ SetLedStatus(cnLedCookedAll, cnLedStatus_Flash_500ms); }while(0)
#define	TurnOnLedCookedAllFlash300ms()		do{ SetLedStatus(cnLedCookedAll, cnLedStatus_Flash_300ms); }while(0)
#define	TurnOnLedCookedAllFlash100ms()		do{ SetLedStatus(cnLedCookedAll, cnLedStatus_Flash_100ms); }while(0)
#define	TurnOnLedCookedAllFlash2times()		do{ SetLedStatus(cnLedCookedAll, cnLedStatus_Flash_2times); }while(0)
#define	TurnOffLedCookedAllFlash2times()	do{ ledPara[cnLedCookedAll].flashCnt = 0; TurnOffLedPower(); }while(0)
#define TurnOnLedCookedAllBreath()			do{ SetLedStatus(cnLedCookedAll, cnLedStatus_Breath); }while(0)

#define	TurnOnLedCookedMed()				do{ SetLedStatus(cnLedCookedMed, cnLedStatus_On); }while(0)
#define	TurnOffLedCookedMed()				do{ SetLedStatus(cnLedCookedMed, cnLedStatus_Off); }while(0)
#define	TurnOnLedCookedMedFlash500ms()		do{ SetLedStatus(cnLedCookedMed, cnLedStatus_Flash_500ms); }while(0)
#define	TurnOnLedCookedMedFlash300ms()		do{ SetLedStatus(cnLedCookedMed, cnLedStatus_Flash_300ms); }while(0)
#define	TurnOnLedCookedMedFlash100ms()		do{ SetLedStatus(cnLedCookedMed, cnLedStatus_Flash_100ms); }while(0)
#define	TurnOnLedCookedMedFlash2times()		do{ SetLedStatus(cnLedCookedMed, cnLedStatus_Flash_2times); }while(0)
#define	TurnOffLedCookedMedFlash2times()	do{ ledPara[cnLedCookedMed].flashCnt = 0; TurnOffLedPower(); }while(0)
#define TurnOnLedCookedMedBreath()			do{ SetLedStatus(cnLedCookedMed, cnLedStatus_Breath); }while(0)
											
#define	TurnOnLedCookedHot()				do{ SetLedStatus(cnLedCookedHot, cnLedStatus_On); }while(0)
#define	TurnOffLedCookedHot()				do{ SetLedStatus(cnLedCookedHot, cnLedStatus_Off); }while(0)
#define	TurnOnLedCookedHotFlash500ms()		do{ SetLedStatus(cnLedCookedHot, cnLedStatus_Flash_500ms); }while(0)
#define	TurnOnLedCookedHotFlash300ms()		do{ SetLedStatus(cnLedCookedHot, cnLedStatus_Flash_300ms); }while(0)
#define	TurnOnLedCookedHotFlash100ms()		do{ SetLedStatus(cnLedCookedHot, cnLedStatus_Flash_100ms); }while(0)
#define	TurnOnLedCookedHotFlash2times()		do{ SetLedStatus(cnLedCookedHot, cnLedStatus_Flash_2times); }while(0)
#define	TurnOffLedCookedHotFlash2times()	do{ ledPara[cnLedCookedHot].flashCnt = 0; TurnOffLedPower(); }while(0)
#define TurnOnLedCookedHotBreath()			do{ SetLedStatus(cnLedCookedHot, cnLedStatus_Breath); }while(0)
																						
#define	TurnOnLedSteam()					do{ SetLedStatus(cnLedSteam, cnLedStatus_On); }while(0)
#define	TurnOffLedSteam()					do{ SetLedStatus(cnLedSteam, cnLedStatus_Off); }while(0)
#define	TurnOnLedSteamFlash500ms()			do{ SetLedStatus(cnLedSteam, cnLedStatus_Flash_500ms); }while(0)
#define	TurnOnLedSteamFlash300ms()			do{ SetLedStatus(cnLedSteam, cnLedStatus_Flash_300ms); }while(0)
#define	TurnOnLedSteamFlash100ms()			do{ SetLedStatus(cnLedSteam, cnLedStatus_Flash_100ms); }while(0)
#define	TurnOnLedSteamFlash2times()			do{ SetLedStatus(cnLedSteam, cnLedStatus_Flash_2times); }while(0)
#define	TurnOffLedSteamFlash2times()		do{ ledPara[cnLedSteam].flashCnt = 0; TurnOffLedPower(); }while(0)
#define TurnOnLedSteamBreath()				do{ SetLedStatus(cnLedSteam, cnLedStatus_Breath); }while(0)

#define	TurnOnLedCooking()					do{ SetLedStatus(cnLedCooking, cnLedStatus_On); }while(0)
#define	TurnOffLedCooking()					do{ SetLedStatus(cnLedCooking, cnLedStatus_Off); }while(0)
#define	TurnOnLedCookingFlash500ms()		do{ SetLedStatus(cnLedCooking, cnLedStatus_Flash_500ms); }while(0)
#define	TurnOnLedCookingFlash300ms()		do{ SetLedStatus(cnLedCooking, cnLedStatus_Flash_300ms); }while(0)
#define	TurnOnLedCookingFlash100ms()		do{ SetLedStatus(cnLedCooking, cnLedStatus_Flash_100ms); }while(0)
#define	TurnOnLedCookingFlash2times()		do{ SetLedStatus(cnLedCooking, cnLedStatus_Flash_2times); }while(0)
#define	TurnOffLedCookingFlash2times()		do{ ledPara[cnLedCooking].flashCnt = 0; TurnOffLedPower(); }while(0)
#define TurnOnLedCookingBreath()			do{ SetLedStatus(cnLedCooking, cnLedStatus_Breath); }while(0)

#define TurnAllLedSame(sta)				do{ uint8_t i; \
											for(i=cnLed_Start; i<cnLed_Max; i++) \
												SetLedStatus(i, sta); \
											}while(0)
#define TurnOnAllLed()					do{ TurnAllLedSame(cnLedStatus_On); }while(0)
#define TurnOffAllLed()					do{ TurnAllLedSame(cnLedStatus_Off); }while(0)
#define TurnOffAllLedForce()			do{ sub_memset((uint8_t *)ledPara, 0, cnLed_Max*sizeof(LedPara_t)); }while(0)

// ÷∏ æµ∆
#define cnLedRunTaskT			cnTBaseT_10ms			// √ø10ms≈‹“ª¥Œ
#define	cnLedRunT_2s			(2000/cnLedRunTaskT)
#define	cnLedRunT_1s			(1000/cnLedRunTaskT)
#define	cnLedRunT_0s5			(500/cnLedRunTaskT)
#define	cnLedRunT_0s3			(300/cnLedRunTaskT)
#define	cnLedRunT_0s25			(250/cnLedRunTaskT)
#define	cnLedRunT_0s2			(200/cnLedRunTaskT)
#define	cnLedRunT_0s1			(100/cnLedRunTaskT)


///////////////////////////////////////////////////////////////////////////////////////////////////
LED_EXT void Led_Init(void);
LED_EXT void Update_Led_Show(void);
LED_EXT void SetLedStatus(Led_T led, LedStatus_T sta);
LED_EXT void LedShow_Run_Task(void);



#endif



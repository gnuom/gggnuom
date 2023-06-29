
#define	__EXT_BUZZERDRV_
#include "Globals.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
bool_t bBuzzerOn;
static uint16_t RAM_xDATA bzOnTime, bzCtrlOnTime;
static uint8_t RAM_xDATA bzToneType;

///////////////////////////////////////////////////////////////////////////////////////////////////
#define cnBuzzerToneFreq_2K3			(163)
#define cnBuzzerToneFreq_2K6			(144)
#define cnBuzzerToneFreq_2K9			(129)
#define cnBuzzerToneFreq_3K3			(113)		// Fsys=48Mhz£¬Fbuz = Fsys/(2*64*113) =3.3khz
#define cnBuzzerToneFreq_3K6			(104)
#define cnBuzzerToneFreq_3K9			(96)
#define cnBuzzerToneFreq_4K				(93)
#define cnBuzzerToneFreq_Default		cnBuzzerToneFreq_2K6
#define BUZ_ConfigBuzzerFreq(x)			do{ BUZ_ConfigBuzzer(BUZ_CKS_64, x); }while(0)
void BUZZER_Config(void)
{
	// (1)ÅäÖÃ·äÃùÆ÷Ê±ÖÓ
	BUZ_ConfigBuzzerFreq(cnBuzzerToneFreq_Default);	
	// (2)ÅäÖÃ·äÃùÆ÷Êä³öIO
	GPIO_SET_MUX_MODE(P06CFG, GPIO_P06_MUX_BUZZ);
	// (3)Ê¹ÄÜ·äÃùÆ÷Ê±ÖÓ
	BUZ_DisableBuzzer();	
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void Buzzer_Init(void)
{
	GPIO_SET_MUX_MODE(CFG_BUZ_POWER, GPIO_MUX_GPIO);  
	GPIO_ENABLE_OUTPUT(PortTRIS_BUZ_POWER, PIN_BUZ_POWER); 

	BUZZER_Config();
	BuzzerOff();

	bzToneType = cnBzToneOff;
	bzOnTime = 0;
	bzCtrlOnTime = 0;
}

static ROM_DATA BzTone_FMT BzToneTab[] = {
	//						Tv(bzCtrlOnT)		Tf(bzOnT)
	{ cnBzTonePowerOn,		(500UL/cnBzTIntv),	(2000UL/cnBzTIntv) },
	{ cnBzTonePowerOff,		(20UL/cnBzTIntv),	(1000UL/cnBzTIntv) },
	{ cnBzToneKeyPress,		(200UL/cnBzTIntv),	(1000UL/cnBzTIntv) },
	{ cnBzToneCancel,		(500UL/cnBzTIntv),	(2000UL/cnBzTIntv) },
	//{ cnBzToneDone,			(2000UL/cnBzTIntv),	(3000UL/cnBzTIntv) },
	{ cnBzToneDone,			(2UL/cnBzTIntv),	(900UL/cnBzTIntv) },
};

/************************************************************
·äÃùÆ÷ÖÃÉù£ºÉèÖÃ¸÷ÊÂ¼þÀàÐÍ·¢ÉùÉùµ÷(PW_ON PW_OFF KEYPRESS)
*************************************************************/
static uint8_t bzDoneCnt;
void SetBuzzerRunTime(uint8_t bzTone)
{
	uint8_t i;
	
	if((bzTone > cnBzToneOff) && (bzTone < cnBzTone_max))
	{
		for(i = 0; i < (sizeof(BzToneTab) / sizeof(BzTone_FMT)); i++)
		{
			if(bzTone == BzToneTab[i].bzTone)
			{
				bzDoneCnt = 0;
				bzToneType = bzTone;
				bzOnTime = BzToneTab[i].bzOnT;				//10;
				bzCtrlOnTime = BzToneTab[i].bzCtrlOnT;		//10;
				BUZ_ConfigBuzzerFreq(cnBuzzerToneFreq_Default);
				BuzzerOn();
				return;
			}
		}
	}

	bzToneType = cnBzToneOff;
	BuzzerOff();
}

/************************************************************
·äÃùÆ÷ÈÎÎñµ÷¶È£º1ms task
*************************************************************/
void Buzzer_Run_Task(void)
{
	if((bBuzzerOn == FALSE) || ((bzOnTime == 0) && (bzCtrlOnTime == 0)))
	{
		if((bzToneType == cnBzToneDone) && (bzDoneCnt < 2))
		{
			++bzDoneCnt;

			bzToneType = cnBzToneDone;
			bzOnTime = (900UL/cnBzTIntv);
			bzCtrlOnTime = (10UL/cnBzTIntv);
			BUZ_ConfigBuzzerFreq(cnBuzzerToneFreq_Default);
			BuzzerOn();
		}
		else
		{
			bzDoneCnt = 0;
			bzToneType = cnBzToneOff;
			bzOnTime = 0;
			bzCtrlOnTime = 0;
			BuzzerOff();
		}	
		return;
	}

	if(bzCtrlOnTime > 0)
	{
		if((--bzCtrlOnTime) == 0)
		{
			BuzzerCtrlOff();
		}
	}

	if(bzOnTime > 0)
	{
		--bzOnTime;
		if(bzToneType == cnBzToneCancel)
		{
			if(bzOnTime > (1800/cnBzTIntv))
				BUZ_ConfigBuzzerFreq(cnBuzzerToneFreq_2K9);
			else if(bzOnTime > (1600/cnBzTIntv))
				BUZ_ConfigBuzzerFreq(cnBuzzerToneFreq_2K6);
			else
				BUZ_ConfigBuzzerFreq(cnBuzzerToneFreq_2K3);
		}		
		else if(bzToneType == cnBzTonePowerOn)
		{
			if(bzOnTime > (1800/cnBzTIntv))
				BUZ_ConfigBuzzerFreq(cnBuzzerToneFreq_2K3);
			else if(bzOnTime > (1600/cnBzTIntv))
				BUZ_ConfigBuzzerFreq(cnBuzzerToneFreq_2K6);
			else
				BUZ_ConfigBuzzerFreq(cnBuzzerToneFreq_2K9);
		}	
		else if(bzToneType == cnBzToneDone)
		{
			if(bzOnTime > (2500/cnBzTIntv))
				BUZ_EnableBuzzer();
			else if(bzOnTime > (2000/cnBzTIntv))	
				BUZ_DisableBuzzer();
			else if(bzOnTime > (1500/cnBzTIntv))
				BUZ_EnableBuzzer();
			else if(bzOnTime > (1000/cnBzTIntv))	
				BUZ_DisableBuzzer();
			else if(bzOnTime > (500/cnBzTIntv))
				BUZ_EnableBuzzer();
			else
				BUZ_DisableBuzzer();
		}
		else if(bzToneType == cnBzToneKeyPress)
		{
			//if(bzOnTime == (400/cnBzTIntv))
			//	BUZ_ConfigBuzzerFreq(cnBuzzerToneFreq_3K3);
		}
	}
	else
	{
		BuzzerSet(cnBuzzerL);
	}
}



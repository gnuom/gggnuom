
#define	__EXT_SCANKEY_
#include "Globals.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
void Key_Init(void)
{
	// 默认复用触摸口，可以不设置复用
	GPIO_SET_MUX_MODE(P00CFG, GPIO_MUX_TKKEY); //复用成触摸口TK18 -> TK00  
	GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_2); 
	
	GPIO_SET_MUX_MODE(P01CFG, GPIO_MUX_TKKEY); //复用成触摸口TK19 -> TK01
	GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_3); 
}

//按键是否放开，1s内的短按键，放开才动作。1s后放开，无动作
bool_t Get_Key_IsRelease(uint16_t MsgValue)
{
	return (((MsgValue & cnKeyPressed) == 0) 
			&& (MsgValue < (cnKeyPressedT_1s & cnKeyUnpressed)) 
			&& IsKeyRelease());
}

//判断长按键是否按下time时长? 立即执行动作
bool_t Get_Key_IsPressed(uint16_t MsgValue, uint16_t Time)
{
	return ((MsgValue >= Time) && IsKeyRelease());
}

static bool_t  bIsKeyPressed = FALSE;
static uint8_t KeyPressInterval = 0;
static uint8_t u8KeyNew, u8KeyTmp = 0;
static uint8_t rdKeyValue;
static uint32_t u32KeyValueFlag;
static uint16_t u16KeyPressedTmr = 0, u16KeyReleaseTmr = 0;

/************************************************************
按键扫描调度：10ms task
*************************************************************/
static uint8_t ScanKeyRunCnt;
void ScanKey_Run_Task(void)
{
	++ScanKeyRunCnt;
	if(ScanKeyRunCnt < cnKeyTaskT)
		return;
	ScanKeyRunCnt = 0;	

	//按键处理程序开始
	u8KeyNew = cnMsgNull;
	rdKeyValue = 0;
	
	if(KeyPressInterval > 0)
		--KeyPressInterval;

	//按键扫描
	__CMS_CheckTouchKey();
	rdKeyValue = (uint8_t)KeyFlag;

	bIsKeyPressed = TRUE;
	switch(rdKeyValue)
	{
	case cnKey1:
		u8KeyNew = cnMsgKeyPower;
		break;
	case cnKey2:
		u8KeyNew = cnMsgKeyMenu;
		break;
	//case (cnKey3+cnKey1):
	//	u8KeyNew = cnMsgKeyCmbDrying;
	//	break;
	//case (cnKey3+cnKey5):
	//	u8KeyNew = cnMsgKeyCmbICT;
	//	break;
	
	default:
		u8KeyNew = cnMsgKey_Max;
		break;
	}


	if(u16KeyReleaseTmr > 0)
	{
		//键释放防抖200
		u16KeyReleaseTmr--;
		if((u16KeyReleaseTmr == 0) && (rdKeyValue == 0))
		{
			// 所有键松开
			u16KeyPressedTmr &= (~cnKeyPressed);

			if((u8KeyTmp > cnMsgKey) && (u8KeyTmp < cnMsgKey_Max))
			{
				StationRun(u8KeyTmp, u16KeyPressedTmr); /*按键释放优先调用处理函数*/
			}
			
			SetkeyRelease();
			u16KeyPressedTmr = 0;

			bIsKeyPressed = FALSE;
			u8KeyNew = cnMsgKey;
			u8KeyTmp = cnMsgKey;
		}
	}

	if((u8KeyNew == u8KeyTmp) && (KeyPressInterval != 0))
	{
		//键压下防抖200
		return;
	}
	
	if((u8KeyNew > cnMsgKey) && (u8KeyNew < cnMsgKey_Max))
	{
		//有新键压下，则
		++u16KeyPressedTmr; //定时器，按下计时
		u16KeyPressedTmr &= (~cnKeyPressed);
		if(u16KeyPressedTmr > cnKeyPressedT_Max)
		{
			//超长按住约束
			u16KeyPressedTmr = cnKeyPressedT_Max;
		}

		if(bIsKeyPressed == TRUE)
		{
			#if	0 //20201120	// 长按某键后滑到旁边的键，会对新键做长按键处理bug
			if(u8KeyTmp != u8KeyNew)
			{
				if((u8KeyTmp > cnMsgKey) && (u8KeyTmp < cnMsgKey_Max))
				{
					StationRun(u8KeyTmp, u16KeyPressedTmr); /*按键释放优先调用处理函数*/
				}
				
				SetkeyRelease();
				u16KeyPressedTmr = 0;
			}
			#endif

			u8KeyTmp = u8KeyNew;

			u16KeyPressedTmr |= cnKeyPressed;
			KeyPressInterval = (cnKeyDebounceT / cnKeyTaskT);		// 等待下一个按键的时间
			u16KeyReleaseTmr = (cnKeyReleaseDebounceT / cnKeyTaskT);
		}
		
		StationRun(u8KeyNew, u16KeyPressedTmr);		
	}
}



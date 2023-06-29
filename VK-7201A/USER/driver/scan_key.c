
#define	__EXT_SCANKEY_
#include "Globals.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
void Key_Init(void)
{
	// Ĭ�ϸ��ô����ڣ����Բ����ø���
	GPIO_SET_MUX_MODE(P00CFG, GPIO_MUX_TKKEY); //���óɴ�����TK18 -> TK00  
	GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_2); 
	
	GPIO_SET_MUX_MODE(P01CFG, GPIO_MUX_TKKEY); //���óɴ�����TK19 -> TK01
	GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_3); 
}

//�����Ƿ�ſ���1s�ڵĶ̰������ſ��Ŷ�����1s��ſ����޶���
bool_t Get_Key_IsRelease(uint16_t MsgValue)
{
	return (((MsgValue & cnKeyPressed) == 0) 
			&& (MsgValue < (cnKeyPressedT_1s & cnKeyUnpressed)) 
			&& IsKeyRelease());
}

//�жϳ������Ƿ���timeʱ��? ����ִ�ж���
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
����ɨ����ȣ�10ms task
*************************************************************/
static uint8_t ScanKeyRunCnt;
void ScanKey_Run_Task(void)
{
	++ScanKeyRunCnt;
	if(ScanKeyRunCnt < cnKeyTaskT)
		return;
	ScanKeyRunCnt = 0;	

	//�����������ʼ
	u8KeyNew = cnMsgNull;
	rdKeyValue = 0;
	
	if(KeyPressInterval > 0)
		--KeyPressInterval;

	//����ɨ��
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
		//���ͷŷ���200
		u16KeyReleaseTmr--;
		if((u16KeyReleaseTmr == 0) && (rdKeyValue == 0))
		{
			// ���м��ɿ�
			u16KeyPressedTmr &= (~cnKeyPressed);

			if((u8KeyTmp > cnMsgKey) && (u8KeyTmp < cnMsgKey_Max))
			{
				StationRun(u8KeyTmp, u16KeyPressedTmr); /*�����ͷ����ȵ��ô�����*/
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
		//��ѹ�·���200
		return;
	}
	
	if((u8KeyNew > cnMsgKey) && (u8KeyNew < cnMsgKey_Max))
	{
		//���¼�ѹ�£���
		++u16KeyPressedTmr; //��ʱ�������¼�ʱ
		u16KeyPressedTmr &= (~cnKeyPressed);
		if(u16KeyPressedTmr > cnKeyPressedT_Max)
		{
			//������סԼ��
			u16KeyPressedTmr = cnKeyPressedT_Max;
		}

		if(bIsKeyPressed == TRUE)
		{
			#if	0 //20201120	// ����ĳ���󻬵��Աߵļ�������¼�������������bug
			if(u8KeyTmp != u8KeyNew)
			{
				if((u8KeyTmp > cnMsgKey) && (u8KeyTmp < cnMsgKey_Max))
				{
					StationRun(u8KeyTmp, u16KeyPressedTmr); /*�����ͷ����ȵ��ô�����*/
				}
				
				SetkeyRelease();
				u16KeyPressedTmr = 0;
			}
			#endif

			u8KeyTmp = u8KeyNew;

			u16KeyPressedTmr |= cnKeyPressed;
			KeyPressInterval = (cnKeyDebounceT / cnKeyTaskT);		// �ȴ���һ��������ʱ��
			u16KeyReleaseTmr = (cnKeyReleaseDebounceT / cnKeyTaskT);
		}
		
		StationRun(u8KeyNew, u16KeyPressedTmr);		
	}
}



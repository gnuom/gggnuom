
#ifndef	__H_SCAN_KEY_
#define	__H_SCAN_KEY_

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef	__EXT_SCANKEY_
#define	SCANKEY_EXT
#else
#define SCANKEY_EXT		extern
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
#define cnTK_KEY_OnOff				cnTK0
#define cnTK_KEY_LED				cnTK1
#define cnTK_KEY_Menu				cnTK2 
#define cnTK_KEY_Left				cnTK3
#define cnTK_KEY_Right				cnTK4


#define	cnKeyDebounceT				(100UL)
#define	cnKeyReleaseDebounceT	 	(100UL)
#define	cnKeyTaskT					(4)//(10)

#define	cnKeyPressedT_Max			(30000UL / cnKeyDebounceT)
#define	cnKeyPressedT_0s2			((200UL / cnKeyDebounceT) | cnKeyPressed)
#define	cnKeyPressedT_1s			((1000UL / cnKeyDebounceT) | cnKeyPressed)
#define	cnKeyPressedT_1s5			((1500UL / cnKeyDebounceT) | cnKeyPressed)
#define	cnKeyPressedT_2s			((2000UL / cnKeyDebounceT) | cnKeyPressed)
#define	cnKeyPressedT_3s			((3000UL / cnKeyDebounceT) | cnKeyPressed)
#define	cnKeyPressedT_5s			((5000UL / cnKeyDebounceT) | cnKeyPressed)
#define	cnKeyPressedT_10s			((10000UL / cnKeyDebounceT) | cnKeyPressed)
#define	cnKeyPressedT_PowerOff		((1500UL / cnKeyDebounceT) | cnKeyPressed)

SCANKEY_EXT bool_t bKeyPressed;
#define	SetKeyProcessed()			do{ bKeyPressed = TRUE; }while(0)		// 该键已经响应过
#define	SetkeyRelease()				do{ bKeyPressed = FALSE; }while(0)		// 该键松开了
#define IsKeyRelease()				(bKeyPressed == FALSE)					// 该键是否松开

/*应用层使用以下接口*/
#define Set_Key_Processed()    		do{ SetKeyProcessed(); SetBuzzerRunTime(cnBzToneKeyPress); }while(0) //设置该按键已处理


///////////////////////////////////////////////////////////////////////////////////////////////////
SCANKEY_EXT void Key_Init(void);
SCANKEY_EXT bool_t Get_Key_IsRelease(uint16_t MsgValue);
SCANKEY_EXT bool_t Get_Key_IsPressed(uint16_t MsgValue, uint16_t Time);
SCANKEY_EXT void ScanKey_Run_Task(void);

#endif




#ifndef	__H_DEBUG_
#define	__H_DEBUG_

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef	__EXT_DEBUG_
#define	DEBUG_EXT
#else
#define DEBUG_EXT		extern
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
#define P_TX					P50
#define P_RX					//P10
#define SetTXPortDirOut()		do{ GPIO_SET_MUX_MODE(P50CFG, GPIO_MUX_GPIO); \
									GPIO_ENABLE_OUTPUT(P5TRIS, GPIO_PIN_0); \
									GPIO_DISABLE_UP(P5UP, GPIO_PIN_0); \
									GPIO_DISABLE_RD(P5RD, GPIO_PIN_0); \
									}while(0)
#define SetRXPortDirIn()		//do{ GPIO_SET_MUX_MODE(P10CFG, GPIO_MUX_GPIO); \
								//	GPIO_ENABLE_INPUT(P1TRIS, GPIO_PIN_0); \
								//	GPIO_DISABLE_UP(P1UP, GPIO_PIN_0); \
								//	GPIO_DISABLE_RD(P1RD, GPIO_PIN_0); \
								//	}while(0)


enum {
	cnRxStep_WaitStartH = 0,	// �ȴ�Rx���ϵ�H��ƽ
	cnRxStep_WaitStartBit,		// �ȴ�Rx��ʼλ
	cnRxStep_GetBit,			// Rx 8bit����
	cnRxStep_WaitEndBit,		// �ȴ�Rx����λ

	cnRxStep_Max
};

enum {
	cnTxStep_WaitStart = 0,		// �ȴ�Tx����ʱTx������ΪH��ƽ
	cnTxStep_SendStartBit,		// ������ʼλL��ƽ
	cnTxStep_SendBit,			// Tx 8bit����
	cnTxStep_SendEndBit,		// ���ͽ���λH��ƽ

	cnTxStep_Max
};


#ifdef cnDebug_Print
#define debug_print(x)			GpioUart_Send(x)
#else
#define debug_print(x)
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
DEBUG_EXT void Debug_Init(void);
DEBUG_EXT void GpioUart_Send(uint8_t dat);
DEBUG_EXT void SetDebugTimerCnt(uint16_t cnt);
DEBUG_EXT void Debug_Run_Task(void);



#endif




#ifndef	__H_CONST_
#define	__H_CONST_

///////////////////////////////////////////////////////////////////////////////////////////////////
#define	cnOn			1
#define	cnOff			0

typedef enum {
	cnSuccess = 0,					// �ɹ�
	cnFailure,			  			// ʧ��
	cnNoRespond,		  			// ����Ӧ
}RET_CODE;

#define	RAM_DATA		data
#define	RAM_iDATA		idata
#define	RAM_pDATA		pdata
#define	RAM_xDATA		xdata
#define ROM_DATA		code

#define GCC_NOP()		_nop_()

///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------
//	���ܺŶ���
//-------------------------------------
enum {
	cnFuncNumInit = 0x00,		// �ϵ��ʼ��
	cnFuncNumIdle,				// Idle����ģʽ
	cnFuncNumWorking,			// Working����ģʽ
	cnFuncNumEmergency,			// Emergency�����¼�
	//cnFuncNumICT,				// SMT�����Զ�����

	cnFuncNumCommon,			// ��ģʽ���ܺţ�ֻΪ��������Ϣ

	cnFuncNumMax				// ����ܺ�
};


/****************************************************
*	��������
*****************************************************/
#define	cnTK0 			0x00000001
#define	cnTK1			0x00000002
#define	cnTK2 			0x00000004
#define	cnTK3 			0x00000008

#define	cnTK4 			0x00000010
#define	cnTK5			0x00000020
#define	cnTK6 			0x00000040         //
#define	cnTK7 			0x00000080         //

#define	cnTK8 			0x00000100         //
#define	cnTK9 			0x00000200
#define	cnTK10 			0x00000400
#define	cnTK11 			0x00000800

#define	cnTK12 			0x00001000        //
#define	cnTK13 			0x00002000        //
#define	cnTK14 			0x00004000        //
#define	cnTK15 			0x00008000

#define	cnTK16 			0x00010000
#define	cnTK17 			0x00020000
#define	cnTK18 			0x00040000
#define	cnTK19			0x00080000

#define	cnTK20			0x00100000
#define	cnTK21			0x00200000
#define	cnTK22			0x00400000
#define	cnTK23			0x00800000

#define	cnTK39			0x01000000
#define	cnTK40			0x02000000       //
#define	cnTK41			0x04000000
#define	cnTK42			0x08000000

#define	cnTK43			0x10000000
#define	cnTK44			0x20000000


#define	cnKey1			(1 << 0)
#define	cnKey2			(1 << 1)
#define	cnKey3			(1 << 2)
#define	cnKey4			(1 << 3)
#define	cnKey5			(1 << 4)
#define	cnKey6			(1 << 5)
#define	cnKey7			(1 << 6)
#define	cnKey8			(1 << 7)
#define	cnKey9			(1 << 8)
#define	cnKey10			(1 << 9)
#define	cnKey11			(1 << 10)
#define	cnKey12			(1 << 11)
#define	cnKey13			(1 << 12)
#define	cnKey14			(1 << 13)
#define	cnKey15			(1 << 14)
#define	cnKeyPressed	(1 << 15)
#define	cnKeyUnpressed	(~cnKeyPressed)			// ���ɿ�
#define	cnKeyPressedTMax	(30000UL)				// 30*1000 = �����������ֵ30s

#define	cnKeyHoldT1s	(cnKeyPressed + 1000UL)	// 1s������
#define	cnKeyHoldT2s	(cnKeyPressed + 2000UL)	// 2s������
#define	cnKeyHoldT3s	(cnKeyPressed + 3000UL)	// 3s������

//-------------------------------------
//	��Ϣ����
//-------------------------------------
enum 
{
	cnMsgNull = 0,
	
	// Key message
	cnMsgKey,					// ������Ϣ
	cnMsgKeyPower,				// ��Դ��
	cnMsgKeyMenu,				// �˵�����ѡ���
	
	// Key combination
	cnMsgKeyCmb,				// ��ϼ�
	//cnMsgKeyCmbICT,				// SMT���ϲ���

	cnMsgKeyUnknow,				// δ֪����
	cnMsgKey_Max,				// �����������Ч��Ϣ	


	// detection message
	cnMsgDct,					// �������Ϣ(Sensor)

	cnMsgDct_Max,

	// command message
	cnMsgCmd,					// ������Ϣ

	cnMsgCmd_Max,				// ������Ϣ���ֵ


	cnMsgMax					// ������Ϣ�����ֵ
};
#define	cnMsgKeyNoKey	cnMsgKey		// û�м�����


#endif


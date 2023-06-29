#ifndef _REL_PROTOCOL_
#define _REL_PROTOCOL_

#include "CheckTouchKey_Set.h"

void REL_SenderLoop0();
// <!!!!! ע��ṹ����1�ֽڶ���,���ݴ��˳��ΪС��ģʽ
// ���ݷ���ʹ��,1:ʹ�ܣ����಻ʹ��
//#define REL_SENDER_ENABLE0	1

// ����ʵ�ֶ���
#include "uart0.h"
#define REL_PreSendCallBack()							
#define REL_SendByte(ch)									//UART0_SendChar(ch)
#define REL_EndSendCallBack()							

// �������Ͷ���
//typedef int s32;
//typedef short int s16;
//typedef char s8;

//typedef unsigned int u32;
//typedef unsigned short int u16;
//typedef unsigned char u8;

/*************************************************************************
***************************��������һ�㲻���޸�***************************
**************************************************************************/ 

// ��ͷ�ֽ�
#define REL_HEADER_BYTE	0xA0

// ��ͷ�ṹ
//#pragma pack(1)
typedef struct _PackHeader
{
	u8 length;					// ����,sizeof(PackHeader) + sizeof(PackStrcut) * n + 1
	u8 packIdxCur : 4;	// �ְ�����,��0��ʼ
	u8 packIdxMax : 4;	// ��������
	u8 typeId;					// ����ID,����ʹ�õĽṹ��
}PackHeader;
//#pragma pack()

// ���ģʽת����С��ģʽ
#define htol16(num) (((u16)(num) >> 8) | ((u16)(num) << 8))
#define htol32(num)	(((u32)(num) >> 24) | \
										(((u32)(num) >> 8) & 0x0000FF00) | \
										(((u32)(num) << 8) & 0x00FF0000) | \
										(((u32)(num) << 24)))

// ���շ��ͺ���					
#define REL_SendStart(packHeader)	\
	{u8 _checkSum = 0;\
	u8 _i;\
	u8 *_bufPoint;\
	REL_PreSendCallBack();\
	REL_SendByte(REL_HEADER_BYTE);\
	_bufPoint = (u8*)&packHeader;\
	for(_i = 0;_i < sizeof(packHeader);_i++,_bufPoint++) {\
		REL_SendByte(*_bufPoint);\
		_checkSum += *_bufPoint;\
	}
	
#define REL_SendNext(packStrcut) \
	_bufPoint = (u8*)&packStrcut;\
	for(_i = 0;_i < sizeof(packStrcut);_i++,_bufPoint++) {\
		REL_SendByte(*_bufPoint);\
		_checkSum += *_bufPoint;\
	}

#define REL_SendEnd()	\
	REL_SendByte(_checkSum);\
	REL_EndSendCallBack();}
	
#endif /*_REL_PROTOCOL_*/


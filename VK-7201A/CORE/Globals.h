
#ifndef	__H_GLOBALS_
#define	__H_GLOBALS_


///////////////////////////////////////////////////////////////////////////////////////////////////
//�̼��汾	�޶��汾(1 byte)|| �ΰ汾(1 byte)||���汾(1 byte),��:0A0201��ʾ1.2.10�汾
#define	cnFWVer_Major			1
#define	cnFWVer_Minor			0
#define	cnFWVer_Revised			0




///////////////////////////////////////////////////////////////////////////////////////////////////
//#define cnNTCModel_XF_Fast			// �η����ӦNTC
#define cnNTCModel_KonTan_TK_S			// ��ɽ���ױ�˹�������������޹�˾


///////////////////////////////////////////////////////////////////////////////////////////////////
// ע�⣺Release�汾ʱ������ر�����debug����������
#define cnDebug_Print						// ģ�⴮�ڵ��Խӿ�
//#define cnDebug_OffHeater


///////////////////////////////////////////////////////////////////////////////////////////////////
#include "CheckTouchKey_80F73xx.h"
#include "CheckTouchKey_Set.h"
#include "types.h"
#include "FWLib.h"

#include "REL_Protocol.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "const.h"
#include "station.h"
#include "subprog.h"

#include "driver.h"
#include "event.h"
#include "mid.h"

#endif



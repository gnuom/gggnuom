
#ifndef	__H_GLOBALS_
#define	__H_GLOBALS_


///////////////////////////////////////////////////////////////////////////////////////////////////
//固件版本	修订版本(1 byte)|| 次版本(1 byte)||主版本(1 byte),如:0A0201表示1.2.10版本
#define	cnFWVer_Major			1
#define	cnFWVer_Minor			0
#define	cnFWVer_Revised			0




///////////////////////////////////////////////////////////////////////////////////////////////////
//#define cnNTCModel_XF_Fast			// 鑫丰快响应NTC
#define cnNTCModel_KonTan_TK_S			// 中山市易比斯传感器技术有限公司


///////////////////////////////////////////////////////////////////////////////////////////////////
// 注意：Release版本时，必须关闭如下debug的条件开关
#define cnDebug_Print						// 模拟串口调试接口
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



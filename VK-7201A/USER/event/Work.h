
#ifndef	__H_WORKING_
#define	__H_WORKING_

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef	__EXT_WORKING_
#define	WORKING_EXT
#else
#define WORKING_EXT		extern
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum {
	cnWorkStatus_Stop = 0,				// 停止加热 
	cnWorkStatus_Select,				// 选择功能
	cnWorkStatus_PreHeat,				// 先加热
	cnWorkStatus_Ready,					// 温度已经达到
	cnWorkStatus_DoCooking1,			// 正在煮蛋: 第一阶段
	cnWorkStatus_DoCooking2,			// 正在煮蛋: 第二阶段
	cnWorkStatus_DoCooking3,			// 正在煮蛋: 第三阶段

	cnWorkStatus_Ending,				// 结束
	
	cnWorkStatus_Max
}WorkStatus_T;

typedef enum {
	cnWorkType_Null = 0,
	cnWorkType_CookedAll,				// 全熟
	cnWorkType_CookedMed,				// 半熟
	cnWorkType_CookedHot,				// 温泉蛋
	cnWorkType_Steam,					// 蒸鸡胸肉
	cnWorkType_Cooking,					// 蒸煮蔬菜

	cnWorkType_Max
}WorkType_T;

typedef struct {
	uint8_t temp;						// 温度
	uint32_t tmrms;						// 工作时长，单位：ms
}WorkPara_t;

typedef struct {
	WorkStatus_T status;			// 工作状态
	WorkType_T type;				// 类别
	WorkPara_t para;				// 参数：工作温度、时间
}Working_t;

WORKING_EXT Working_t RAM_xDATA Working;
#define ResetWorkingPara()			do{ sub_memset((uint8_t *)&Working, 0, sizeof(Working_t)); }while(0)
#define SetWorkingStatus(sta)		do{ Working.status = sta; }while(0)
#define IsWorkingStatusReady()		(Working.status >= cnWorkStatus_Ready)
#define IsWorkingStatus(sta)		(Working.status == sta)
#define IsWorkingTypeValid()		((Working.type > cnWorkType_Null) && (Working.type < cnWorkType_Max))


WORKING_EXT bool_t bIsWorkingStop;
#define EnableWorkingStop()			do{ bIsWorkingStop = TRUE; }while(0)


/* 温控设置 */
#define cnWTempCoffeePreHeat		(90)	// 预加热温度

// pump duty设置
#define cnPumpDutyPer_Min			(0)		
#define cnPumpDutyPer_ChgCell		(2)		//变化量	
#define cnPumpDutyPer_DoMin			(90UL)
#define cnPumpDutyPer_Default		(95UL)
#define cnPumpDutyPer_Max			(100UL)
#define cnPumpDutyPer_MaxMax		(100)

// 制作时间
#define cnWorkPHTBase				cnTBaseT_5ms
#define cnWorkingPreHeatT			(2*(1000UL/cnWorkPHTBase))
#define cnWorkingDoT				(30*60*(1000UL/cnWorkPHTBase))
#define cnWorkingDoEndingT			(5*(1000UL/cnWorkPHTBase))


///////////////////////////////////////////////////////////////////////////////////////////////////
WORKING_EXT void Working_Con(void);
WORKING_EXT void Working_De(void);

WORKING_EXT void Working_Run_Task(void);
WORKING_EXT void Working_PumpHeat_Run_Task(void);

WORKING_EXT RET_CODE StationRun_Working(uint8_t Msg, MsgValue_t MsgValue);


#endif


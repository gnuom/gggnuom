
#ifndef	__H_STATION_
#define	__H_STATION_

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef	__EXT_STATION_
#define	STATION_EXT
#else
#define STATION_EXT	extern
#endif

typedef	uint16_t		MsgValue_t;	
typedef struct			// 消息响应函数	
{
	uint8_t		Msg;
	RET_CODE	(*MsgCallBack)(MsgValue_t value);
}On_Command;


///////////////////////////////////////////////////////////////////////////////////////////////////
STATION_EXT uint8_t RAM_DATA FuncNum1st;
STATION_EXT uint8_t RAM_DATA FuncNum2nd;
STATION_EXT uint8_t RAM_DATA FuncNum3rd;

#define	GetCurWorkMode()				(FuncNum1st)
#define Get2ndWorkMode()				(FuncNum2nd)
#define Get3rdWorkMode()				(FuncNum3rd)

#define	IsCurWorkModeInit()				(FuncNum1st == cnFuncNumInit)
#define	Is2ndWorkModeInit()				(FuncNum2nd == cnFuncNumInit)
#define	IsCurWorkModeIdle()				(FuncNum1st == cnFuncNumIdle)
#define	Is2ndWorkModeIdle()				(FuncNum2nd == cnFuncNumIdle)
#define	IsCurWorkModeDisplay()			(FuncNum1st == cnFuncNumDisplay)
#define	Is2ndWorkModeDisplay()			(FuncNum2nd == cnFuncNumDisplay)
#define	IsCurWorkModeWorking()			(FuncNum1st == cnFuncNumWorking)
#define	Is2ndWorkModeWorking()			(FuncNum2nd == cnFuncNumWorking)
#define	IsCurWorkModeEmergency()		(FuncNum1st == cnFuncNumEmergency)
#define	Is2ndWorkModeEmergency()		(FuncNum2nd == cnFuncNumEmergency)
#define	IsCurWorkModeFlush()			(FuncNum1st == cnFuncNumFlush)
#define	Is2ndWorkModeFlush()			(FuncNum2nd == cnFuncNumFlush)
//#define	IsCurWorkModeICT()				(FuncNum1st == cnFuncNumICT)
//#define	Is2ndWorkModeICT()				(FuncNum2nd == cnFuncNumICT)


///////////////////////////////////////////////////////////////////////////////////////////////////
STATION_EXT void SetWorkMode(uint8_t mode);
STATION_EXT void ResumeWorkMode(void);

STATION_EXT RET_CODE NullRoutine(MsgValue_t value);
STATION_EXT RET_CODE StationRun(uint8_t Msg, MsgValue_t MsgValue);

#endif



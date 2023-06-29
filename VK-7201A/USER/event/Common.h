
#ifndef	__H_COMMON_
#define	__H_COMMON_

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef	__EXT_COMMON_
#define	COMMON_EXT
#else
#define COMMON_EXT		extern
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
#define	cnSystemStatusReportErrT		(50)	//(1*(500/cnTBaseT_10ms))	// 0.2s
#define	cnSystemStatusReportComT		(100)	//(1*(1000/cnTBaseT_10ms))	// 1s
#define	cnSystemStatusReportT			(500UL)	//(5*(1000/cnTBaseT_10ms))	// 5s



///////////////////////////////////////////////////////////////////////////////////////////////////
COMMON_EXT void Common_Init(void);
COMMON_EXT void Common_Run_Task(void);

COMMON_EXT RET_CODE StationRun_Common(uint8_t Msg, MsgValue_t MsgValue);


#endif


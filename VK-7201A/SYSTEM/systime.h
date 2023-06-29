#ifndef _TIME_H_
#define _TIME_H_

#ifdef	__EXT_TIME_
#define  TIME_EXT
#else
#define  TIME_EXT	extern
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
TIME_EXT bool_t bTime1ms;
TIME_EXT bool_t bTime5ms;
TIME_EXT bool_t bTime10ms;
TIME_EXT bool_t bTime100ms;
TIME_EXT bool_t bTime200ms;
TIME_EXT bool_t bTime500ms;
TIME_EXT bool_t bTime1s;

#define	IsTask1ms()				(bTime1ms == TRUE)
#define	IsTask5ms()				(bTime5ms == TRUE)
#define	IsTask10ms()			(bTime10ms == TRUE)
#define	IsTask100ms()			(bTime100ms == TRUE)
#define	IsTask200ms()			(bTime200ms == TRUE)
#define	IsTask500ms()			(bTime500ms == TRUE)
#define	IsTask1s()				(bTime1s == TRUE)

#define	ClearTaskFlag1ms()		do{ bTime1ms = FALSE; }while(0)
#define	ClearTaskFlag5ms()		do{ bTime5ms = FALSE; }while(0)
#define	ClearTaskFlag10ms()		do{ bTime10ms = FALSE; }while(0)
#define	ClearTaskFlag100ms()	do{ bTime100ms = FALSE; }while(0)
#define	ClearTaskFlag200ms()	do{ bTime200ms = FALSE; }while(0)
#define	ClearTaskFlag500ms()	do{ bTime500ms = FALSE; }while(0)
#define	ClearTaskFlag1s()		do{ bTime1s = FALSE; }while(0)


#define	cnTBaseT_1ms			(1)
#define	cnTBaseT_5ms			(5)
#define	cnTBaseT_10ms			(10)
#define	cnTBaseT_100ms			(100)
#define	cnTBaseT_200ms			(200)
#define	cnTBaseT_500ms			(500UL)
#define	cnTBaseT_1s				(1000UL)

TIME_EXT uint32_t RAM_DATA sysTotalTick;
#define	GetSysTotalTick()		(sysTotalTick)
#define	IsPowerOnMorethan20s()	(sysTotalTick > (20*1000UL/cnTBaseT_1ms))


///////////////////////////////////////////////////////////////////////////////////////////////////
TIME_EXT void SysTime_Config(void);

#endif //_TIME_H_


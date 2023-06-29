
#ifndef	__H_ICT_
#define	__H_ICT_

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef	__EXT_ICT_
#define	ICT_EXT
#else
#define ICT_EXT				extern
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
enum {
	cnICTStep_Start = 0,		// ICT测试开始：关闭所有显示
	cnICTStep_KeyPressed,		// 按键，对应的红/蓝Led熄灭/点亮
	cnICTStep_Heat,				// 加热电路检测
	cnICTStep_Pump,				// 水泵电路检测
	
	cnICTStep_LockSW,			// 开盖电路检测
	cnICTStep_NTC,				// NTC电路检测

	cnICTStep_End,				// 测试结束

	cnICTStep_Max
};

///////////////////////////////////////////////////////////////////////////////////////////////////
ICT_EXT void ICT_Con(void);
ICT_EXT void ICT_De(void);
ICT_EXT void ICT_Run_Task(void);

ICT_EXT On_Command ROM_DATA ICTTable[];


#endif


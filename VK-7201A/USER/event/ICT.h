
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
	cnICTStep_Start = 0,		// ICT���Կ�ʼ���ر�������ʾ
	cnICTStep_KeyPressed,		// ��������Ӧ�ĺ�/��LedϨ��/����
	cnICTStep_Heat,				// ���ȵ�·���
	cnICTStep_Pump,				// ˮ�õ�·���
	
	cnICTStep_LockSW,			// ���ǵ�·���
	cnICTStep_NTC,				// NTC��·���

	cnICTStep_End,				// ���Խ���

	cnICTStep_Max
};

///////////////////////////////////////////////////////////////////////////////////////////////////
ICT_EXT void ICT_Con(void);
ICT_EXT void ICT_De(void);
ICT_EXT void ICT_Run_Task(void);

ICT_EXT On_Command ROM_DATA ICTTable[];


#endif


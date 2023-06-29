
#ifndef	__H_EMERGENCY_
#define	__H_EMERGENCY_

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef	__EXT_EMERGENCY_
#define	EMERGENCY_EXT
#else
#define EMERGENCY_EXT				extern
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum {
	cnEmergencyType_Null = 0,
	cnEmergencyType_NTCBroken,		// NTC传感器故障
	cnEmergencyType_TempHi,			// 高温报警

	cnEmergencyType_Max
}Emergency_T;

EMERGENCY_EXT Emergency_T emergencyType;
#define IsCurWorkModeEmergency_NTCBroken()		(IsCurWorkModeEmergency() && (emergencyType == cnEmergencyType_NTCBroken))
#define IsCurWorkModeEmergency_TempHi()			(IsCurWorkModeEmergency() && (emergencyType == cnEmergencyType_TempHi))


///////////////////////////////////////////////////////////////////////////////////////////////////
EMERGENCY_EXT void Emergency_Con(void);
EMERGENCY_EXT void Emergency_NTCCon(void);
EMERGENCY_EXT void Emergency_TempHiCon(void);
EMERGENCY_EXT void Emergency_De(void);

EMERGENCY_EXT void Emergency_Run_Task(void);

EMERGENCY_EXT RET_CODE StationRun_Emergency(uint8_t Msg, MsgValue_t MsgValue);



#endif


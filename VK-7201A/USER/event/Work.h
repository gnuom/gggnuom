
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
	cnWorkStatus_Stop = 0,				// ֹͣ���� 
	cnWorkStatus_Select,				// ѡ����
	cnWorkStatus_PreHeat,				// �ȼ���
	cnWorkStatus_Ready,					// �¶��Ѿ��ﵽ
	cnWorkStatus_DoCooking1,			// ������: ��һ�׶�
	cnWorkStatus_DoCooking2,			// ������: �ڶ��׶�
	cnWorkStatus_DoCooking3,			// ������: �����׶�

	cnWorkStatus_Ending,				// ����
	
	cnWorkStatus_Max
}WorkStatus_T;

typedef enum {
	cnWorkType_Null = 0,
	cnWorkType_CookedAll,				// ȫ��
	cnWorkType_CookedMed,				// ����
	cnWorkType_CookedHot,				// ��Ȫ��
	cnWorkType_Steam,					// ��������
	cnWorkType_Cooking,					// �����߲�

	cnWorkType_Max
}WorkType_T;

typedef struct {
	uint8_t temp;						// �¶�
	uint32_t tmrms;						// ����ʱ������λ��ms
}WorkPara_t;

typedef struct {
	WorkStatus_T status;			// ����״̬
	WorkType_T type;				// ���
	WorkPara_t para;				// �����������¶ȡ�ʱ��
}Working_t;

WORKING_EXT Working_t RAM_xDATA Working;
#define ResetWorkingPara()			do{ sub_memset((uint8_t *)&Working, 0, sizeof(Working_t)); }while(0)
#define SetWorkingStatus(sta)		do{ Working.status = sta; }while(0)
#define IsWorkingStatusReady()		(Working.status >= cnWorkStatus_Ready)
#define IsWorkingStatus(sta)		(Working.status == sta)
#define IsWorkingTypeValid()		((Working.type > cnWorkType_Null) && (Working.type < cnWorkType_Max))


WORKING_EXT bool_t bIsWorkingStop;
#define EnableWorkingStop()			do{ bIsWorkingStop = TRUE; }while(0)


/* �¿����� */
#define cnWTempCoffeePreHeat		(90)	// Ԥ�����¶�

// pump duty����
#define cnPumpDutyPer_Min			(0)		
#define cnPumpDutyPer_ChgCell		(2)		//�仯��	
#define cnPumpDutyPer_DoMin			(90UL)
#define cnPumpDutyPer_Default		(95UL)
#define cnPumpDutyPer_Max			(100UL)
#define cnPumpDutyPer_MaxMax		(100)

// ����ʱ��
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


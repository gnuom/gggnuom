
#define	__EXT_LED_
#include "Globals.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
void Update_Led_Show(void)
{
}


///////////////////////////////////////////////////////////////////////////////////////////////////
static bool_t bLedBreathDir;
uint16_t LedBreathDuty;

void Led_Init(void)
{
	
	//����EPWM����ģʽ:
	// ����ģʽ+�������ģʽ+�ԳƼ���ģʽ+���¼���(���ض���)ģʽ
	PWM_ConfigRunMode(PWM_WFG_INDEPENDENT | PWM_OC_INDEPENDENT);
	//����EPWM����ʱ��	
	PWM_ConfigChannelClk(cnLedCom_EPWM, PWM_CLK_DIV_32);

	//����EPWM �����Լ�ռ�ձ�	
	PWM_ConfigChannelPeriod(cnLedCom_EPWM, cnLedComPWMPeriodNum);
	PWM_ConfigChannelDuty(cnLedCom_EPWM, 0);

	//����EPWM�ļ��ط�ʽΪ�Զ�����
	PWM_EnableAutoLoadMode(cnLedCom_chnEPWM_MSK);
	//����EPWM���������
	PWM_DisableReverseOutput(cnLedCom_chnEPWM_MSK); //�رշ������
	//����EPWM���
	PWM_EnableOutput(cnLedCom_chnEPWM_MSK);		//�������
	//����EPWM����
	PWM_DisableDeadZone(cnLedCom_EPWM);
	
	//����EPWM���IO����
	GPIO_SET_MUX_MODE(cnLedCom_PortCFG, cnLedCom_PortMUX);

	//����EPWM					
	PWM_Start(cnLedCom_chnEPWM_MSK);


	bLedBreathDir = TRUE;
	SetPortAllLedAsOut();
	TurnOffAllLed();
}

LedPara_t RAM_xDATA ledPara[cnLed_Max];
void SetLedStatus(Led_T led, LedStatus_T sta)
{
	if(ledPara[led].status == sta)
		return;
	if((ledPara[led].status == cnLedStatus_Flash_2times) && (ledPara[led].flashCnt != 0))
		return;

	ledPara[led].statusTmp = ledPara[led].status;
	ledPara[led].status = sta;
	ledPara[led].OnOff = cnLedOff;
	ledPara[led].flashCnt = 0;

	if(sta == cnLedStatus_Flash_100ms)
		ledPara[led].runTmrTmp = cnLedRunT_0s2;
	else if(sta == cnLedStatus_Flash_300ms)
		ledPara[led].runTmrTmp = cnLedRunT_0s5;
	else if(sta == cnLedStatus_Flash_2times)
	{
		ledPara[led].flashCnt = 2;
		ledPara[led].runTmrTmp = cnLedRunT_0s2;
	}	
	else
		ledPara[led].runTmrTmp = cnLedRunT_1s;

	ledPara[led].runTmr = ledPara[led].runTmrTmp;
}

static void TurnLedOnOff(Led_T led, uint8_t onoroff)
{
	switch(led)
	{
	case cnLedPower:
		{
			if(onoroff == cnLedOn)			LedPower_On();
			else							LedPower_Off();
		}
		break;
	case cnLedCookedAll:		// ȫ��
		{
			if(onoroff == cnLedOn)			LedCookedAll_On();
			else							LedCookedAll_Off();
		}
		break;
	case cnLedCookedMed:		// ����
		{
			if(onoroff == cnLedOn)			LedCookedMed_On();
			else							LedCookedMed_Off();
		}
		break;
	case cnLedCookedHot:		// ��Ȫ��
		{
			if(onoroff == cnLedOn)			LedCookedHot_On();
			else							LedCookedHot_Off();
		}
		break;
	case cnLedSteam:			// ��
		{
			if(onoroff == cnLedOn)			LedSteam_On();
			else							LedSteam_Off();
		}
		break;
	case cnLedCooking:			// ����
		{
			if(onoroff == cnLedOn)			LedCooking_On();
			else							LedCooking_Off();
		}
		break;
	}
}

void LedShow_Run_Task(void)
{
	uint8_t i;

	for(i=0; i<cnLed_Max; i++)
	{
		switch(ledPara[i].status)
		{
		case cnLedStatus_On:
			{
				TurnLedOnOff(i, cnLedOn);
				if((i>cnLed_Start) && (i<cnLed_Max))
					LedCom_On();
			}	
			break;
			
		case cnLedStatus_Flash_500ms:
		case cnLedStatus_Flash_300ms:
		case cnLedStatus_Flash_100ms:
		case cnLedStatus_Flash_2times:
			{
				if((++ledPara[i].runTmr) >= ledPara[i].runTmrTmp)
				{
					ledPara[i].runTmr = 0;
					if(ledPara[i].OnOff == cnLedOn)
					{
						ledPara[i].OnOff = cnLedOff;

						if(ledPara[i].status == cnLedStatus_Flash_2times)
						{
							if((--ledPara[i].flashCnt) == 0)
								SetLedStatus(i, ledPara[i].statusTmp);						
						}
					}	
					else
						ledPara[i].OnOff = cnLedOn;
				}

				if(ledPara[i].OnOff == cnLedOn)
				{
					TurnLedOnOff(i, cnLedOn);
				}	
				else
				{
					TurnLedOnOff(i, cnLedOff);
				}	

				if((i>cnLed_Start) && (i<cnLed_Max))
					LedCom_On();
			}
			break;
			
		case cnLedStatus_Breath:
			{
				if(bLedBreathDir)
				{
					LedBreathDuty += cnLedComPWMDutyStep;
					if(LedBreathDuty > (cnLedComPWMDutyMax-100))
					{
						bLedBreathDir = FALSE;
						//LedBreathDuty = cnLedComPWMDutyMax-100;
					}	
				}
				else
				{
					if(LedBreathDuty <= cnLedComPWMDutyStep)
						bLedBreathDir = TRUE;
					else
						LedBreathDuty -= cnLedComPWMDutyStep;
				}
				
				SetLedComPWM_Duty(LedBreathDuty);
				TurnLedOnOff(i, cnLedOn);
			}
			break;

		//case cnLedStatus_Off:
		default:
			TurnLedOnOff(i, cnLedOff);
			break;
		}
	}

	Update_Led_Show();
}



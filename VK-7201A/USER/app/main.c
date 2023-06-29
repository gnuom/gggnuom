
#include "Globals.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
	Init_Con();

	InitEnd();
	
	while(1)
	{
		// real time task
		
		// 1ms task
		if(IsTask1ms())
		{
			ClearTaskFlag1ms();

			ScanKey_Run_Task();
			Buzzer_Run_Task();
		}

		// 5ms task
		if(IsTask5ms())
		{
			ClearTaskFlag5ms();

			Working_PumpHeat_Run_Task();
		}

		// 10ms task
		if(IsTask10ms())
		{
			ClearTaskFlag10ms();
			
			NTC_Run_Task();
			LedShow_Run_Task();
		}

		// 100ms task
		if(IsTask100ms())
		{
			ClearTaskFlag100ms();
			
			Heater_Run_Task();

			Working_Run_Task();
			Debug_Run_Task();
		}

		if(IsTask200ms())
		{
			ClearTaskFlag200ms();
			
			ClearWDT();
			Init_Run_Task();
			Idle_Run_Task();
			Emergency_Run_Task();

			//ICT_Run_Task();
		}
		
		// 500ms task
		if(IsTask500ms())
		{
			ClearTaskFlag500ms();
			
		}

		// 1s task
		if(IsTask1s())
		{
			ClearTaskFlag1s();

		}
		
	}
}


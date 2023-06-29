
#define	__EXT_NTC_
#include "Globals.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
#define cnNTCResMin					48			// 高于200℃的电阻值
#define cnNTCResMax					170000		// 低于-30℃的电阻值
#define cnCheckNTCTempHLT			(500/cnTBaseT_10ms)		// 检测NTC超高温/超低温判断时间

#ifdef cnNTCModel_XF_Fast
#define cnBoilerNTCResTabNum		126
static uint16_t ROM_DATA BoilerNTC_Res_Tab[cnBoilerNTCResTabNum] = {
	32701,	31076,	29541,	28090,	26720,	25424,	24198,	23039,	21942,	20903,	// 0~9
	19920,	18988,	18105,	17268,	16475,	15722,	15008,	14331,	13688,	13077,	// 10~19
	12497,	11946,	11422,	10924,	10450,	10000,	9571,	9163,	8774,	8405, 	// 20~29
	8052,	7717,	7397,	7092,	6801,	6524,	6259,	6007,	5766,	5536, 	// 30~39
	5316,	5106,	4906,	4714,	4531,	4356,	4188,	4028,	3875,	3728, 	// 40~49
	3588,	3454,	3325,	3202,	3084,	2970,	2862,	2758,	2658,	2563,   // 50~59 
	2471,	2383,	2299,	2218,	2140,	2065,	1994,	1925,	1859,	1795,   // 60~69 
	1734,	1675,	1619,	1564,	1512,	1462,	1414,	1367,	1322,	1279,   // 70~79 
	1238,	1198,	1159,	1122,	1086,	1052,	1019,	987,	956,	926,	// 80~89   
	898,	870,	843,	817,	793,	769,	745,	723,	702,	681,	// 90~99   
	661,	641,	622,	604,	587,	570,	553,	537,	522,	507,	// 100~109   
	493,	479,	465,	452,	440,	428,	416,	404,	393,	383,   	// 110~119
	372,	362,	352,	343,	334,	325										// 120~125
};

#elif (defined(cnNTCModel_KonTan_TK_S))
#define cnBoilerNTCResTabNum		200
static uint16_t ROM_DATA BoilerNTC_Res_Tab[cnBoilerNTCResTabNum] = {
	30903,	29366,	27914,	26542,	25246,	24021,	22862,	21766,	20729,	19748,
	18818,	17938,	17103,	16313,	15563,	14852,	14177,	13537,	12930,	12353,
	11805,	11284,	10789,	10319,	9871,	9446,	9040,	8651,	8281,	7928,
	7593,	7275,	6971,	6682,	6407,	6145,	5895,	5657,	5430,	5213,
	5007,	4810,	4621,	4442,	4270,	4106,	3949,	3799,	3656,	3519,
	3388,	3261,	3140,	3024,	2912,	2806,	2704,	2606,	2512,	2421,
	2335,	2252,	2172,	2096,	2023,	1952,	1885,	1820,	1757,	1697,
	1640,	1584,	1531,	1480,	1431,	1383,	1338,	1294,	1251,	1211,
	1171,	1134,	1097,	1062,	1029,	996,	965,	935,	906,	878,
	851,	825,	800,	776,	752,	730,	708,	687,	666,	647,
	628,	609,	592,	575,	558,	542,	527,	512,	497,	483,
	470,	457,	444,	432,	420,	409,	397,	387,	376,	366,
	356,	347,	338,	329,	320,	312,	304,	296,	288,	281,
	273,	266,	260,	253,	247,	241,	235,	229,	223,	218,
	212,	207,	202,	197,	192,	188,	183,	179,	174,	170,
	166,	162,	158,	155,	151,	147,	144,	141,	137,	134,
	131,	128,	125,	122,	119,	117,	114,	111,	109,	106,
	104,	102,	99,		97,		95,		93,		91,		89,		87,		85,
	83,		81,		80,		78,		76,		75,		73,		72,		70,		69,
	67,		66,		64,		63,		62,		60,		59,		58,		57,		56
};

#else
#define cnBoilerNTCResTabNum		200
static uint16_t ROM_DATA BoilerNTC_Res_Tab[cnBoilerNTCResTabNum] = {
	31769,	30160,	28642,	27209,	25856,	24580,	23375,	22237,	21164,	20150,	// 0~9
	19192,	18288,	17434,	16628,	15866,	15146,	14466,	13823,	13215,	12641,	// 10~19
	12098,	11585,	11100,	10641,	10207,	9796,	9376,	8976,	8596,	8233,	// 20~29
	7887,	7557,	7243,	6944,	6658,	6385, 	6125, 	5876, 	5639, 	5413, 	// 30~39
	5197, 	4990, 	4793, 	4604, 	4424, 	4251, 	4086, 	3928, 	3778, 	3633, 	// 40~49
	3495, 	3363, 	3236, 	3115, 	2998, 	2887, 	2781, 	2678, 	2580, 	2486, 	// 50~59
	2396, 	2310, 	2227, 	2147, 	2071, 	1998, 	1927, 	1860, 	1795, 	1733,	// 60~69
	1673,	1615,	1560,	1507,	1456,	1407,	1360,	1314,	1270,	1228,	// 70~79
	1188,	1149,	1111,	1075,	1041,	1007,	975,	944,	914,	885,	// 80~89
	857,	830,	804,	779,	755,	732,	710,	688,	667,	647,	// 90~99
	628,	609,	591,	573,	556,	540,	524,	509,	494,	480,	// 100~109
	466,	453,	440,	428,	416,	404,	393,	382,	371,	361,	// 110~119
	351,	341,	332,	323,	314,	306,	298,	290,	282,	275,	// 120~129
	268,	261,	254,	247,	241,	235,	229,	223,	217,	212,	// 130~139
	206,	201,	196,	191,	187,	182,	178,	173,	169,	165,	// 140~149
	161,	157,	154,	150,	147,	143,	140,	137,	134,	130,	// 150~159
	128,	125,	122,	119,	116,	114,	111,	109,	106,	104,	// 160~169
	102,	100,	97,		95,		93,		91,		89,		87,		86,		84,		// 170~179
	82,		80,		79,		77,		75,		74,		72,		71,		69,		68,		// 180~189
	66,		65,		64,		62,		61,		60,		59,		58,		56,		55		// 190~199
};

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
/*
		5V
		---
		 |
		|-|
		| | Rx
		|_|
		 |		_____
		 |------|	|----------------> ADC_Port
		 |		-----		 |
		|-|		  2K		 |
		| |	10K				---
		|_|					--- 100nF
		 |					 |
		 |--------------------
		---
		 -  GND

电压转换为电阻值的计算方法:
	 10000 				    Vb5.0 * Vad
--------------- * Va5.0  =  -----------
  (Rx+10000)	   			  4095

Rx	: 为待求的NTC电阻值，单位欧姆
Vad : 为AD转换器的读数，AD的基准电压为Vb5.0为5V，分辨率为12bit.
Va5.0 : 用于NTC工作电压5V，请参考原理图
10000 : 分压电阻的阻值,单位欧姆。
最后的欧姆结果再除以10，缩小10倍，以适用上面数组的电阻值。

整合之后的公式: Rx = 1000*(4095-Vad)/Vad;
*/


Temp_NTC_t RAM_xDATA tempNTC;

void NTC_Init(void)
{
	GetADC_Init();
	
	tempNTC.NTCErr = cnNTC_Err_OK;
	tempNTC.TempHighCnt = 0;
	tempNTC.TempLowCnt = 0;
	tempNTC.temp = 0xFF;
}

static uint8_t Get_NTC_averTemp(uint8_t temp)
{
	uint8_t i;
	
	if(tempNTC.temp == 0xFF)
		sub_memset((uint8_t *)tempNTC.tempBuf, temp, cnGetNTCNum);
	else
	{
		for(i=1; i<cnGetNTCNum; i++)
			tempNTC.tempBuf[cnGetNTCNum-i] = tempNTC.tempBuf[cnGetNTCNum-1-i];
		tempNTC.tempBuf[0] = temp;
	}

	temp = sub_getchecksum_u16((uint8_t *)tempNTC.tempBuf, cnGetNTCNum) / cnGetNTCNum;
	return temp;
}

void NTC_Run_Task(void)
{
	uint8_t temp;
	uint16_t Vad;
	uint32_t Rx;

//return;

	// 读取ADC值
	Vad = Read_BoilerNTC_ADC();
	if(Vad == 0)
	{
		tempNTC.NTCErr = cnNTC_Err_RxShort;
		tempNTC.temp = 0;
		return;
	}
	if(Vad >= 4095)
	{
		tempNTC.NTCErr = cnNTC_Err_RxOpen;
		tempNTC.temp = 0;
		return;
	}
	
	// 转换为电阻
	Rx = 1000UL * (4095 - Vad) / Vad;
	
	// 转换为温度值
	if((Rx >= BoilerNTC_Res_Tab[cnBoilerNTCResTabNum-1]) && (Rx <= BoilerNTC_Res_Tab[0]))
	{
		for(temp=0; temp<(cnBoilerNTCResTabNum-1); temp++)
		{
			if((Rx <= BoilerNTC_Res_Tab[temp]) && (Rx > BoilerNTC_Res_Tab[temp+1]))
				break;
		}

		tempNTC.NTCErr = cnNTC_Err_OK;
		tempNTC.TempLowCnt = 0;
		tempNTC.TempHighCnt = 0;
	}
	else
	{
		if(Rx < BoilerNTC_Res_Tab[cnBoilerNTCResTabNum-1])
		{
			temp = cnBoilerNTCResTabNum - 1;
			if((++tempNTC.TempHighCnt) > cnCheckNTCTempHLT)
			{
				tempNTC.TempHighCnt = cnCheckNTCTempHLT;
				tempNTC.NTCErr = cnNTC_Err_TempHigh;
			}
		}
		else
		{
			temp = 0;
			if((++tempNTC.TempLowCnt) > cnCheckNTCTempHLT)
			{
				tempNTC.TempLowCnt = cnCheckNTCTempHLT;
				tempNTC.NTCErr = cnNTC_Err_TempLow;
			}
		}
	}

	tempNTC.temp = Get_NTC_averTemp(temp);
}		


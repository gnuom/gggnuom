
#define	__EXT_SUBPROG_
#include "Globals.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
void sub_memset(uint8_t *buf, uint8_t ch, uint16_t len)
{
	uint16_t i;
	for(i = 0; i < len; i++)
		buf[i] = ch;
}

void sub_memcpy(uint8_t *src, uint8_t *dst, uint16_t len)
{
	uint16_t i;
	for(i = 0; i < len; i++)
		dst[i] = src[i];
}

/*
bool_t sub_memcmp(uint8_t xdata *buf1, uint8_t xdata *buf2, uint8_t len)
{
	uint8_t i;
	for(i = 0; i < len; i++)
	{
		if(buf1[i] != buf2[i])
			return FALSE;
	}

	return TRUE;
}
*/

uint8_t sub_getchecksum(uint8_t *buf, uint16_t len)
{
	uint16_t i;
	uint8_t sum;

	sum = 0;
	for(i = 0; i < len; i++)
		sum += buf[i];

	return sum;
}

uint16_t sub_getchecksum_u16(uint8_t *buf, uint16_t len)
{
	uint16_t i;
	uint16_t sum;

	sum = 0;
	for(i = 0; i < len; i++)
		sum += buf[i];

	return sum;
}


uint16_t sub_getaveragev(uint16_t *buf, uint8_t len)
{
	uint8_t i;
	uint32_t sum;

	sum = 0;
	for(i = 0; i < len; i++)
		sum += buf[i];

	return (uint16_t)(sum / len);
}

//大、小端交换
uint16_t swapBigLittle(uint16_t iData)
{
	uint16_t tmpL, tmpH;
	
	tmpL = iData >> 8;
	tmpH = iData << 8;
	
	return (tmpH | tmpL);
}

//字符串转数字
uint8_t sub_atoi(char *str)
{
	uint8_t nResult = 0;
	
	if(str == NULL)
	{
		return 0;
	}
	
	while((*str >= '0') && (*str <= '9'))
	{
		nResult = nResult * 10 + (*str - '0'); 
	}
	return nResult;
}

//数字转字符串：n - 要转化的数字，radix转换基数，如：10、16、8、2
void sub_itos(int n, char *str, int radix)
{
	int i = 0;
	int m = n;
	int f = 0;
	
	if(n == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return;
	}
	else if(n < 0)
	{
		str[0] = '-';
		n = -n;
		f = 1;
	}
	
	while(m)
	{
		m /= radix;
		i++;
	}
	
	str[i + f] = '\0';
	i--;
	
	while(n)
	{
		str[i + f] = n % radix;
		if(str[i + f] < 10)
		{
			str[i + f] += '0';
		}
		else
		{
			str[i + f] += ('a' - 10);
		}
		n /= radix;
		i--;
	}
}

//字符串长度函数
uint8_t sub_Strlen(char str[])
{
	uint8_t len = 0;
	
	while (str[len] != '\0')
	{
		len++;
	}
	return len;
}

//字符串拷贝函数
void sub_Strcpy(char str1[], char str2[])
{
	uint8_t len = 0;
	
	while (str2[len] != '\0' || str1[len] != '\0')
	{
		str1[len] = str2[len];
		len++;
	}
	str1[len] = '\0';
}

//字符串拷贝N个函数
void sub_nStrcpy(char str1[], char str2[], uint8_t n)
{
	uint8_t i;
	uint8_t len = 0;
	
	for(i = 0; i < n; i++)
	{
		if(str2[len] == '\0')
		{
			break;
		}
		str1[len] = str2[len];
		len++;
	}
	str1[len] = '\0';
}

//字符串拼接函数
void sub_Strcat(char str1[], char str2[])
{
	uint8_t len = 0;
	uint8_t len1 = 0;
	
	while (str1[len] != '\0')
	{
		len++;
	}
	while (str2[len1] != '\0')
	{
		str1[len] = str2[len1];
		len++;
		len1++;
	}
	str1[len] = '\0';
}

//字符串比较函数
int8_t sub_Strcmp(char str1[], char str2[])
{
	int len = 0;

	while((str1[len] != '\0') || (str2[len] != '\0'))
	{
		if(str1[len] > str2[len])
		{
			return 1;
		}
		else if(str1[len] < str2[len])
		{
			return -1;
		}
		else
		{
			len++;
		}
	}
	return 0;
}

//字符查找
char * sub_Strchr(char *str, char ch)
{   
	while (*str != '\0')
	{
		if(*str == ch)
		{
			return str;
		}
		str++;
	}
	return NULL;
}

//字符串的查找 
char * sub_Strstr(char *str1, char *str2)
{
	char *p = str1;  
	char *str2Begin = str2;
	
	while (*str1 != '\0')
	{
		p = str1;     
		str2 = str2Begin;  
		while (*str1 == *str2 || *str2 == '\0')
		{ 
			if(*str2 == '\0') 
			{
				return p;
			}
			str2++;  
			str1++;
		}
		str1 = p; 
		str1++;  
	}
	return NULL;
}

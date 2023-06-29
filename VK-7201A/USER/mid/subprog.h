
#ifndef	__H_SUBPROG_
#define	__H_SUBPROG_

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef	__EXT_SUBPROG_
#define	SUBPROG_EXT
#else
#define SUBPROG_EXT	extern
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
#define NOP()			_nop_()

SUBPROG_EXT void sub_memset(uint8_t *buf, uint8_t ch, uint16_t len);
SUBPROG_EXT void sub_memcpy(uint8_t *src, uint8_t *dst, uint16_t len);
//SUBPROG_EXT bool_t sub_memcmp(uint8_t *buf1, uint8_t *buf2, uint8_t len);
SUBPROG_EXT uint8_t sub_getchecksum(uint8_t *buf, uint16_t len);
SUBPROG_EXT uint16_t sub_getchecksum_u16(uint8_t *buf, uint16_t len);
SUBPROG_EXT uint16_t sub_getaveragev(uint16_t *buf, uint8_t len);

//by csm add 20200826
SUBPROG_EXT uint16_t swapBigLittle(uint16_t big);
SUBPROG_EXT uint8_t sub_atoi(char *str);
SUBPROG_EXT void sub_itos(int n, char *str, int radix);
SUBPROG_EXT uint8_t sub_Strlen(char str[]);
SUBPROG_EXT void sub_Strcpy(char str1[], char str2[]);
SUBPROG_EXT void sub_nStrcpy(char str1[], char str2[], uint8_t n);
SUBPROG_EXT void sub_Strcat(char str1[], char str2[]);
SUBPROG_EXT int8_t sub_Strcmp(char str1[], char str2[]);
SUBPROG_EXT char * sub_Strchr(char *str, char ch);
SUBPROG_EXT char * sub_Strstr(char *str1, char *str2);

#endif



#ifndef __USART1_H__
#define __USART1_H__

#include "stm32f4xx.h"
#include "sys.h"
#include "stdio.h"	
#include "stm32f4xx_conf.h"

/* 提供给其他C文件调用的函数 -----------------------------------------------------------------------------------------------*/
void Usart1_Init(u32 Bound);
/* 深度值获取相关程序  */

int hextoDec(int hex);                        //十六进制转十进制
void newdepth_jieshou(void);                      //打印深度值程序

/*定义 -------------------------------------------------------------------------------------------------------------------*/

#endif


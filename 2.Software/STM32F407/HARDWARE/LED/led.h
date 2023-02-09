#ifndef __LED_H__
#define __LED_H__

#include "sys.h"

//LED端口定义
#define LED0 PFout(9)	// DS0
#define LED1 PFout(10)	// DS1	 

void LED_Init(void);//初始化		
 				    
#endif

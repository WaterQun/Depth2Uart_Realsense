#ifndef __TIM1_H
#define __TIM1_H

#include "stm32f4xx.h"


/* 提供给其他C文件调用的函数 -----------------------------------------------------------------------------------------------*/
void TIM10_PWM_Init(uint16_t Per,uint16_t Psc);
void TIM11_PWM_Init(uint16_t Per,uint16_t Psc);

#endif

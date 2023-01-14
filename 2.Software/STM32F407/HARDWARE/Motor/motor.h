/**
  *************************************************************************************************************************
  * @file    motor.c
  * @author  @你认识
  * @version V1.0
  * @date    2022-10-06
  * @brief   tb6612模块.h文件配置
  *************************************************************************************************************************/
	
#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f4xx.h"
#include "sys.h"
/*定义 -------------------------------------------------------------------------------------------------------------------*/
#define M_left_IN1     PCout(4)
#define M_left_IN2     PAout(5)
#define M_right_IN3    PAout(4)
#define M_right_IN4    PAout(7)

typedef enum
{
  FORWARD,
	BACK,
	STOP
}Motor_Choose;

/* 提供给其他C文件调用的函数 -----------------------------------------------------------------------------------------------*/
void Motor_Init(void);//PB12,PB13,PB14,PB15
void Moror_Left(Motor_Choose Direction);
void Moror_Right(Motor_Choose Direction);








#endif

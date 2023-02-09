#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "stm32f4xx.h"
#include "sys.h"
/*���� -------------------------------------------------------------------------------------------------------------------*/
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

/* �ṩ������C�ļ����õĺ��� -----------------------------------------------------------------------------------------------*/
void Motor_Init(void);//PB12,PB13,PB14,PB15
void Moror_Left(Motor_Choose Direction);
void Moror_Right(Motor_Choose Direction);

#endif

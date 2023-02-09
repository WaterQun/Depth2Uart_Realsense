#include "motor.h"

/***
 * 函数名:Motor_Init
 * 描述:电机对应引脚的初始化
 * 输入:无
 * 输出:无
 */
void Motor_Init(void)//PC4,PA5,PA4,PA7
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOF时钟

	//GPIO初始化设置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7;//
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;//IO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIO
}

/***
 * 函数名:Moror_Left
 * 描述:右轮电机控制函数
 * 输入:Direction=(FORWARD,BACK,STOP)
 * 输出:无
 */
void Moror_Left(Motor_Choose Direction)
{

	if(FORWARD == Direction)
	{
		M_left_IN1 = 1;
		M_left_IN2 = 0;
	}
	else if(BACK == Direction)
	{
		M_left_IN1 = 0;
		M_left_IN2 = 1;
	}
	else if(STOP == Direction)
	{
		M_left_IN1 = 0;
		M_left_IN2 = 0;
	}
}	
	
/***
 * 函数名:Moror_Right
 * 描述:左轮电机控制函数
 * 输入:Direction=(FORWARD,BACK,STOP)
 * 输出:无
 */
void Moror_Right(Motor_Choose Direction)
{
  	if(FORWARD == Direction)
	{
	  	M_right_IN3 = 1;
	  	M_right_IN4 = 0;
	}
	else if(BACK == Direction)
	{
	  	M_right_IN3 = 0;
	  	M_right_IN4 = 1;
	}
	else if(STOP == Direction)
	{
	  	M_right_IN3 = 0;
	  	M_right_IN4 = 0;
	}
}		

#include "motor.h"

/***
 * ������:Motor_Init
 * ����:�����Ӧ���ŵĳ�ʼ��
 * ����:��
 * ���:��
 */
void Motor_Init(void)//PC4,PA5,PA4,PA7
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��GPIOFʱ��

	//GPIO��ʼ������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7;//
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;//IO��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIO
}

/***
 * ������:Moror_Left
 * ����:���ֵ�����ƺ���
 * ����:Direction=(FORWARD,BACK,STOP)
 * ���:��
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
 * ������:Moror_Right
 * ����:���ֵ�����ƺ���
 * ����:Direction=(FORWARD,BACK,STOP)
 * ���:��
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

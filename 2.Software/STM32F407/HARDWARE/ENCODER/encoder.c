/**
  *************************************************************************************************************************
  * @file    encoder.c�ļ�
  * @author  @����ʶ
  * @version V1.0
  * @date    2022-10-11
  * @brief   ������.c�����ļ�
  *************************************************************************************************************************/
	
#include "encoder.h"


/***
 * ������:TIM3_Encoder_Init
 * ����:��ʱ��2����������
 * ����:��
 * ���:��
 */
void TIM3_Encoder_Init(void)//PC6,PC7
{
	//�ṹ�嶨��
  	GPIO_InitTypeDef GPIO_InitStructure;
  	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
  	TIM_ICInitTypeDef TIM_ICInitStructure;      
  	//PC6 ch1  A,PC7 ch2 B 
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	//GPIO��ʼ������
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;        
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //����   
  	GPIO_Init(GPIOC, &GPIO_InitStructure);                           
	//�˿ڸ���
  	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3);
  	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM3);
	//TIM��ʱ����ʼ������
	TIM_TimeBaseInitStructure.TIM_Period = 0;                       //������װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = 65535;                //����ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //����ʱ�ӷָ�
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //����TIM���ϼ���
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	//���ñ�����ģʽ
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	//���벶���ʼ������
	TIM_ICInitStructure.TIM_ICFilter = 10;                          //����Ƚ��˲���
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	//��ʱ��2��ʼ��
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_SetCounter(TIM3,0);
	//ʹ�ܶ�ʱ��
	TIM_Cmd(TIM3,ENABLE);
}

/***
 * ������:TIM4_Encoder_Init
 * ����:��ʱ��4����������
 * ����:��
 * ���:��
 */
void TIM4_Encoder_Init(void)//PD12 ch1  A,PD13 ch2 B 
{
	//�ṹ�嶨��
	GPIO_InitTypeDef GPIO_InitStructure;
  	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
  	TIM_ICInitTypeDef TIM_ICInitStructure;      
  	//PD12 ch1  A,PD13 ch2 B ����ʱ��
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  	//����GPIO
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;        
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //����
  	GPIO_Init(GPIOD, &GPIO_InitStructure);                           
  	//�˿ڸ���
  	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);
  	GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);
	//TIM��ʱ����ʼ������
	TIM_TimeBaseInitStructure.TIM_Period = 0;                       //������װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = 65535;                //����ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //����ʱ�ӷָ�
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //����TIM���ϼ���
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	//���ñ�����ģʽ
	TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	//���벶���ʼ������
	TIM_ICInitStructure.TIM_ICFilter = 10;                          //����Ƚ��˲���
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	//��ʱ��2��ʼ��
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	TIM_SetCounter(TIM4,0);
	//ʹ�ܶ�ʱ��
	TIM_Cmd(TIM4,ENABLE);  
}

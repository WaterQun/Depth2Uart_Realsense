/**
  *************************************************************************************************************************
  * @file    tim1.c�ļ� 
  * @author  @����ʶ
  * @version V1.0
  * @date    2020-10-09
  * @brief   ��ʱ��1����PWM.c���ú���
  *************************************************************************************************************************/

#include "tim1.h"

/***
 * ������:TIM10_PWM_Init
 * ����:��ʱ��10���PWM���ú���
 * ����:Per(�Զ���װֵ), Pscʱ��Ԥ��Ƶ��)
 * ���:��
 */ 
void TIM10_PWM_Init(uint16_t Per,uint16_t Psc)//PF6,PF7
{
	//GPIO��NVIC��TIM�ṹ�嶨��
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	//����GPIO��TIM10�Լ���ӳ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource6,GPIO_AF_TIM10); //GPIOF6����Ϊ��ʱ��10

	//GPIO��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;//GPIOF6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOF,&GPIO_InitStructure);
	//TIM��ʼ��
	TIM_TimeBaseInitStructure.TIM_Prescaler = Psc;                                  //����ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;                 //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_Period = Per;                                     //�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;                     //����ʱ�ӷָ�
	TIM_TimeBaseInit(TIM10,&TIM_TimeBaseInitStructure);

	//��ʼ��TIM1 Channel1��Channel1 PWMģʽ
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                               //ѡ��PWMģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;                  //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;                       //������Ը�
	//TIM_OCInitStructure.TIM_Pulse = 0;
  //��ʼ��TM10��CH1 PWM
  TIM_OC1Init(TIM10, &TIM_OCInitStructure);
  //ɲ���������Ĵ���
//  TIM_CtrlPWMOutputs(TIM1,ENABLE);//����PWM��(�߼���ʱ������)
	//ʹ��Ԥװ�ؼĴ���
	TIM_OC1PreloadConfig(TIM10, TIM_OCPreload_Enable);
	//ARPEʹ�� 
	TIM_ARRPreloadConfig(TIM10,ENABLE);
	//ʹ��TIM10
	TIM_Cmd(TIM10,ENABLE);

}
/***
 * ������:TIM11_PWM2_Init
 * ����:��ʱ��11���PWM���ú���
 * ����:Per(�Զ���װֵ), Pscʱ��Ԥ��Ƶ��)
 * ���:��
 */
void TIM11_PWM_Init(uint16_t Per,uint16_t Psc)//PF7
{
	//GPIO��NVIC��TIM�ṹ�嶨��
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	//����GPIO��TIM11�Լ���ӳ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource7,GPIO_AF_TIM11); //GPIOF7����Ϊ��ʱ��11
	//GPIO��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//GPIOF7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOF,&GPIO_InitStructure);
	//TIM��ʼ��
	TIM_TimeBaseInitStructure.TIM_Period = Per;                                     //�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = Psc;                                  //����ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;                 //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;                     //����ʱ�ӷָ�
	TIM_TimeBaseInit(TIM11,&TIM_TimeBaseInitStructure);

	//��ʼ��TIM1 Channel1��Channel1 PWMģʽ
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                               //ѡ��PWMģʽ1
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;                       //������Ը�
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;                  //�Ƚ����ʹ��
//	TIM_OCInitStructure.TIM_Pulse = 0;
  //��ʼ��TM11��CH1 PWM
  TIM_OC1Init(TIM11, &TIM_OCInitStructure);
  //ɲ���������Ĵ���
//  TIM_CtrlPWMOutputs(TIM1,ENABLE);//����PWM��(�߼���ʱ������)
	//ʹ��Ԥװ�ؼĴ���
	TIM_OC1PreloadConfig(TIM11, TIM_OCPreload_Enable);
	//ARPEʹ�� 
	TIM_ARRPreloadConfig(TIM11,ENABLE);
	//ʹ��TIM11
	TIM_Cmd(TIM11,ENABLE);
	
//	TIM_CtrlPWMOutputs(TIM11,ENABLE);
}






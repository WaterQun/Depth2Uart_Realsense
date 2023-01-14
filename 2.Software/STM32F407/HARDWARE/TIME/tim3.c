/**
  *************************************************************************************************************************
  * @file    tim3.c�ļ� 
  * @author  @����ʶ
  * @version V1.0
  * @date    2020-10-09
  * @brief   ��ʱ��3.c���ú���
  *************************************************************************************************************************/

#include "tim3.h"

/**
 * ������:Tim3_Init
 * ����:��ʱ-10ms
 * ����:��
 * ���:��
 */
//��ʱ10ms 
void TIM3_Init(void)
{	
	//TIM��NVIC�ṹ�嶨��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
  //����TIM3ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseInitStructure.TIM_Period = 72-1;                    //�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = 10000-1;              //����ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //����ʱ�ӷָ�
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ���
	//NVIC��ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;                //����TIM3�ⲿ�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;      //������ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;             //������Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                //ʹ���ⲿ�ж�
	//NVIC��TIM3��ʼ��	
  NVIC_Init(&NVIC_InitStructure);
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	//����TIM3
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	//ʹ��TIM3
	TIM_Cmd(TIM3,ENABLE);
}





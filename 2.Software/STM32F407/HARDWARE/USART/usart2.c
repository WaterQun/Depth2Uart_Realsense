/**
  *************************************************************************************************************************
  * @file    usart2.c
  * @author  @����ʶ
  * @version V1.0
  * @date    2022-10-08
  * @brief   ����2.c�ļ�����
  *************************************************************************************************************************/
	
#include "usart2.h"

/***
 * ������: Usart2_Init
 * ����:   Usart2��ʼ��
 * ����:   Bound��������
 * ���:   ��
 */
 
void Usart2_Init(u32 Bound)
{
	//GPIO,USART,NVIC���ýṹ��
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//��������ʱ�Ӻ�GPIOʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA2����ΪUSART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA3����ΪUSART1
	//���ڸ�λ
  USART_DeInit(USART2);	
	//USART3�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA2��GPIOA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA2��PA3
	//USART2����
	USART_InitStructure.USART_BaudRate = Bound;                                     //����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     //�˸��ֳ�
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                          //һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;                             //����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��Ӳ��������
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;                   //�շ�ģʽ
	//NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;           //ʹ��USART1�ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //ʹ���ⲿͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;    //��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;           //��Ӧ���ȼ�
  //�����жϣ�ʹ�ܴ���
  USART_ITConfig(USART2,USART_IT_RXNE, ENABLE);                   //�����ж�
  USART_Cmd(USART2, ENABLE);                                  //ʹ�ܴ���
  //GPIO,USART,NVIC��ʼ��
  GPIO_Init(GPIOA,&GPIO_InitStructure);
	USART_Init(USART2, &USART_InitStructure);
	NVIC_Init(&NVIC_InitStructure);
}







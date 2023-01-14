/**
  *************************************************************************************************************************
  * @file    usart3.c
  * @author  @����ʶ
  * @version V1.0
  * @date    2022-10-08
  * @brief   ����3.c�ļ�����
  *************************************************************************************************************************/
	
#include "usart3.h"

/***
 * ������: Usart3_Init
 * ����:   Usart3��ʼ��
 * ����:   Bound��������
 * ���:   ��
 */
 
void Usart3_Init(u32 Bound)
{
	//GPIO,USART,NVIC���ýṹ��
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//���ڸ�λ
	USART_DeInit(USART3);
	//��������ʱ�Ӻ�GPIOʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //GPIOB10����ΪUSART3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOB11����ΪUSART3
	
	//USART3�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //GPIOB10��GPIOB11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOB,&GPIO_InitStructure); //��ʼ��PB10��PB11
	//USART3����
	USART_InitStructure.USART_BaudRate = Bound;                                     //����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     //�˸��ֳ�
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                          //һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;                             //����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��Ӳ��������
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;                   //�շ�ģʽ
	//NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;           //ʹ��USART3�ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //ʹ���ⲿͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;    //��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;           //��Ӧ���ȼ�
  //�����жϣ�ʹ�ܴ���
  USART_ITConfig(USART3,USART_IT_RXNE, ENABLE);                   //�����ж�
  USART_Cmd(USART3, ENABLE);                                  //ʹ�ܴ���
  //GPIO,USART,NVIC��ʼ��
  GPIO_Init(GPIOB,&GPIO_InitStructure);
	USART_Init(USART3, &USART_InitStructure);
	NVIC_Init(&NVIC_InitStructure);
}







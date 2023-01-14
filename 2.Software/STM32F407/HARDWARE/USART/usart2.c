/**
  *************************************************************************************************************************
  * @file    usart2.c
  * @author  @你认识
  * @version V1.0
  * @date    2022-10-08
  * @brief   串口2.c文件配置
  *************************************************************************************************************************/
	
#include "usart2.h"

/***
 * 函数名: Usart2_Init
 * 描述:   Usart2初始化
 * 输入:   Bound—波特率
 * 输出:   无
 */
 
void Usart2_Init(u32 Bound)
{
	//GPIO,USART,NVIC配置结构体
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//开启串口时钟和GPIO时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA2复用为USART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA3复用为USART1
	//串口复位
  USART_DeInit(USART2);	
	//USART3端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA2与GPIOA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA2，PA3
	//USART2配置
	USART_InitStructure.USART_BaudRate = Bound;                                     //波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     //八个字长
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                          //一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;                             //无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件控制流
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;                   //收发模式
	//NVIC配置
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;           //使能USART1外部中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //使能外部通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;    //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;           //响应优先级
  //开启中断，使能串口
  USART_ITConfig(USART2,USART_IT_RXNE, ENABLE);                   //开启中断
  USART_Cmd(USART2, ENABLE);                                  //使能串口
  //GPIO,USART,NVIC初始化
  GPIO_Init(GPIOA,&GPIO_InitStructure);
	USART_Init(USART2, &USART_InitStructure);
	NVIC_Init(&NVIC_InitStructure);
}







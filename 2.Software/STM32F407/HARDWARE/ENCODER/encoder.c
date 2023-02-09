/**
  *************************************************************************************************************************
  * @file    encoder.c文件
  * @author  @你认识
  * @version V1.0
  * @date    2022-10-11
  * @brief   编码器.c配置文件
  *************************************************************************************************************************/
	
#include "encoder.h"


/***
 * 函数名:TIM3_Encoder_Init
 * 描述:定时器2编码器配置
 * 输入:无
 * 输出:无
 */
void TIM3_Encoder_Init(void)//PC6,PC7
{
	//结构体定义
  	GPIO_InitTypeDef GPIO_InitStructure;
  	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
  	TIM_ICInitTypeDef TIM_ICInitStructure;      
  	//PC6 ch1  A,PC7 ch2 B 
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	//GPIO初始化配置
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;        
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //下拉   
  	GPIO_Init(GPIOC, &GPIO_InitStructure);                           
	//端口复用
  	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3);
  	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM3);
	//TIM定时器初始化配置
	TIM_TimeBaseInitStructure.TIM_Period = 0;                       //设置重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 65535;                //设置时钟频率除数的预分频值
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //设置时钟分割
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //设置TIM向上计数
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	//设置编码器模式
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	//输入捕获初始化配置
	TIM_ICInitStructure.TIM_ICFilter = 10;                          //输入比较滤波器
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	//定时器2初始化
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_SetCounter(TIM3,0);
	//使能定时器
	TIM_Cmd(TIM3,ENABLE);
}

/***
 * 函数名:TIM4_Encoder_Init
 * 描述:定时器4编码器配置
 * 输入:无
 * 输出:无
 */
void TIM4_Encoder_Init(void)//PD12 ch1  A,PD13 ch2 B 
{
	//结构体定义
	GPIO_InitTypeDef GPIO_InitStructure;
  	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
  	TIM_ICInitTypeDef TIM_ICInitStructure;      
  	//PD12 ch1  A,PD13 ch2 B 开启时钟
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  	//配置GPIO
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;        
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //下拉
  	GPIO_Init(GPIOD, &GPIO_InitStructure);                           
  	//端口复用
  	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);
  	GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);
	//TIM定时器初始化配置
	TIM_TimeBaseInitStructure.TIM_Period = 0;                       //设置重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 65535;                //设置时钟频率除数的预分频值
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //设置时钟分割
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //设置TIM向上计数
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	//设置编码器模式
	TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	//输入捕获初始化配置
	TIM_ICInitStructure.TIM_ICFilter = 10;                          //输入比较滤波器
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	//定时器2初始化
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	TIM_SetCounter(TIM4,0);
	//使能定时器
	TIM_Cmd(TIM4,ENABLE);  
}

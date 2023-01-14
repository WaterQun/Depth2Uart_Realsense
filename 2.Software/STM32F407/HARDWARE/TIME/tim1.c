/**
  *************************************************************************************************************************
  * @file    tim1.c文件 
  * @author  @你认识
  * @version V1.0
  * @date    2020-10-09
  * @brief   定时器1配置PWM.c配置函数
  *************************************************************************************************************************/

#include "tim1.h"

/***
 * 函数名:TIM10_PWM_Init
 * 描述:定时器10输出PWM配置函数
 * 输入:Per(自动重装值), Psc时钟预分频数)
 * 输出:无
 */ 
void TIM10_PWM_Init(uint16_t Per,uint16_t Psc)//PF6,PF7
{
	//GPIO，NVIC，TIM结构体定义
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	//开启GPIO，TIM10以及重映射时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource6,GPIO_AF_TIM10); //GPIOF6复用为定时器10

	//GPIO初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;//GPIOF6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOF,&GPIO_InitStructure);
	//TIM初始化
	TIM_TimeBaseInitStructure.TIM_Prescaler = Psc;                                  //设置时钟频率除数的预分频值
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;                 //向上计数模式
	TIM_TimeBaseInitStructure.TIM_Period = Per;                                     //设置自动重装载寄存器周期的值
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;                     //设置时钟分割
	TIM_TimeBaseInit(TIM10,&TIM_TimeBaseInitStructure);

	//初始化TIM1 Channel1和Channel1 PWM模式
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                               //选择PWM模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;                  //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;                       //输出极性高
	//TIM_OCInitStructure.TIM_Pulse = 0;
  //初始化TM10的CH1 PWM
  TIM_OC1Init(TIM10, &TIM_OCInitStructure);
  //刹车和死区寄存器
//  TIM_CtrlPWMOutputs(TIM1,ENABLE);//产生PWM波(高级定时器独有)
	//使能预装载寄存器
	TIM_OC1PreloadConfig(TIM10, TIM_OCPreload_Enable);
	//ARPE使能 
	TIM_ARRPreloadConfig(TIM10,ENABLE);
	//使能TIM10
	TIM_Cmd(TIM10,ENABLE);

}
/***
 * 函数名:TIM11_PWM2_Init
 * 描述:定时器11输出PWM配置函数
 * 输入:Per(自动重装值), Psc时钟预分频数)
 * 输出:无
 */
void TIM11_PWM_Init(uint16_t Per,uint16_t Psc)//PF7
{
	//GPIO，NVIC，TIM结构体定义
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	//开启GPIO，TIM11以及重映射时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource7,GPIO_AF_TIM11); //GPIOF7复用为定时器11
	//GPIO初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//GPIOF7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOF,&GPIO_InitStructure);
	//TIM初始化
	TIM_TimeBaseInitStructure.TIM_Period = Per;                                     //设置自动重装载寄存器周期的值
	TIM_TimeBaseInitStructure.TIM_Prescaler = Psc;                                  //设置时钟频率除数的预分频值
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;                 //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;                     //设置时钟分割
	TIM_TimeBaseInit(TIM11,&TIM_TimeBaseInitStructure);

	//初始化TIM1 Channel1和Channel1 PWM模式
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                               //选择PWM模式1
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;                       //输出极性高
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;                  //比较输出使能
//	TIM_OCInitStructure.TIM_Pulse = 0;
  //初始化TM11的CH1 PWM
  TIM_OC1Init(TIM11, &TIM_OCInitStructure);
  //刹车和死区寄存器
//  TIM_CtrlPWMOutputs(TIM1,ENABLE);//产生PWM波(高级定时器独有)
	//使能预装载寄存器
	TIM_OC1PreloadConfig(TIM11, TIM_OCPreload_Enable);
	//ARPE使能 
	TIM_ARRPreloadConfig(TIM11,ENABLE);
	//使能TIM11
	TIM_Cmd(TIM11,ENABLE);
	
//	TIM_CtrlPWMOutputs(TIM11,ENABLE);
}






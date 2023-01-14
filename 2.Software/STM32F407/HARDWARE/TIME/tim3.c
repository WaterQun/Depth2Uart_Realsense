/**
  *************************************************************************************************************************
  * @file    tim3.c文件 
  * @author  @你认识
  * @version V1.0
  * @date    2020-10-09
  * @brief   定时器3.c配置函数
  *************************************************************************************************************************/

#include "tim3.h"

/**
 * 函数名:Tim3_Init
 * 描述:定时-10ms
 * 输入:无
 * 输出:无
 */
//定时10ms 
void TIM3_Init(void)
{	
	//TIM，NVIC结构体定义
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
  //开启TIM3时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	//定时器TIM3初始化
	TIM_TimeBaseInitStructure.TIM_Period = 72-1;                    //设置自动重装载寄存器周期的值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 10000-1;              //设置时钟频率除数的预分频值
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //设置时钟分割
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数
	//NVIC初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;                //开启TIM3外部中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;      //设置抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;             //设置响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                //使能外部中断
	//NVIC，TIM3初始化	
  NVIC_Init(&NVIC_InitStructure);
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	//开启TIM3
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	//使能TIM3
	TIM_Cmd(TIM3,ENABLE);
}





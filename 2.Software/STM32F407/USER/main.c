#include "sys.h"
#include "delay.h"
#include "motor.h"
#include "usart1.h"
#include "encoder.h"
#include "tim1.h"
#include "tim3.h"
#include "oled.h"
#include "led.h"
#include "key.h"

int depth; //定义用户深度值
u32 num;   //定义中断计数变量

//测试接收变量
int testRece1     =0;
int testRece2     =0;

int main(void)
{ 	
	extern int newdepth;             //定义与调用全局变量(串口深度值)
	extern int depth;                //定义与调用全局变量(用户定义深度值)
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	Usart1_Init(115200);
	//TIM3_Init();                 //定时器3-10ms定时
	TIM3_Encoder_Init();           //定时器3编码器配置
	TIM4_Encoder_Init();           //定时器4编码器配置
	Motor_Init();                  //电机对应引脚gpio初始化
	delay_init(168);               //初始化延时函数
	LED_Init();                    //LED初始化
	OLED_Init();                   //OLED初始化
	KEY0_Init();                   //按键初始化
	Exti_Init();                   //外部中断初始化
 	TIM10_PWM_Init(500-1,84-1);	
	TIM11_PWM_Init(500-1,84-1);    //84M/84=1Mhz的计数频率,重装载值500，所以PWM频率为 1M/500=2Khz.     
	
	OLED_ShowString(26,0,"FS-TAST",16,1);     //固定位置不变
	OLED_ShowString(10,24,"old:",16,1);       //固定位置不变
	OLED_ShowString(10,44,"new:",16,1);       //固定位置不变
	
	LED0=0;	
	depth = 1000;                  //给深度值初步赋值
  	//newdepth = 1500;               //给深度值初步赋值(串口)
		
	while(1) 
	{
		OLED_Refresh();
		delay_ms(10);
    	newdepth_jieshou();
		
		TIM_SetCompare1(TIM10,300);	//修改比较值，修改占空比(左轮)
		TIM_SetCompare1(TIM11,300); //修改比较值，修改占空比(右轮)
		//Moror_Left(FORWARD);	      //前进(左轮)
		//Moror_Right(FORWARD);       //前进(右轮)
		
    	OLED_ShowNum(45,24,depth,4,16,0);      //OLED显示(深度值用户赋值)
		OLED_ShowNum(45,44,newdepth,4,16,0);   //OLED显示(深度值串口赋值)

		//必须的延时
		delay_ms(13);
		
		if(newdepth == 0)
		{
			Moror_Left (STOP);	
      		Moror_Right(STOP);
		}
		if( depth > newdepth+200)
		{
			Moror_Left (FORWARD);	
      		Moror_Right(FORWARD);
		}
		if(((newdepth+200) >= depth) && (depth >= (newdepth-200)))
		{
		  	Moror_Left (STOP);	
      		Moror_Right(STOP);
		}
		if(depth < newdepth-200)
		{
		  	Moror_Left (BACK);	
      		Moror_Right(BACK);
		}
	}
}

//外部中断KEY服务程序
void EXTI4_IRQHandler(void)
{
	delay_ms(10);	//消抖
	
	//if(EXTI_GetITStatus(EXTI_Line4)!= RESET)
	//{
	num ++;
	LED0 = ~LED0;
	switch (num)
	{
		case 1:
			depth = 1500;
			break;
		case 2:
			depth = 2000;
			break;
		case 3:
			depth = 2500;
			num =0;
			break;
		default:
			break;
	}
  	EXTI_ClearITPendingBit(EXTI_Line4);//清除中断标志
	//}
}

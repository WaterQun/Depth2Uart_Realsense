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

int depth; //�����û����ֵ
u32 num;   //�����жϼ�������

//���Խ��ձ���
int testRece1     =0;
int testRece2     =0;

int main(void)
{ 	
	extern int newdepth;             //���������ȫ�ֱ���(�������ֵ)
	extern int depth;                //���������ȫ�ֱ���(�û��������ֵ)
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	Usart1_Init(115200);
	//TIM3_Init();                 //��ʱ��3-10ms��ʱ
	TIM3_Encoder_Init();           //��ʱ��3����������
	TIM4_Encoder_Init();           //��ʱ��4����������
	Motor_Init();                  //�����Ӧ����gpio��ʼ��
	delay_init(168);               //��ʼ����ʱ����
	LED_Init();                    //LED��ʼ��
	OLED_Init();                   //OLED��ʼ��
	KEY0_Init();                   //������ʼ��
	Exti_Init();                   //�ⲿ�жϳ�ʼ��
 	TIM10_PWM_Init(500-1,84-1);	
	TIM11_PWM_Init(500-1,84-1);    //84M/84=1Mhz�ļ���Ƶ��,��װ��ֵ500������PWMƵ��Ϊ 1M/500=2Khz.     
	
	OLED_ShowString(26,0,"FS-TAST",16,1);     //�̶�λ�ò���
	OLED_ShowString(10,24,"old:",16,1);       //�̶�λ�ò���
	OLED_ShowString(10,44,"new:",16,1);       //�̶�λ�ò���
	
	LED0=0;	
	depth = 1000;                  //�����ֵ������ֵ
  	//newdepth = 1500;               //�����ֵ������ֵ(����)
		
	while(1) 
	{
		OLED_Refresh();
		delay_ms(10);
    	newdepth_jieshou();
		
		TIM_SetCompare1(TIM10,300);	//�޸ıȽ�ֵ���޸�ռ�ձ�(����)
		TIM_SetCompare1(TIM11,300); //�޸ıȽ�ֵ���޸�ռ�ձ�(����)
		//Moror_Left(FORWARD);	      //ǰ��(����)
		//Moror_Right(FORWARD);       //ǰ��(����)
		
    	OLED_ShowNum(45,24,depth,4,16,0);      //OLED��ʾ(���ֵ�û���ֵ)
		OLED_ShowNum(45,44,newdepth,4,16,0);   //OLED��ʾ(���ֵ���ڸ�ֵ)

		//�������ʱ
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

//�ⲿ�ж�KEY�������
void EXTI4_IRQHandler(void)
{
	delay_ms(10);	//����
	
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
  	EXTI_ClearITPendingBit(EXTI_Line4);//����жϱ�־
	//}
}

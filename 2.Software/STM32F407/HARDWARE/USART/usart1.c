/**
  *************************************************************************************************************************
  * @file    usart1.c
  * @author  @你认识
  * @version V1.0
  * @date    2022-10-08
  * @brief   串口1.c文件配置
  *************************************************************************************************************************/
	
#include "usart1.h"

/*定义 -------------------------------------------------------------------------------------------------------------------*/
unsigned char table_data[5]; //这是提前定义一个数组存放接收到的数据
unsigned char table_cp[5];   //这是额外定义一个数组，将接收到的数据复制到这里面
unsigned short count=0;      //接收数据计数
int newdepth;

/***
 * 函数名: Usart1_Init
 * 描述:   Usart1初始化
 * 输入:   Bound—波特率
 * 输出:   无
 */
 
void Usart1_Init(u32 Bound)
{
   GPIO_InitTypeDef GPIO_InitStructure;
	 USART_InitTypeDef USART_InitStructure;
	 NVIC_InitTypeDef NVIC_InitStruct;
	//开启串口时钟和GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_USART1); //GPIOB6复用为USART1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_USART1); //GPIOB7复用为USART1
	//串口复位
  USART_DeInit(USART1);	
	//USART3端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; //GPIOB6与GPIOB7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure); //初始化PB6，PB7
	
//USART配置
	 USART_InitStructure.USART_BaudRate = Bound;                                     //波特率设置
	 USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     //字长为8位
	 USART_InitStructure.USART_StopBits = USART_StopBits_1;                          //一个停止位
	 USART_InitStructure.USART_Parity = USART_Parity_No;                             //无奇偶校验位
   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件数据流控制
	 USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;                    //收发模式
//NVIC中断配置
	 NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;                                  //使能USART外部中断通道
	 NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;                          //抢占优先级3
	 NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;                                 //子优先级3
	 NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;                                    //使能外部中断通道

	
//GPIO,USART,NVIC初始化	
	 GPIO_Init(GPIOA, &GPIO_InitStructure);
	 USART_Init(USART1, &USART_InitStructure);
	 NVIC_Init(&NVIC_InitStruct);
	 
//开启中断
  USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
//使能串口
  USART_Cmd(USART1, ENABLE);
}

/***
 * 函数名:
 * 描述:
 * 输入:
 * 输出:
 */
//使用自定义协议接收十六进制数据



int hextoDec(int hex)
{
	 int sum=0,mul=1;
	 int i,r;
	 int count=0;
	 do{
	  r=hex%16;
	  for(i=0;i<count;i++)
	   mul*=16;
	  mul*=r;
	  sum+=mul;
	  mul=1;
	  count++; 
	 }while(hex/=16);
	 return sum;
}

void newdepth_jieshou(void)
{
	int num_H,num_L,i;
	if(table_cp[0]==0x55)//如果数组第一个十六进制数据是0X2C则进行
	{
		//用十进制数据打印一下接收到的数据
		//原始数据（十六进制数据）是55 AA 00 00 0D 0A
		//前两位是固定的，第7个和第8个十六进制数据分别是CO2的高八位和低八位
		for(i=0;i<5;i++)
		{
				printf(" %d \n",table_cp[i]);
		}
		
		printf("\r\n");//加一个回车换行
		//把对应的十六进制数据转化为十进制数据
		num_H=hextoDec(table_cp[2]);//高8位
		num_L=hextoDec(table_cp[3]);//低8位
		printf("hh=%d LL=%d \n",num_H,num_L);
		newdepth=num_H*256+num_L;//使用CO2浓度计算公式计算出数值
		printf("newdepth=%d\n",newdepth);
	}
}

void USART1_IRQHandler(void)                 	//串口1中断服务程序
{
	u8 Res,i;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断
	{
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据
		
		if(count==0)//如果是接收的第一个数据
		{
			table_data[count]=Res;//将第一个数据存到数据中第一元素
			if(table_data[0]==0x55)//判断接收的第一个数据是不是十六进制0X2C
			  count++;//如果第一个数据是0X2C则表示正确计数+1
		}
		else if(count==1)//第一个数据接收正确的情况下，判断第二个数据
		{
			if(Res==0xAA)//如果刚接收的数据是0xE4则表示数据正确
			{
				table_data[count]=Res;//将数据储存到数组第二个元素位置
				count++;//接收数据计数+1
			}
			else//如果第二个字符不是0XE4则计数清零，重新接收
				count=0;
		}
		else if(count==2&&Res==0)//如果前两个数据正确，接收的第三个数据是0，则清零计数，重新接收数据
		{ 
			count=0;
		}
		else if(count>1&&count<5)//这是可以接收数据的范围，只要count在数据可接收数据范围内即可进行存入数据
		{
			table_data[count]=Res;
			count++;
		}
		else if(count>=5)//如果接收数据超过数组大小，则清零重新接收
		{
			count=0;
		}		
   } 
	 
	//	memset(&table_cp, 0, sizeof(table_data));//在使用数组table_cp时清空
		for(i=0;i<5;i++)//把接收到的数据复制到table_cp数组中
		{
			 table_cp[i]= table_data[i];
	}
} 



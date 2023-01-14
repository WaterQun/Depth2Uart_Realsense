#include "mbotLinuxUsart.h"
#include "usart.h"         //包含printf

/*--------------------------------发送协议-----------------------------------
//----------------55 AA  00 00  0D 0A----------------------
//数据头55aa +   两个数据位（利用共用体）  + 数据尾）0D 0A
//注意：这里数据中预留了一个字节的控制位，其他的可以自行扩展，更改size和数据
--------------------------------------------------------------------------*/

/*--------------------------------接收协议-----------------------------------
//----------------55 AA  00 00  0D 0A----------------------
//数据头55aa +   两个数据位（利用共用体）  + 数据尾）0D 0A
//注意：这里数据中预留了一个字节的控制位，其他的可以自行扩展，更改size和数据
--------------------------------------------------------------------------*/


/**************************************************************************
通信的发送函数和接收函数必须的一些常量、变量、共用体对象
**************************************************************************/

//数据接收暂存区
unsigned char  receiveBuff[6] = {0};         
//通信协议常量
const unsigned char header[2]  = {0x55, 0xAA};//前两位检验头
const unsigned char ender[2]   = {0x0D, 0x0A};//后两位检验尾

//定义一个深度变量
u32 newdepth;

//发送数据（左轮速、右轮速、角度）共用体（-32767 - +32768）
//union sendData
//{
//	short d;
//	unsigned char data[2];
//}leftVelNow,rightVelNow,angleNow;

//深度变量共用体
union receiveData
{
	short d;
	unsigned char data[2];
}newdepth1,newdepth2;

/**************************************************************************
函数功能：通过串口中断服务函数，获取上位机发送的左右轮控制速度、预留控制标志位，分别存入参数中
入口参数：左轮轮速控制地址、右轮轮速控制地址、预留控制标志位
返回  值：无特殊意义
**************************************************************************/
int usartReceiveOneData(int *p_newdepth1,int *p_newdepth2)//数据接收
{
	unsigned char USART_Receiver              = 0;          //接收数据
//	static unsigned char checkSum             = 0;
	static unsigned char USARTBufferIndex     = 0;
	static short k=0;
	static unsigned char USARTReceiverFront   = 0;
	static unsigned char Start_Flag           = START;      //一帧数据传送开始标志位
	//static short dataLength                   = 0;          //数据长度

	USART_Receiver = USART_ReceiveData(USART1);   //@@@@@#####如果你使用不是USART1更改成相应的，比如USART3
	//接收消息头
	if(Start_Flag == START)
	{
		if(USART_Receiver == 0xAA)                             //buf[1]
		{  
			if(USARTReceiverFront == 0x55)        //数据头两位 //buf[0]
			{
				Start_Flag = !START;              //收到数据头，开始接收数据
				//printf("header ok\n");	
				receiveBuff[0]=header[0];         //buf[0]
				receiveBuff[1]=header[1];         //buf[1]
				USARTBufferIndex = 0;             //缓冲区初始化
			}
		}
		else 
		{
			USARTReceiverFront = USART_Receiver;  
		}
	}
	else
    { 
		switch(USARTBufferIndex)
		{
			case 0://接收两个数据位
			  receiveBuff[2] = USART_Receiver;//buf[2]
			  receiveBuff[3] = USART_Receiver;//buf[3]
			  USARTBufferIndex++;
				break;			
			case 1://接收信息尾
				if(k==0)
				{
					//数据0d     buf[4]  无需判断
					k++;
				}
				else if (k==1)
				{
					//数据0a     buf[5] 无需判断

					//newdepth = receiveBuff[2]*256 + receiveBuff[3];
					//进行赋值操作										
						newdepth1.data[0]  = receiveBuff[2]; //buf[2] 
						newdepth2.data[0]  = receiveBuff[3]; //buf[3] 
									
					
					//速度赋值操作
					*p_newdepth1  = (int)newdepth1.d;
					*p_newdepth2  = (int)newdepth2.d;
					
//					//ctrlFlag
//					*p_crtlFlag = receiveBuff[7];                //buf[7]

					//完成一个数据包的接收，相关变量清零，等待下一字节数据
					USARTBufferIndex   = 0;
					USARTReceiverFront = 0;
					Start_Flag         = START;
//					checkSum           = 0;
					//dataLength         = 0;
					k = 0;
					//-----------------------------------------------------------------					
				}
				break;
			 default:break;
		}		
	}
		return 0;
}

/**********************************END***************************************/








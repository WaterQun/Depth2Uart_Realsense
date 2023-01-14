#include "mbotLinuxUsart.h"
#include "usart.h"         //����printf

/*--------------------------------����Э��-----------------------------------
//----------------55 AA  00 00  0D 0A----------------------
//����ͷ55aa +   ��������λ�����ù����壩  + ����β��0D 0A
//ע�⣺����������Ԥ����һ���ֽڵĿ���λ�������Ŀ���������չ������size������
--------------------------------------------------------------------------*/

/*--------------------------------����Э��-----------------------------------
//----------------55 AA  00 00  0D 0A----------------------
//����ͷ55aa +   ��������λ�����ù����壩  + ����β��0D 0A
//ע�⣺����������Ԥ����һ���ֽڵĿ���λ�������Ŀ���������չ������size������
--------------------------------------------------------------------------*/


/**************************************************************************
ͨ�ŵķ��ͺ����ͽ��պ��������һЩ���������������������
**************************************************************************/

//���ݽ����ݴ���
unsigned char  receiveBuff[6] = {0};         
//ͨ��Э�鳣��
const unsigned char header[2]  = {0x55, 0xAA};//ǰ��λ����ͷ
const unsigned char ender[2]   = {0x0D, 0x0A};//����λ����β

//����һ����ȱ���
u32 newdepth;

//�������ݣ������١������١��Ƕȣ������壨-32767 - +32768��
//union sendData
//{
//	short d;
//	unsigned char data[2];
//}leftVelNow,rightVelNow,angleNow;

//��ȱ���������
union receiveData
{
	short d;
	unsigned char data[2];
}newdepth1,newdepth2;

/**************************************************************************
�������ܣ�ͨ�������жϷ���������ȡ��λ�����͵������ֿ����ٶȡ�Ԥ�����Ʊ�־λ���ֱ���������
��ڲ������������ٿ��Ƶ�ַ���������ٿ��Ƶ�ַ��Ԥ�����Ʊ�־λ
����  ֵ������������
**************************************************************************/
int usartReceiveOneData(int *p_newdepth1,int *p_newdepth2)//���ݽ���
{
	unsigned char USART_Receiver              = 0;          //��������
//	static unsigned char checkSum             = 0;
	static unsigned char USARTBufferIndex     = 0;
	static short k=0;
	static unsigned char USARTReceiverFront   = 0;
	static unsigned char Start_Flag           = START;      //һ֡���ݴ��Ϳ�ʼ��־λ
	//static short dataLength                   = 0;          //���ݳ���

	USART_Receiver = USART_ReceiveData(USART1);   //@@@@@#####�����ʹ�ò���USART1���ĳ���Ӧ�ģ�����USART3
	//������Ϣͷ
	if(Start_Flag == START)
	{
		if(USART_Receiver == 0xAA)                             //buf[1]
		{  
			if(USARTReceiverFront == 0x55)        //����ͷ��λ //buf[0]
			{
				Start_Flag = !START;              //�յ�����ͷ����ʼ��������
				//printf("header ok\n");	
				receiveBuff[0]=header[0];         //buf[0]
				receiveBuff[1]=header[1];         //buf[1]
				USARTBufferIndex = 0;             //��������ʼ��
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
			case 0://������������λ
			  receiveBuff[2] = USART_Receiver;//buf[2]
			  receiveBuff[3] = USART_Receiver;//buf[3]
			  USARTBufferIndex++;
				break;			
			case 1://������Ϣβ
				if(k==0)
				{
					//����0d     buf[4]  �����ж�
					k++;
				}
				else if (k==1)
				{
					//����0a     buf[5] �����ж�

					//newdepth = receiveBuff[2]*256 + receiveBuff[3];
					//���и�ֵ����										
						newdepth1.data[0]  = receiveBuff[2]; //buf[2] 
						newdepth2.data[0]  = receiveBuff[3]; //buf[3] 
									
					
					//�ٶȸ�ֵ����
					*p_newdepth1  = (int)newdepth1.d;
					*p_newdepth2  = (int)newdepth2.d;
					
//					//ctrlFlag
//					*p_crtlFlag = receiveBuff[7];                //buf[7]

					//���һ�����ݰ��Ľ��գ���ر������㣬�ȴ���һ�ֽ�����
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








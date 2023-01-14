/**
  *************************************************************************************************************************
  * @file    usart1.c
  * @author  @����ʶ
  * @version V1.0
  * @date    2022-10-08
  * @brief   ����1.c�ļ�����
  *************************************************************************************************************************/
	
#include "usart1.h"

/*���� -------------------------------------------------------------------------------------------------------------------*/
unsigned char table_data[5]; //������ǰ����һ�������Ž��յ�������
unsigned char table_cp[5];   //���Ƕ��ⶨ��һ�����飬�����յ������ݸ��Ƶ�������
unsigned short count=0;      //�������ݼ���
int newdepth;

/***
 * ������: Usart1_Init
 * ����:   Usart1��ʼ��
 * ����:   Bound��������
 * ���:   ��
 */
 
void Usart1_Init(u32 Bound)
{
   GPIO_InitTypeDef GPIO_InitStructure;
	 USART_InitTypeDef USART_InitStructure;
	 NVIC_InitTypeDef NVIC_InitStruct;
	//��������ʱ�Ӻ�GPIOʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_USART1); //GPIOB6����ΪUSART1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_USART1); //GPIOB7����ΪUSART1
	//���ڸ�λ
  USART_DeInit(USART1);	
	//USART3�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; //GPIOB6��GPIOB7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOB,&GPIO_InitStructure); //��ʼ��PB6��PB7
	
//USART����
	 USART_InitStructure.USART_BaudRate = Bound;                                     //����������
	 USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     //�ֳ�Ϊ8λ
	 USART_InitStructure.USART_StopBits = USART_StopBits_1;                          //һ��ֹͣλ
	 USART_InitStructure.USART_Parity = USART_Parity_No;                             //����żУ��λ
   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��Ӳ������������
	 USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;                    //�շ�ģʽ
//NVIC�ж�����
	 NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;                                  //ʹ��USART�ⲿ�ж�ͨ��
	 NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;                          //��ռ���ȼ�3
	 NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;                                 //�����ȼ�3
	 NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;                                    //ʹ���ⲿ�ж�ͨ��

	
//GPIO,USART,NVIC��ʼ��	
	 GPIO_Init(GPIOA, &GPIO_InitStructure);
	 USART_Init(USART1, &USART_InitStructure);
	 NVIC_Init(&NVIC_InitStruct);
	 
//�����ж�
  USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
//ʹ�ܴ���
  USART_Cmd(USART1, ENABLE);
}

/***
 * ������:
 * ����:
 * ����:
 * ���:
 */
//ʹ���Զ���Э�����ʮ����������



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
	if(table_cp[0]==0x55)//��������һ��ʮ������������0X2C�����
	{
		//��ʮ�������ݴ�ӡһ�½��յ�������
		//ԭʼ���ݣ�ʮ���������ݣ���55 AA 00 00 0D 0A
		//ǰ��λ�ǹ̶��ģ���7���͵�8��ʮ���������ݷֱ���CO2�ĸ߰�λ�͵Ͱ�λ
		for(i=0;i<5;i++)
		{
				printf(" %d \n",table_cp[i]);
		}
		
		printf("\r\n");//��һ���س�����
		//�Ѷ�Ӧ��ʮ����������ת��Ϊʮ��������
		num_H=hextoDec(table_cp[2]);//��8λ
		num_L=hextoDec(table_cp[3]);//��8λ
		printf("hh=%d LL=%d \n",num_H,num_L);
		newdepth=num_H*256+num_L;//ʹ��CO2Ũ�ȼ��㹫ʽ�������ֵ
		printf("newdepth=%d\n",newdepth);
	}
}

void USART1_IRQHandler(void)                 	//����1�жϷ������
{
	u8 Res,i;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�
	{
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������
		
		if(count==0)//����ǽ��յĵ�һ������
		{
			table_data[count]=Res;//����һ�����ݴ浽�����е�һԪ��
			if(table_data[0]==0x55)//�жϽ��յĵ�һ�������ǲ���ʮ������0X2C
			  count++;//�����һ��������0X2C���ʾ��ȷ����+1
		}
		else if(count==1)//��һ�����ݽ�����ȷ������£��жϵڶ�������
		{
			if(Res==0xAA)//����ս��յ�������0xE4���ʾ������ȷ
			{
				table_data[count]=Res;//�����ݴ��浽����ڶ���Ԫ��λ��
				count++;//�������ݼ���+1
			}
			else//����ڶ����ַ�����0XE4��������㣬���½���
				count=0;
		}
		else if(count==2&&Res==0)//���ǰ����������ȷ�����յĵ�����������0����������������½�������
		{ 
			count=0;
		}
		else if(count>1&&count<5)//���ǿ��Խ������ݵķ�Χ��ֻҪcount�����ݿɽ������ݷ�Χ�ڼ��ɽ��д�������
		{
			table_data[count]=Res;
			count++;
		}
		else if(count>=5)//����������ݳ��������С�����������½���
		{
			count=0;
		}		
   } 
	 
	//	memset(&table_cp, 0, sizeof(table_data));//��ʹ������table_cpʱ���
		for(i=0;i<5;i++)//�ѽ��յ������ݸ��Ƶ�table_cp������
		{
			 table_cp[i]= table_data[i];
	}
} 



/**
  *************************************************************************************************************************
  * @file    nvic.c
  * @author  @����ʶ
  * @version V1.0
  * @date    2022-11-07
  * @brief   NVIC�жϿ�����.c�ļ�����
  *************************************************************************************************************************
  * @attention
  *
  *
  *************************************************************************************************************************
  */

/* Includes -------------------------------------------------------------------------------------------------------------*/
#include	"nvic.h"
/* ���� -----------------------------------------------------------------------------------------------------------------*/

/**
 * ������:NVIC_Config  
 * ����:�ж����ȼ�����
 * ����:��
 * ���:��
 */
//void NVIC_Config(void)
//{
//	//�ж����ȼ�����
//	//NVIC_PriorityGroup_2:(2 bits for pre-emption priority and 2 bits for subpriority)
//	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	
//}

/*
	 NVIC_PriorityGroup_2                    
	 pre-emption priority    subpriority        
						0                  0                 
						0                  1      					  USART1     
						0                  2                  USART2   
						0                  3        				  
						1                  0      					  USART3
						1                  1      					     
						1                  2      					    
						1                  3       	        				 
						2                  0      
						2                  1      
						2                  2     
						2                  3                
						3                  0      
						3                  1                
						3                  2      					
						3                  3    
*/

/*****************************************************END OF FILE*********************************************************/	
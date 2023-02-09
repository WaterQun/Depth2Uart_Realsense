#include	"nvic.h"

/**
 * 函数名:NVIC_Config  
 * 描述:中断优先级分组
 * 输入:无
 * 输出:无
 */
//void NVIC_Config(void)
//{
//	//中断优先级分组
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

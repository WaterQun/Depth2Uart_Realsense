#ifndef __MBOTLINUXUSART__
#define __MBOTLINUXUSART__
#include <sys.h>	

#define START   0X11

/*定义 -------------------------------------------------------------------------------------------------------------------*/



/* 提供给其他C文件调用的函数 -----------------------------------------------------------------------------------------------*/

//从linux接收并解析数据
int usartReceiveOneData(int *p_newdepth1,int *p_newdepth2);

#endif

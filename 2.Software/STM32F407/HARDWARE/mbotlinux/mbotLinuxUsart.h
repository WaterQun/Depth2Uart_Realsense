#ifndef __MBOTLINUXUSART__
#define __MBOTLINUXUSART__

#include <sys.h>	

#define START   0X11

//��linux���ղ���������
int usartReceiveOneData(int *p_newdepth1,int *p_newdepth2);

#endif

/*************************************************************************
	> File Name: debug.h
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Fri 01 Oct 2021 12:40:31 PM CST
 ************************************************************************/

#ifdef DEBUG 
#define DBG(fmt, args...)  printf(fmt, ##args)
#else
#define DBG(fmt, args...)
#endif

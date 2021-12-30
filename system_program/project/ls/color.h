/*************************************************************************
	> File Name: color.h
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Fri 01 Oct 2021 12:52:08 PM CST
 ************************************************************************/

#ifndef _COLOR_H
#define _COLOR_H

#define COLOR(a, b)        "\033[" #a "m" b
#define COLOR_HL(a, b)   "\033[1;" #a "m" b 

#define RED(a)             COLOR(31, a)
#define GREEN(a)           COLOR(32, a)
#define YELLOW(a)          COLOR(33, a)
#define BLUE(a)            COLOR(34, a)
#define PURPLE(a)          COLOR(35, a)

#define RED_HL(a)        COLOR_HL(31, a)
#define GREEN_HL(a)      COLOR_HL(32, a)
#define YELLOW_HL(a)     COLOR_HL(33, a)
#define BLUE_HL(a)       COLOR_HL(34, a)
#define PURPLE_HL(a)     COLOR_HL(35, a)

#endif

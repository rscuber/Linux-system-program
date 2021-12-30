/*************************************************************************
	> File Name: color.h
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Wed 15 Sep 2021 11:50:10 PM CST
 ************************************************************************/

#ifndef _COLOR_H
#define _COLOR_H
#define COLOR(a, b)         "\033[0;" #b "m" a "\033[0m"
#define COLOR_HL(a, b)      "\033[0;1;" #b "m" a "\033[0m"
#define COLOR_HB(a, b)      "\033[0;2;" #b "m" a "\033[0m"
#define COLOR_BG(a, b)      "\033[0;" #b "m" a "\033[0m"
//hb: 一半亮度
//bg: 背景色

#define RED(a)       COLOR(a, 31)
#define GREEN(a)     COLOR(a, 32)
#define YELLOW(a)    COLOR(a, 33)
#define BLUE(a)      COLOR(a, 34)
#define PURPLE(a)    COLOR(a, 35)
#define CYAN(a)      COLOR(a, 36)

#define RED_HL(a)       COLOR_HL(a, 31)
#define GREEN_HL(a)     COLOR_HL(a, 32)
#define YELLOW_HL(a)    COLOR_HL(a, 33)
#define BLUE_HL(a)      COLOR_HL(a, 34)
#define PURPLE_HL(a)    COLOR_HL(a, 35)
#define CYAN_HL(a)      COLOR_HL(a, 36)

#define RED_HB(a)       COLOR_HB(a, 31)
#define GREEN_HB(a)     COLOR_HB(a, 32)
#define YELLOW_HB(a)    COLOR_HB(a, 33)
#define BLUE_HB(a)      COLOR_HB(a, 34)
#define PURPLE_HB(a)    COLOR_HB(a, 35)
#define CYAN_HB(a)      COLOR_HB(a, 36)

#define BLACK_BG(a)     COLOR_BG(a, 40)
#define RED_BG(a)       COLOR_BG(a, 41)
#define GREEN_BG(a)     COLOR_BG(a, 42)
#define YELLOW_BG(a)    COLOR_BG(a, 43)
#define BLUE_BG(a)      COLOR_BG(a, 44)
#define PURPLE_BG(a)    COLOR_BG(a, 45)
#define DGREEN_BG(a)    COLOR_BG(a, 46)
#define WHITE_BG(a)     COLOR_BG(a, 47)

#endif

/*************************************************************************
	> File Name: color.h
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Fri 01 Oct 2021 12:52:08 PM CST
 ************************************************************************/

#ifndef _COLOR_H
#define _COLOR_H

#define COLOR(a)        "\033[" #a "m"
#define BOLD_COLOR(a)   "\033[1;" #a "m"
#define NONE            "\033[0m"

#define RED             COLOR(31)
#define GREEN           COLOR(32)
#define YELLOW          COLOR(33)
#define BLUE            COLOR(34)
#define PURPLE          COLOR(35)

#define BOLD_RED        BOLD_COLOR(31)
#define BOLD_GREEN      BOLD_COLOR(32)
#define BOLD_YELLOW     BOLD_COLOR(33)
#define BOLD_BLUE       BOLD_COLOR(34)
#define BOLD_PURPLE     BOLD_COLOR(35)

#endif

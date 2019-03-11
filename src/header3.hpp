#include <fstream>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#ifndef header3_hpp_
#define header3_hpp_

#define WrongCLS 0b100
#define OutOfRangeGOTOXY 0b101
#define BadGetScreenSize 0b110
#define BadFGColor 0b111
#define BadBGColor 0b1000

int mt_clrscr(void);
int mt_gotoXY (int x, int y);
int mt_getscreensize(int *rows, int *cols);
/*
int mt_setfgcolor(enum colors);
int mt_setbgcolor(enum colors);
*/
int mt_clrscr(void)
{
	std::cout << "\E[H\E[2J";
}

int mt_gotoXY(int x, int y)
{
	//
}

int mt_getscreensize(int *rows, int *cols)
{
	//
}
/*
int mt_setfgcolor(enum colors)
{
	//
}

int mt_setbgcolor(enum colors)
{
	//
}
*/
#endif

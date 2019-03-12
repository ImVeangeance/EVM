#include <fstream>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <sys/ioctl.h>
#ifndef mt_header_hpp_
#define mt_header_hpp_

#define WrongCLS 0b100
#define OutOfRangeGOTOXY 0b101
#define BadGetScreenSize 0b110
#define BadFGColor 0b111
#define BadBGColor 0b1000

enum colors {RED = 88, BLUE = 33, GREEN = 22, WHITE = 255, PINK = 213, BLACK = 232};

int mt_clrscr(void);
int mt_gotoXY (int x, int y);
int mt_getscreensize(int *rows, int *cols);
int mt_setfgcolor(enum colors);
int mt_setbgcolor(enum colors);

int mt_clrscr(void)
{
	std::cout << "\E[H\E[2J";
	return 0;
}

int mt_gotoXY(int x, int y)
{
	std::cout << "\E[" << x << ";" << y << "H";
	return 0;
}

int mt_getscreensize(int &rows, int &cols)
{
	winsize jopa;
	if(ioctl(1, TIOCGWINSZ, &jopa))
		return 1;
	rows = jopa.ws_row;
	cols = jopa.ws_col;
	return 0;
}

int mt_setfgcolor(enum colors)
{
	std::cout << "\E[38;5;" << PINK << "m";
	return 0;
}

int mt_setbgcolor(enum colors)
{
	std::cout << "\E[48;5;" << GREEN << "m";
	return 0;
}
/*
	set_a_background=\E[4%p1%dm
	set_a_foreground=\E[3%p1%dm
*/

#endif

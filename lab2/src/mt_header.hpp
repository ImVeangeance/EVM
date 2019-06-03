#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/stat.h>
#ifndef mt_header_hpp_
#define mt_header_hpp_

enum colors {RED = 1, BLUE = 33,/*33, 20*/ PURPLE = 55, GREEN = 22, WHITE = 255, PINK = 207, BLACK = 16}; // tipo strucktura s 4vetami, kotorie est' v linuxe

int mt_clrscr(void);
int mt_gotoXY (int x, int y);
int mt_getscreensize(int *rows, int *cols);
int mt_setscreensize(int rows, int cols);
int mt_setfgcolor(enum colors);
int mt_setbgcolor(enum colors);
int mt_setscreensize(int rows, int cols);

int mt_clrscr(void) // o4istka ekrana
{
	std::cout << "\E[H\E[2J";
	return 0;
}

int mt_gotoXY(int x, int y) // perehod v opredelenii piksel'
{
	std::cout << "\E[" << x << ";" << y << "H";
	return 0;
}

int mt_getscreensize(int &rows, int &cols) // polu4at' razmer ekrana
{
	winsize jopa;
	if(ioctl(1, TIOCGWINSZ, &jopa))
		return 1;
	rows = jopa.ws_row;
	cols = jopa.ws_col;
	return 0;
}

int mt_setscreensize(int rows, int cols) // zadat' razmer ekrana
{
	std::cout << "\E[8;" << cols << ";" << rows << ";t";
	return 0;
}

int mt_setfgcolor(enum colors color) // menyaet cvet texta
{
	std::cout << "\E[38;5;" << color << "m";
	return 0;
}

int mt_setbgcolor(enum colors color) // menyaet obvodku
{
	std::cout << "\E[48;5;" << color << "m";
	return 0;
}

#endif

#include <iostream>
#include <cmath>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <fstream>
#include <iomanip>
#include "mt_header.hpp"
#include "sc_header.hpp"
#include "bc_header.hpp"

int adress, value = 111;

void printBig(void)
{
    int h[2] = {0};
	sc_memoryGet(adress, &value); // value = bigchar
	std::stringstream sstream;
    std::string str;
    sstream << std::setw(4) << std::setfill('0') << std::hex << (short)value  << std::dec;
	str = sstream.str();
	if(value >= 0)
		chooseBig(h, '+'), bc_printbigchar(h, 15, 3, BLUE, BLACK);
	else
		chooseBig(h, '0'), bc_printbigchar(h, 15, 3, BLUE, BLACK);
	chooseBig(h, str[0]);
	bc_printbigchar(h, 15, 11, BLUE, BLACK);
	chooseBig(h, str[1]);
	bc_printbigchar(h, 15, 19, BLUE, BLACK);
	chooseBig(h, str[2]);
	bc_printbigchar(h, 15, 27, BLUE, BLACK);
	chooseBig(h, str[3]);
	bc_printbigchar(h, 15, 35, BLUE, BLACK);
	mt_setbgcolor(BLACK);
	mt_setfgcolor(WHITE);
	mt_gotoXY(25, 400);
}

void ap(void)
{
    sc_memoryInit();
	sc_regInit();
	mt_clrscr();
	bc_boxPrint();
	sc_memoryPrint(adress);
	sc_regPrint();
	//mt_setbgcolor(RED);
	bc_framenamePrint();
	printBig();
	mt_gotoXY(26, 400);
}

int main(void)
{
	mt_setscreensize(96, 24);
    ap();
    sc_regPrint();
	
	mt_gotoXY(25, 1);
	std::cout << "\n";
	return 0;
}


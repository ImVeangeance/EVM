#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>
#include "sc_header.hpp"
#include "mt_header.hpp"

int main(void)
{
	mt_setscreensize(100, 20);
	int value;
	mt_clrscr();
	sc_memoryInit();
	mt_setfgcolor(GREEN);
	sc_memoryPrint();
	sc_memorySet(10, 100);
	sc_regGet(ErrorMemoryOut, &value);
	//
	sc_memorySave("memory.txt");
	return 0;
}

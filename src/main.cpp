#include "sc_header.hpp"
#include "mt_header.hpp"

int main(void)
{
	int value, rows = 50, cols = 60;
	sc_memoryInit();
	sc_regInit();
	mt_clrscr();
	mt_setfgcolor(PINK);
	mt_setbgcolor(GREEN);
	sc_memorySave("pojiloibinarnik");
	sc_memoryLoad("pojiloibinarnik");
	sc_memoryPrint(3, 3);
	mt_setbgcolor(PINK);
	mt_setfgcolor(BLUE);
	sc_regPrint(3, 80);
	//mt_gotoXY(100, 100);
	//mt_getscreensize(&rows, &cols);
	std::cout << std::endl;
	mt_gotoXY(999, 1);
	return 0;
}

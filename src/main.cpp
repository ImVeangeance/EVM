#include "sc_header.hpp"
#include "mt_header.hpp"
#include "bc_header.hpp"

int main(void)
{
	int value, rows = 50, cols = 60;
	mt_setscreensize(110, 30);
	sc_memoryInit();
	sc_regInit();
	mt_clrscr();
	//mt_setfgcolor(BLUE);
	//mt_setbgcolor(WHITE);
	sc_memorySave("pojiloibinarnik");
	sc_memoryLoad("pojiloibinarnik");
	bc_boxPrint();
	sc_memoryPrint(3, 3);
	sc_regPrint(12, 77);
	bc_framenamePrint();
	mt_gotoXY(27, 1);
	return 0;
}

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
	mt_setfgcolor(BLUE);
	mt_setbgcolor(RED);
	sc_memorySave("pojiloibinarnik");
	sc_memoryLoad("pojiloibinarnik");
	bc_box(2,3,60,11);
	bc_framenamePrint();
	sc_memoryPrint(3, 3);
	//mt_setbgcolor(BLUE);
	//mt_setfgcolor(WHITE);
	bc_box(16,85,19,4);
	sc_regPrint(17, 85);
	bc_framenamePrint();
	mt_gotoXY(27, 1);
	return 0;
}

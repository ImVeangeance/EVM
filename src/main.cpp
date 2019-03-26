#include "sc_header.hpp"
#include "mt_header.hpp"
 #include "bc_header.hpp"

int main(void)
{
	int value, rows = 50, cols = 60;
	int h = 1;
	mt_setscreensize(110, 30);
	sc_memoryInit();
	sc_regInit();
	sc_memorySet(49, 1488);
	mt_clrscr();
	//mt_setfgcolor(BLUE);
	//mt_setbgcolor(WHITE);
	sc_memorySave("pojiloibinarnik");
	sc_memoryLoad("pojiloibinarnik");
	bc_boxPrint();
	sc_memoryPrint(3, 3);
	sc_regPrint(12, 77);
	bc_framenamePrint();
	chooseBig(&h, '+');
	bc_printbigchar(&h, 15, 3, BLACK, WHITE);
	chooseBig(&h, '1');
	bc_printbigchar(&h, 15, 11, BLACK, WHITE);
	chooseBig(&h, '4');
	bc_printbigchar(&h, 15, 19, BLACK, WHITE);
	chooseBig(&h, '8');
	bc_printbigchar(&h, 15, 27, BLACK, WHITE);
	chooseBig(&h, '8');
	bc_printbigchar(&h, 15, 35, BLACK, WHITE);
	mt_gotoXY(27, 1);
	std::cout << "\n";
	return 0;
}

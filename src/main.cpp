#include "sc_header.hpp"
#include "mt_header.hpp"

int main(void)
{
	char act;
	int value, rows = 50, cols = 60;
	mt_setfgcolor(PINK);
	mt_setbgcolor(GREEN);
	sc_memoryInit();
	sc_regInit();
	//sc_memorySet(-1, 228);
	//sc_regGet(ErrorMemoryOut, &value);
	//std::cout << "Value - " << value << "\n";
	//sc_memorySave("pojiloibinarnik");
	//sc_memoryLoad("pojiloibinarnik");
	//std::cout.unsetf(std::ios::dec);
	//std::cout.setf(std::ios::hex);	
	//sc_memoryPrint();
	//std::cout.unsetf(std::ios::hex);
	//std::cout.setf(std::ios::dec);
	sc_regSet(ErrorMemoryOut, 0); // UNSET OF ERROR
	sc_memorySet(0, 1488);
	sc_regGet(ErrorMemoryOut, &value);
	std::cout << "Value - " << value << "\n";
	sc_memorySave("pojiloibinarnik");
	sc_memoryLoad("pojiloibinarnik");
	std::cout.unsetf(std::ios::dec);
	std::cout.setf(std::ios::hex);
	std::cout << std::endl << "CLS!";
	std::cin >> act;
	mt_clrscr();
	sc_memoryPrint();
	sc_regPrint(5, 100);
	std::cout.unsetf(std::ios::hex);
	std::cout.setf(std::ios::dec);
	//mt_gotoXY(100, 100);
	//mt_getscreensize(&rows, &cols);
	std::cout << std::endl;
	return 0;
}

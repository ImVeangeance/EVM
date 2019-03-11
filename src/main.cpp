#include "header.hpp"

int main(void)
{
	//sc_clear(); //4OT TAKOE
	int value;
	sc_memoryInit();
	sc_regInit();
	//
	sc_memorySet(-1, 228);
	sc_regGet(ErrorMemoryOut, &value);
	std::cout << "Value - " << value << "\n";
	sc_memorySave("pojiloibinarnik");
	sc_memoryLoad("pojiloibinarnik");
	std::cout.unsetf(std::ios::dec);
	std::cout.setf(std::ios::hex);	
	sc_memoryPrint();
	std::cout.unsetf(std::ios::hex);
	std::cout.setf(std::ios::dec);
	sc_regSet(ErrorMemoryOut, 0); // UNSET OF ERROR
	sc_memorySet(0, 1488);
	sc_regGet(ErrorMemoryOut, &value);
	std::cout << "Value - " << value << "\n";
	sc_memorySave("pojiloibinarnik");
	sc_memoryLoad("pojiloibinarnik");
	std::cout.unsetf(std::ios::dec);
	std::cout.setf(std::ios::hex);
	sc_memoryPrint();
	std::cout.unsetf(std::ios::hex);
	std::cout.setf(std::ios::dec);
	//BAN
	return 0;
}

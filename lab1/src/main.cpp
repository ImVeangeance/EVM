#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>
#include "sc_header.hpp"

int main(void)
{
	int value;
	sc_memoryInit();
	for(auto i = 0; i < 100; i++)
		std::cout << massive[i] << " ";
	//
	sc_memorySet(10, 100);
std::cout << "\n";
	for(auto i = 0; i < 100; i++)
		std::cout << massive[i] << " ";
	sc_regGet(ErrorMemoryOut, &value);
	//
	sc_memorySave("memory.txt");
	sc_memoryInit();
std::cout << "\n";
	for(auto i = 0; i < 100; i++)
		std::cout << massive[i] << " ";
	sc_memoryLoad("memory.txt");
std::cout << "\n";
	for(auto i = 0; i < 100; i++)
		std::cout << massive[i] << " ";
std::cout << "\n";
	//sc_commandDecode(0x10, 0xa, &value);
	//sc_commandEncode(value, 0x10, 0xa);
	return 0;
}

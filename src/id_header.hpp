#include <iostream>
#include "sc_header.hpp"
#include "mt_header.hpp"
#include "bc_header.hpp"
#include "rk_header.hpp"
#ifndef id_header_hpp_
#define id_header_hpp_

/* Space for pajilii functions */

int id_accumPrint(int x, int y);
int id_infoPrint(int x, int y);

int id_accumPrint(int x, int y)
{
	//
	return 0;
}

int id_infoPrint(void)
{
	mt_gotoXY(15,45);
	std::cout << "arrow key's - bypass the memory";
	mt_gotoXY(16,45);
	std::cout << "l - load";
	mt_gotoXY(17,45);
	std::cout << "s - save";
	mt_gotoXY(18,45);
	std::cout << "r - reset";
	mt_gotoXY(19,45);
	std::cout << "'+' - +5 to memory unit";
	mt_gotoXY(20,45);
	std::cout << "'-' -5 to memory unit";
	mt_gotoXY(21,45);
	std::cout << "q - quite";
	return 0;
}


#endif
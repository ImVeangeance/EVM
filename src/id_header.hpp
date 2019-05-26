#include <iostream>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include "sc_header.hpp"
#include "mt_header.hpp"
#include "bc_header.hpp"
#include "rk_header.hpp"
#ifndef id_header_hpp_
#define id_header_hpp_

/* Space for pajilii functions */

int id_accumPrint(int x, int y);
int id_infoPrint(int adress);
void printBig(void);
void ap(void);
void stopHandler(int);
void handlerRun(int);
void handlerRun(int);
void goOnce(void);
void runOnMemory(void);

int id_accumPrint(int x, int y)
{
	//
	return 0;
}

int id_infoPrint(int adress)
{
	int memo;
	//sc_memoryGet(adress, &memo);
	mt_gotoXY(6,76);
	std::cout << std::setw(3) << std::setfill('0') << adress+1;// << " - +" << std::setw(4) << std::setfill('0') << std::hex << memo << std::dec;
	//
	mt_gotoXY(15,45);
	std::cout << "arrow key's - bypass the memory";
	mt_gotoXY(16,45);
	std::cout << "'l' - load";
	mt_gotoXY(17,45);
	std::cout << "'s' - save";
	mt_gotoXY(18,45);
	std::cout << "'r' - reset";
	mt_gotoXY(19,45);
	std::cout << "'+' - +5 to memory unit";
	mt_gotoXY(20,45);
	std::cout << "'-' - -5 to memory unit";
	mt_gotoXY(21,45);
	std::cout << "'q' - quite";
	mt_gotoXY(22,45);
	std::cout << "'g' - run";
	std::cout << "\t't' - step";
	mt_gotoXY(12,70);
	mt_setfgcolor(GREEN);
	std::cout << "PlsDeleteMyLife";
	mt_setfgcolor(WHITE);
	mt_gotoXY(26, 400);
	return 0;
}

#endif

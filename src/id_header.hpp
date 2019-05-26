#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <fstream>
#include <iomanip>
#include <termios.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "mt_header.hpp"
#include "sc_header.hpp"
#include "bc_header.hpp"
#ifndef id_header_hpp_
#define id_header_hpp_

/* Space for pajilii functions */

int id_infoPrint(int adress);
void printBig(void);
void ap(void);
void stopHandler(int);
void handlerRun(int);
void handlerRun(int);
void goOnce(void);
void runOnMemory(void);


int id_infoPrint(int adress)
{
	int memo, command, operand;
	sc_memoryGet(adress, &memo);
	mt_gotoXY(3, 76);
	std::cout.unsetf(std::ios::dec);
	std::cout.setf(std::ios::hex);	
	if (accumulator < 0)
		std::cout << std::setw(3) << std::setfill('0') << (short)-memo;
	else
		std::cout << "+" << std::setw(3) << std::setfill('0') << (short)memo;
	std::cout.unsetf(std::ios::hex);
	std::cout.setf(std::ios::dec);	
	mt_gotoXY(9, 73);
	std::cout.unsetf(std::ios::hex);
	std::cout.setf(std::ios::dec);
	if (sc_commandDecode(memo, &command, &operand))
		std::cout << "+00 : 00";
	else
		std::cout << "+" << std::setw(3) << std::setfill('0') 
		<< std::hex << command <<  " : " << std::setw(3) << 
		std::setfill('0') << operand;
	//sc_memoryGet(adress, &memo);
	std::cout.unsetf(std::ios::hex);
	std::cout.setf(std::ios::dec);
	mt_gotoXY(6,76);
	std::cout << std::setw(3) << std::setfill('0') << adress+1;
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

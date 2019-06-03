#include <iostream>
#include <cmath>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <fstream>
#include <iomanip>
#include <termios.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/time.h> // ETA BIBLIOTEKA
#include <fcntl.h>
#include <sys/stat.h>
#include "mt_header.hpp"
#include "sc_header.hpp"
#include "bc_header.hpp"
#include "rk_header.hpp"
#include "id_header.hpp"

int adress = 0, value = 0, instructionCounter= 0;
////////////////////////////////////////////////////////////////////////////////////////////////
void printBig(void)
{
    int h[2] = {0};
	sc_memoryGet(adress, &value);
	std::stringstream sstream;
    std::string str;
    sstream << std::setw(4) << std::setfill('0') << std::hex << (short)value  << std::dec;
	str = sstream.str();
	if(value >= 0)
		chooseBig(h, '+'), bc_printbigchar(h, 15, 3, BLUE, BLACK);
	else
		chooseBig(h, '0'), bc_printbigchar(h, 15, 3, BLUE, BLACK);
	chooseBig(h, str[0]);
	bc_printbigchar(h, 15, 11, BLUE, BLACK);
	chooseBig(h, str[1]);
	bc_printbigchar(h, 15, 19, BLUE, BLACK);
	chooseBig(h, str[2]);
	bc_printbigchar(h, 15, 27, BLUE, BLACK);
	chooseBig(h, str[3]);
	bc_printbigchar(h, 15, 35, BLUE, BLACK);
	mt_setbgcolor(BLACK);
	mt_setfgcolor(WHITE);
	mt_gotoXY(25, 400);
}

void ap(void)
{
    sc_regSet(ErrorTimer, 0);
    sc_memoryInit();
	sc_regInit();
	mt_clrscr();
	bc_boxPrint();
	sc_memoryPrint(adress);
	sc_regPrint();
	//mt_setbgcolor(RED);
	bc_framenamePrint();
	printBig();
	id_infoPrint(adress);
	mt_gotoXY(26, 400);
}

int main(void)
{
    keys key;
    bool move = true;
	mt_setscreensize(96, 24);
    ap();
    sc_regPrint();
	while (key != key_q)
	{
		rk_readkey(&key);
        switch(key)
		{
			case key_load:
			{
			    sc_memoryLoad("data.txt");
				id_infoPrint(adress);
				sc_memoryPrint(adress);
				printBig();
				sc_regPrint();
				mt_gotoXY(26, 400);
			}
				break;
			case key_save:
			{
			    sc_memorySave("data.txt");
				id_infoPrint(adress);
				printBig();
				sc_regPrint();
				mt_gotoXY(26, 400);
			}
				break;
			case key_reset:
			{
			    ap();
			    adress = 0;
			    id_infoPrint(adress);
			    sc_regGet(ErrorTimer, &value);
			    sc_memoryPrint(adress);
			    sc_regPrint();
			    mt_gotoXY(26, 1);
			    move = true;
				sc_regSet(ErrorTimer, 0);
				sc_regPrint();
				sc_memoryPrint(adress);
				printBig();
				mt_gotoXY(26, 400);
			}
				break;
			case key_up:
			{
			    if(adress > 9  and move == true)
			        adress -= 10;
			    id_infoPrint(adress);
			    sc_memoryPrint(adress);
			    sc_regPrint();
			    printBig();
			    mt_gotoXY(26, 400);
			}
				break;
			case key_down:
			{
			    if(adress <= 89 and adress > -1 and move == true)
			        adress += 10, sc_regGet(ErrorTimer, &value);
			    id_infoPrint(adress);
			    sc_memoryPrint(adress);
			    sc_regPrint();
			    printBig();
			    mt_gotoXY(26, 400);
			}
				break;
			case key_right:
			{
			    if(adress < 99  and move == true)
			        adress++, sc_regGet(ErrorTimer, &value);
			    id_infoPrint(adress);
			    sc_memoryPrint(adress);
			    sc_regPrint();
			    printBig();
			    mt_gotoXY(26, 400);
			}
				break;
			case key_left:
			{
			    if(adress > 0  and move == true)
			        adress--, sc_regGet(ErrorTimer, &value);
			    id_infoPrint(adress);
			    sc_memoryPrint(adress);
			    sc_regPrint();
			    printBig();
			    mt_gotoXY(26, 400);
			}
				break;
			case key_plus:
			{
			    if(adress > -1 and adress < 100 and move == true)
			        value += 5;
			    //if dlya 'V'
			    //mt_clrscr();
			    //bc_boxPrint();
			    //bc_framenamePrint();
			    id_infoPrint(adress);
			    sc_memorySet(adress, value);
			    id_infoPrint(adress);
			    sc_regPrint();
			    sc_memoryPrint(adress);
			    printBig();
			    mt_gotoXY(26, 400);
			}
				break;
			case key_minus:
			{

			    if(value > 0 and (adress > -1 and adress < 100) and move == true)
				value -= 5;
			    //mt_clrscr();
			    //bc_boxPrint();
			    //bc_framenamePrint();
			    sc_regPrint();
			    sc_memorySet(adress, value);
			    id_infoPrint(adress);
			    sc_memoryPrint(adress);
			    printBig();
			    mt_gotoXY(26, 400);
			}
			    break;
			case key_run: // EDET 4EREZ VES' MASSIV
			{
			    mt_gotoXY(26, 400);
			}
				break;
			case key_step: // EDET 1 RAZ
            		{
                		mt_gotoXY(26, 400);
            		}		
			    break;
			case key_f5:
			{
                		instructionCounter = adress;
	          		id_infoPrint(adress);
	          		mt_gotoXY(26, 400);
	          		fflush(stdout);
			}
			    break;
			case key_f4:
			{
                		sc_memoryGet(adress, &accumulator);
				id_infoPrint(adress);
	           		mt_gotoXY(26, 400);
	           		fflush(stdout);
			}
			    break;
			case key_f6: // 2 I 3 FUNCCII OSTANAVLIVAUT PROGU
			{
			    	mt_gotoXY(26, 400);
			}
				break;
			default:
			{
			    //
			}
				break;
		}
	}
	mt_gotoXY(25, 1);
	std::cout << "\n";
	return 0;
}


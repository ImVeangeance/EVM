#include "ass.hpp"
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
#include <sys/time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "mt_header.hpp"
#include "sc_header.hpp"
#include "bc_header.hpp"
#include "rk_header.hpp"
#include "id_header.hpp"

struct itimerval newTime, oldTime;

int adress = 0, value = 0;

void stopHandler(int signaly)
{
    newTime.it_interval.tv_sec = 0;
    newTime.it_interval.tv_usec = 0;
    newTime.it_value.tv_sec = 0;
    newTime.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &newTime, &oldTime);
}

void handlerRun(int signaly)
{
    int value;
    sc_regGet(ErrorTimer, &value);
    if((value == 0) & (adress + 1 < 100))
    {
        adress++;	
	sc_memoryPrint(adress);
        printBig();
        id_infoPrint(adress);
        sc_regPrint();
    }
    else
    {
        signal(SIGALRM, handlerRun);
        newTime.it_interval.tv_sec = 0;
        newTime.it_interval.tv_usec = 0;
        newTime.it_value.tv_sec = 0;
        newTime.it_value.tv_usec = 0;
        setitimer(ITIMER_REAL, &newTime, &oldTime);
        sc_regSet(ErrorTimer, 1);
        sc_memoryPrint(adress);
        printBig();
        sc_regPrint();
    }
}

void handlerOnce(int signaly)
{
    int value;
    sc_regGet(ErrorTimer, &value);
    if((value == 0) & (adress + 1 < 100))
    {
        mt_clrscr();
        adress++;
        signal(SIGALRM, handlerOnce);
        newTime.it_interval.tv_sec = 0;
        newTime.it_interval.tv_usec = 0;
        newTime.it_value.tv_sec = 0;
        newTime.it_value.tv_usec = 0;
        setitimer(ITIMER_REAL, &newTime, &oldTime);
        sc_regSet(ErrorTimer, 0);
        mt_clrscr();
        bc_boxPrint();
        bc_framenamePrint();
        printBig();
        sc_regPrint();
        sc_memoryPrint(adress);
        id_infoPrint(adress);
        mt_gotoXY(26, 400);
    }
}

void goOnce()
{
    signal(SIGALRM, handlerOnce);
    newTime.it_interval.tv_sec = 0;
    newTime.it_interval.tv_usec = 0;
    newTime.it_value.tv_sec = 1;
    newTime.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &newTime, &oldTime);
}

void runOnMemory()
{
    signal(SIGALRM, handlerRun);
    newTime.it_interval.tv_sec = 1;
    newTime.it_interval.tv_usec = 0;
    id_infoPrint(adress);
    newTime.it_value.tv_sec = 1;
    newTime.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &newTime, &oldTime);

}

void printBig(void)
{
    int h[2] = {0};
	sc_memoryGet(adress, &value);
	std::stringstream sstream;
    std::string str;
    sstream << std::setw(4) << std::setfill('0') << std::hex << value  << std::dec;
	str = sstream.str();
	chooseBig(h, '+');
	bc_printbigchar(h, 15, 3, BLUE, BLACK);
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
    setbuf(stdout, NULL);
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
				signal(SIGUSR1, stopHandler);
				raise(SIGUSR1);
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
			    sc_memorySet(adress, value);
			    id_infoPrint(adress);
			    sc_memoryPrint(adress);
			    printBig();
			    mt_gotoXY(26, 400);
			}
			    break;
			case key_run:
			{
			    move = false;
				sc_regSet(ErrorTimer, 0);
				mt_clrscr();
				bc_boxPrint();
				bc_framenamePrint();
				sc_regPrint();
				sc_memoryPrint(adress);
				printBig();
				sc_regPrint();
				id_infoPrint(adress);
				runOnMemory();
				sc_regPrint();
			    mt_gotoXY(26, 400);
			}
				break;
			case key_step:
            		{
                		move = false;
				sc_regSet(ErrorTimer, 0);
				mt_clrscr();
				sc_memoryPrint(adress);
				bc_boxPrint();
				bc_framenamePrint();
				printBig();
                		id_infoPrint(adress);
               			 sc_regSet(ErrorTimer, 1);
               			 sc_regPrint();
               			 sc_regSet(ErrorTimer, 0);
               			 goOnce();
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
			case key_f6:
			{
			    	move = false;
				signal(SIGUSR1, stopHandler);
				raise(SIGUSR1);
				id_infoPrint(adress);
				sc_regSet(ErrorTimer, 1);
				sc_regPrint();
				sc_memoryPrint(adress);
				printBig();
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


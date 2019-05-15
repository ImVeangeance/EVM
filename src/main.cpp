#include <iostream>
#include <string>
#include "sc_header.hpp"
#include "mt_header.hpp"
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
    sc_regGet(IGNORE_TIMER, &value);
    if((value == 0) & (adress + 1 < 100))
    {
        adress++;
	sc_memoryPrint(adress);
        printBig();
        sc_regPrint(12, 77);
    }
    else
    {
        signal(SIGALRM, handlerRun);
        newTime.it_interval.tv_sec = 0;
        newTime.it_interval.tv_usec = 0;
        newTime.it_value.tv_sec = 0;
        newTime.it_value.tv_usec = 0;
        setitimer(ITIMER_REAL, &newTime, &oldTime);
        sc_regSet(IGNORE_TIMER, 1);
        sc_memoryPrint(adress);
        printBig();
        sc_regPrint(12, 77);
    }
}

void handlerOnce(int signaly)
{
    int value;
    sc_regGet(IGNORE_TIMER, &value);
    if((value == 0) & (adress + 1 < 100))
    {
        adress++;
        sc_memoryPrint(adress);
        printBig();
        sc_regPrint(12, 77);
        signal(SIGALRM, handlerOnce);
        newTime.it_interval.tv_sec = 0;
        newTime.it_interval.tv_usec = 0;
        newTime.it_value.tv_sec = 0;
        newTime.it_value.tv_usec = 0;
        setitimer(ITIMER_REAL, &newTime, &oldTime);
        sc_regSet(IGNORE_TIMER, 1);
        sc_memoryPrint(adress);
        printBig();
        sc_regPrint(12, 77);
    }
}

void goOnce()
{signal(SIGALRM, handlerOnce);
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
	bc_printbigchar(h, 15, 3, BLACK, BLUE);
	chooseBig(h, str[0]);
	bc_printbigchar(h, 15, 11, BLACK, BLUE);
	chooseBig(h, str[1]);
	bc_printbigchar(h, 15, 19, BLACK, BLUE);
	chooseBig(h, str[2]);
	bc_printbigchar(h, 15, 27, BLACK, BLUE);
	chooseBig(h, str[3]);
	bc_printbigchar(h, 15, 35, BLACK, BLUE);
	mt_setbgcolor(BLACK);
	mt_setfgcolor(WHITE);
	mt_gotoXY(25, 1);
}

void ap(void)
{
    setbuf(stdout, NULL);
    sc_regSet(IGNORE_TIMER, 1);
    sc_memoryInit();
	sc_regInit();
	mt_clrscr();
	bc_boxPrint();
	sc_memoryPrint(adress);
	sc_regPrint(12, 77);
	//mt_setbgcolor(RED);
	bc_framenamePrint();
	printBig();
	id_infoPrint();
	mt_gotoXY(26, 1);
}

int main(void)
{
    keys key;
	mt_setscreensize(110, 30);
    ap();
	while (key != key_q)
	{
		rk_readkey(&key);
        switch (key)
		{
			case key_load:
			{
			    sc_memoryLoad("data.txt");
				sc_memoryPrint(adress);
				printBig();
				sc_regPrint(12, 77);
				mt_gotoXY(26, 1);
			}
				break;
			case key_save:
			{
			    sc_memorySave("data.txt");
				printBig();
				sc_regPrint(12, 77);
				mt_gotoXY(26, 1);
			}
				break;
			case key_reset:
			{
			    ap();
			    adress = 0;
			    sc_regGet(IGNORE_TIMER, &value);
			    sc_memoryPrint(adress);
			    sc_regPrint(12, 77);
			    mt_gotoXY(26, 1);
			}
				break;
			case key_up:
			{
			    if(adress > 9)
			        adress -= 10;
			    sc_memoryPrint(adress);
			    sc_regPrint(12, 77);
			    printBig();
			    mt_gotoXY(26, 1);
			}
				break;
			case key_down:
			{
			    if(adress <= 89 and adress > -1)
			        adress += 10, sc_regGet(IGNORE_TIMER, &value);
			    sc_memoryPrint(adress);
			    sc_regPrint(12, 77);
			    printBig();
			    mt_gotoXY(26, 1);
			}
				break;
			case key_right:
			{
			    if(adress < 99)
			        adress++, sc_regGet(IGNORE_TIMER, &value);
			    sc_memoryPrint(adress);
			    sc_regPrint(12, 77);
			    printBig();
			    mt_gotoXY(26, 1);
			}
				break;
			case key_left:
			{
			    if(adress > 0)
			        adress--, sc_regGet(IGNORE_TIMER, &value);
			    sc_memoryPrint(adress);
			    sc_regPrint(12, 77);
			    printBig();
			    mt_gotoXY(26, 1);
			}
				break;
			case key_plus:
			{
			    if(adress > -1 and adress < 100)
			        value += 5;
			    sc_memorySet(adress, value);
			    sc_regPrint(12, 77);
			    sc_memoryPrint(adress);
			    printBig();
			    mt_gotoXY(26, 1);
			}
				break;
			case key_minus:
			{

			    if(value > 0 and (adress > -1 and adress < 100))
			        value -= 5;
			    sc_memorySet(adress, value);
			    sc_memoryPrint(adress);
			    printBig();
			    mt_gotoXY(26, 1);
			}
			case key_run:
			{
				sc_regSet(IGNORE_TIMER, 0);
				mt_clrscr();
				bc_boxPrint();
				id_infoPrint();
				bc_framenamePrint();
				sc_regPrint(12, 77);
				sc_memoryPrint(adress);
				printBig();
				sc_regPrint(12, 77);
				runOnMemory();
				sc_regPrint(12, 77);
			    mt_gotoXY(26, 1);
			}
				break;
			case key_step:

				sc_regSet(IGNORE_TIMER, 0);
				mt_clrscr();
				bc_boxPrint();
				id_infoPrint();
				bc_framenamePrint();
				mt_gotoXY(26, 1);
				sc_memoryPrint(adress);
				printBig();
				goOnce();
                sc_regPrint(12, 77);
                mt_gotoXY(26, 1);

				break;
			case key_f6:
			{
				sc_regSet(IGNORE_TIMER, 1);
				signal(SIGUSR1, stopHandler);
				raise(SIGUSR1);
				sc_regPrint(12, 77);
				sc_memoryPrint(adress);
				printBig();
				mt_gotoXY(26, 1);
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


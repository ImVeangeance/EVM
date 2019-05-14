#include <iostream>
#include <string>
#include "sc_header.hpp"
#include "mt_header.hpp"
#include "bc_header.hpp"
#include "rk_header.hpp"
#include "id_header.hpp"

int adress = -1, value = 0;

void printBig(void)
{
    int h[2] = {0};
	sc_memoryGet(adress, &value);
	std::stringstream sstream;
    std::string str;
    sstream << std::setw(4) << std::setfill('0') << std::hex << value  << std::dec;
	str = sstream.str();
	chooseBig(h, '+');
	bc_printbigchar(h, 15, 3, WHITE, PINK);
	chooseBig(h, str[0]);
	bc_printbigchar(h, 15, 11, WHITE, PINK);
	chooseBig(h, str[1]);
	bc_printbigchar(h, 15, 19, WHITE, PINK);
	chooseBig(h, str[2]);
	bc_printbigchar(h, 15, 27, WHITE, PINK);
	chooseBig(h, str[3]);
	bc_printbigchar(h, 15, 35, WHITE, PINK);
	mt_setbgcolor(BLACK);
	mt_setfgcolor(WHITE);
	mt_gotoXY(25, 1);
}

void ap(void)
{
    setbuf(stdout, NULL);
    sc_memoryInit();
	sc_regInit();
	mt_clrscr();
	bc_boxPrint();
	sc_memoryPrint(adress);
	sc_regPrint(12, 77);
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
			    adress = -1;
			    sc_memoryPrint(adress);
			    mt_gotoXY(26, 1);
			}
				break;
			case key_up:
			{
			    if(adress > 9)
			        adress -= 10;
			    sc_memoryPrint(adress);
			    printBig();
			    mt_gotoXY(26, 1);
			}
				break;
			case key_down:
			{
			    if(adress <= 89 and adress > -1)
			        adress += 10;
			    sc_memoryPrint(adress);
			    printBig();
			    mt_gotoXY(26, 1);
			}
				break;
			case key_right:
			{
			    if(adress < 99)
			        adress++;
			    sc_memoryPrint(adress);
			    printBig();
			    mt_gotoXY(26, 1);
			}
				break;
			case key_left:
			{
			    if(adress > 0)
			        adress--;
			    sc_memoryPrint(adress);
			    printBig();
			    mt_gotoXY(26, 1);
			}
				break;
			case key_plus:
			{
			    if(adress > -1 and adress < 100)
			        value += 5;
			    sc_memorySet(adress, value);
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


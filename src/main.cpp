#include <iostream>
#include <string>
#include "sc_header.hpp"
#include "mt_header.hpp"
#include "bc_header.hpp"
#include "rk_header.hpp"
#include "id_header.hpp"

void printBig(void)
{
    int value = 0, adress = 0, h = 1;
	sc_memoryGet(adress, &value);
	std::stringstream sstream;
    sstream << std::setw(4) << std::setfill('0') << std::hex << value  << std::dec;
	std::string str = sstream.str();
	chooseBig(&h, '+');
	bc_printbigchar(&h, 15, 3, WHITE, BLUE);
	chooseBig(&h, str[0]);
	bc_printbigchar(&h, 15, 11, WHITE, BLUE);
	chooseBig(&h, str[1]);
	bc_printbigchar(&h, 15, 19, WHITE, BLUE);
	chooseBig(&h, str[2]);
	bc_printbigchar(&h, 15, 27, WHITE, BLUE);
	chooseBig(&h, str[3]);
	bc_printbigchar(&h, 15, 35, WHITE, BLUE);
	mt_gotoXY(25, 1);
}

void ap(void)
{
    setbuf(stdout, NULL);
    sc_memoryInit();
	sc_regInit();
	mt_clrscr();
	bc_boxPrint();
	sc_memoryPrint(3, 3);
	sc_regPrint(12, 77);
	bc_framenamePrint();
	//pa_printAccumulator();
	//pa_printInstructionCounter();
	mt_gotoXY(25, 1);
}


int main(void)
{
    keys key;
	int rows = 50, cols = 60, h;
	mt_setscreensize(110, 30);
    ap();
	while (key != key_q)
	{
		rk_readkey(&key);
        switch (key)
		{
			case key_load:
			{
			    //
			}
				break;
			case key_save:
			{
			    sc_memorySave("data");
				sc_memoryPrint(3, 3);
				//printBig
				sc_regPrint(12, 77);
			}
				break;
			case key_reset:
			{
			    //
			}
				break;
			case key_tt:
			{
			    //
			}
				break;
			case key_i:
			{
			    //
			}
				break;
			case key_f5:
			{
			    //
			}
				break;
			case key_f6:
			{
			    //
			}
				break;
			case key_up:
			{
			    printBig();
			}
				break;
			case key_down:
			{
			    printBig();
			}
				break;
			case key_right:
			{
			    printBig();
			}
				break;
			case key_left:
			{
			    printBig();
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


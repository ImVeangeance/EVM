#include <iostream>
#include <string>
#include "sc_header.hpp"
#include "mt_header.hpp"
#include "bc_header.hpp"
#include "rk_header.hpp"
#include "id_header.hpp"

void printBig(void)
{
    int value, adress, h = 1;
	sc_memoryGet(adress, &value);
	std::stringstream sstream;
    sstream << std::setw(4) << std::setfill('0') << std::hex << value  << std::dec;
	std::string str = sstream.str();
	chooseBig(&h, '+');
	bc_printbigchar(&h, 2, 14, WHITE, GREEN);
	chooseBig(&h, str[0]);
	bc_printbigchar(&h, 11, 14, WHITE, GREEN);
	chooseBig(&h, str[1]);
	bc_printbigchar(&h, 20, 14, WHITE, GREEN);
	chooseBig(&h, str[2]);
	bc_printbigchar(&h, 29, 14, WHITE, GREEN);
	chooseBig(&h, str[3]);
	bc_printbigchar(&h, 38, 14, WHITE, GREEN);
	mt_gotoXY(1, 23);
}


int main(void)
{
    keys key;
	int rows = 50, cols = 60;
	mt_setscreensize(110, 30);
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
			case key_r:
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
			    //
			}
				break;
			case key_down:
			{
			    //
			}
				break;
			case key_right:
			{
			    //
			}
				break;
			case key_left:
			{
			    //
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


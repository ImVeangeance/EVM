#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <termios.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "mt_header.hpp"
#include "sc_header.hpp"
#ifndef bc_header_hpp_
#define bc_header_hpp_

void bc_framenamePrint(void);
int bc_printA (std::string str);
int bc_box(int x1, int y1, int x2, int y2);
void bc_boxPrint(void);
int bc_printbigchar(int a[2], int x, int y, enum colors, enum colors);
int bc_setbigcharpos (int *big, int x, int y, int value);
int bc_getbigcharpos(int *big, int x, int y, int *value);
int bc_bigcharwrite (int fd, int *big,int count);
int bc_bigcharread (int fd, int *big, int need_count, int *count);

void bc_framenamePrint(void) // Imena Ramok
{
	mt_setfgcolor(BLUE);
	//mt_gotoXY(11,66);
	//std::cout << " Author ";
	mt_gotoXY(2,3);
	std::cout << " Memory ";
	mt_gotoXY(2,66);
	std::cout << " Accumulator ";
	mt_gotoXY(5,66);
	std::cout << " Instruction Counter ";
	mt_gotoXY(8,66);
	std::cout << " Operation ";
	mt_gotoXY(3,92);
	std::cout << "F";
	mt_gotoXY(4,92);
	std::cout << "l";
	mt_gotoXY(5,92);
	std::cout << "a";
	mt_gotoXY(6,92);
	std::cout << "g";
	mt_gotoXY(7,92);
	std::cout << "s";
	mt_gotoXY(14,3);
	std::cout << " Number in zoom ";
	mt_gotoXY(14,45);
	std::cout << " Keys of action ";
	//mt_gotoXY(14,87);
	//std::cout << " Color ";
	mt_setfgcolor(BLACK);
}

int bc_printA (std::string str) // Perehod v escape posledovatel'nost'
{
	std::cout << "\E(0";
	std::cout << str;
	std::cout << "\E(B";
}

int bc_box(int x1, int y1, int x2, int y2) // Risovlaka ramok
{
	//mt_setbgcolor(PINK);
	mt_setfgcolor(BLUE);
	for(auto i = 0; i <= y2; i++) /* Left */
	{
		mt_gotoXY(x1 + i, y1 - 1);
		if(i == 0)
			bc_printA("l");
		if(i == y2)
			bc_printA("m");
		bc_printA("x");// Perehod v escape posledovatel'nost'
	}
	for(auto i = 1; i <= y2; i++) /* Right */
	{
		mt_gotoXY(x1 + i, y1 + x2);
		bc_printA("x");// Perehod v escape posledovatel'nost'
	}
	mt_gotoXY(x1, y1);
	for(auto i = 0; i <= x2; i++) /* Top */
	{
		if(i == x2)
			bc_printA("k");
		else
			bc_printA("r");
	}
	mt_gotoXY(x1 + y2 , y1);// Perehod v opredelennii piksel' v terminale
	for(auto i = 0; i <= x2; i++) /* Bottom */
	{
	//	std::cout << "\E(0``aaffggiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz{{||}}~~";
		if(i == x2)
			bc_printA("j");
		else
			bc_printA("r");
	}
	mt_setfgcolor(WHITE);
}

void bc_boxPrint(void) // Risovalka vseh ramok
{
	bc_box(2,3,60,11); // Memory
	bc_box(2,66,24,2); // Accumulator
	bc_box(5,66,24,2); // Coms
	bc_box(8,66,24,2); // Operand
	bc_box(2,93,3,12); // Flag
	bc_box(14,3,40,9); // Big char
	//bc_box(11,66,24,2);
	bc_box(14,45,39,9); // Action
	//bc_box(14,87,9,9);
}

int bc_printbigchar(int a[2], int x, int y, enum colors color1, enum colors color2) // bol'woe 4islo
{
	if (x < 0 || y < 0)
		return -1;

	char str[8] = { 0 };

	mt_setfgcolor(color1); // cvet texta
	mt_setbgcolor(color2); // cvet fona texta
	for (int i = 0; i < 2; i++)
	{
		int a_buf = a[i];
		for (int j = 0; j < 4; j++)
		{
			int buf;
			a_buf = a[i] >> (j * 8);
			buf = a_buf & 0xFF;
			for (int k = 0; k < 8; k++)
			{
				int buf_bit = (buf & (1 << k)) >> k;
				if (buf_bit != 0)
					str[k] = 'a';
				else
					str[k] = ' ';
			}
			mt_gotoXY(x + (i * 4) + j, y);
			bc_printA(str);
		}
	}
	//mt_gotoXY(18, 0);
	return 0;
}

int bc_setbigcharpos (int *big, int x, int y, int value)
{
	if (x < 0 || x > 7 || y < 0 || y > 7 || value > 1 || value < 0)
		return -1;
	int ind = 0;
	if (x > 3)
		ind = 1;
	if (value == 1)
		big[ind] |= 1 << (x * 8 + y);
	else if (value == 0)
		big[ind] &= ~(1 << (x * 8 + y));
	return 0;
}

int bc_getbigcharpos(int *big, int x, int y, int *value)
{
	if (x < 0 || x > 7 || y < 0 || y > 7)
		return -1;
	int ind = 0;
	if (x > 3)
		ind = 1;
	*value = ((big[ind] >> (x * 8)) >> y) & 1;
	return 0;
}

int bc_bigcharwrite (int fd, int *big,int count)
{
	int result;
	while (count > 0)
	{
		if ((result = write(fd, big, sizeof(int) * 2)) == -1)
			return -1;
		count--;
	}
	return 0;
}


int bc_bigcharread (int fd, int *big, int need_count, int *count)
{
	while (need_count > 0)
	{
		int result;
		if ((result = read(fd, big, sizeof(int) * 2)) == -1)
			return -1;
		need_count--;
		*count = *count + 1;
	}
	return 0;
}

void chooseBig(int *BIG, int value) // NEVAJNO
{
	switch (value)
	{
	case '+':
		BIG[0] = 1008205824;
            	BIG[1] = 6204;
            	break;
        case '0': //+
        	BIG[0] = 1382171196;
            	BIG[1] = 1010976330;
            	break;
        case '1': //+
            	BIG[0] = 134744072;
            	BIG[1] = 269488144;
            	break;
        case '2': //+
            	BIG[0] = 270549564;
            	BIG[1] = 2114061320;
            break;
        case '3': //+
            	BIG[0] = 270549564;
            	BIG[1] = 1010966544;
            break;
        case '4': //+
            	BIG[0] = 1213227072;
            	BIG[1] = 1077967940;
            	break;
        case '5': //+
            	BIG[0] = 201474620;
            	BIG[1] = 1010974768;
            	break;
        case '6': //+
            	BIG[0] = 33702968;
            	BIG[1] = 1010975330;
            	break;
        case '7': //+
           	BIG[0] = 135275646;
            	BIG[1] = 134749192;
            	break;
        case '8': //+
            	BIG[0] = 1312965180;
            	BIG[1] = 1010975346;
            	break;
        case '9': //+- !
            	BIG[0] = 1682063932;
            	BIG[1] = 1010974808;
            	break;
        case 'a': //
            	BIG[0] = 2118271614;
            	BIG[1] = 1111638594;
            	break;
        case 'b': //
            	BIG[0] = 2116166206;
            	BIG[1] = 2118271554;
            	break;
        case 'c': //
            	BIG[0] = 33686142;
            	BIG[1] = 2114060802;
            	break;
        case 'd': //
            	BIG[0] = 1145325182;
            	BIG[1] = 2118534212;
            	break;
        case 'e': //
            	BIG[0] = 2114060926;
            	BIG[1] = 2114060926;
            	break;
        case 'f': //
            	BIG[0] = 2114060926;
            	BIG[1] = 131586;
            	break;
        default:
            	BIG[0] = 0;
            	BIG[1] = 0;
		break;
	}
}

#endif

#include <iostream>
#include <string>
#include "sc_header.hpp"
#include "mt_header.hpp"
#ifndef bc_header_hpp_
#define bc_header_hpp_

void bc_framenamePrint(void);
int bc_printA (std::string str);
int bc_box(int x1, int y1, int x2, int y2);
void bc_boxPrint(void);
int bc_printbigchar(int [2], int x, int y, enum colors, enum colors);
int bc_setbigcharpos (int *big, int x, int y, int value);
int bc_getbigcharpos(int *big, int x, int y, int *value);
int bc_bigcharwrite (int fd, int *big,int count);
int bc_bigcharread (int fd, int *big, int need_count, int *count);

void bc_framenamePrint(void)
{
	mt_gotoXY(2,3);
	std::cout << " Memory ";
	mt_gotoXY(2,70);
	std::cout << " Accumulator ";
	mt_gotoXY(5,70);
	std::cout << " InstructionCounter ";
	mt_gotoXY(8,70);
	std::cout << " Operation ";
	mt_gotoXY(11,70);
	std::cout << " Flags ";
}

int bc_printA (std::string str)
{
	std::cout << "\E(0";
	std::cout << str;
	std::cout << "\E(B";
}

int bc_box(int x1, int y1, int x2, int y2)
{
	// ``aaffggiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz{{||}}~~
	for(auto i = 0; i <= y2; i++) /* Left */
	{
		mt_gotoXY(x1 + i, y1 - 1);
		if(i == 0)
			bc_printA("l");
		if(i == y2)
			bc_printA("m");
		bc_printA("x");
	}
	for(auto i = 1; i <= y2; i++) /* Right */
	{
		mt_gotoXY(x1 + i, y1 + x2);
		bc_printA("x");
	}
	mt_gotoXY(x1, y1);
	for(auto i = 0; i <= x2; i++) /* Top */
	{
		if(i == x2)
			bc_printA("k");
		else
			bc_printA("r");
	}
	mt_gotoXY(x1 + y2 , y1);
	for(auto i = 0; i <= x2; i++) /* Bottom */
	{
	//	std::cout << "\E(0``aaffggiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz{{||}}~~";
		if(i == x2)
			bc_printA("j");
		else
			bc_printA("r");
	}
}

void bc_boxPrint(void)
{
	bc_box(2,3,60,11);
	bc_box(2,70,24,2);
	bc_box(5,70,24,2);
	bc_box(8,70,24,2);
	bc_box(11,70,24,2);
}

int bc_printbigchar(int [2], int x, int y, enum colors, enum colors)
{
	//
}

int bc_setbigcharpos (int *big, int x, int y, int value)
{
	//
}

int bc_getbigcharpos(int *big, int x, int y, int *value)
{
	//
}

int bc_bigcharwrite (int fd, int *big,int count)
{
	//
}

int bc_bigcharread (int fd, int *big, int need_count, int *count)
{
	//
}







#endif
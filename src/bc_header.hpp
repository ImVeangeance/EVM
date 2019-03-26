#include <iostream>
#include <string>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "sc_header.hpp"
#include "mt_header.hpp"
#ifndef bc_header_hpp_
#define bc_header_hpp_

int bc0[2] = {1};
int bc1[2] = {1};

void bc_framenamePrint(void);
int bc_printA (std::string str);
int bc_box(int x1, int y1, int x2, int y2);
void bc_boxPrint(void);
int bc_printbigchar(int a[2], int x, int y, enum colors, enum colors);
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

int bc_printbigchar(int a[2], int x, int y, enum colors color1, enum colors color2)
{
	if (x < 0 || y < 0)
		return -1;

	char str[8] = { 0 };

	mt_setfgcolor(color1);
	mt_setbgcolor(color2);
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

void chooseBig(int *BIG, int value) {
	switch (value) {
	case '+':
		BIG[0] = -15198184;
            	BIG[1] = 404232447;
            	break;
        case '0':
        	BIG[0] = 1111638654;
            	BIG[1] = 2118271554;
            	break;
        case '1':
            	BIG[0] = 404430364;
            	BIG[1] = 404232216;
            	break;
        case '2':
            	BIG[0] = 1077953150;
            	BIG[1] = 2114060926;
            break;
        case '3':
            	BIG[0] = 2084586110;
            	BIG[1] = 2118271100;
            break;
        case '4':
            	BIG[0] = 2120640102;
            	BIG[1] = 1616928864;
            	break;
        case '5':
            	BIG[0] = 2114324094;
            	BIG[1] = 2120245344;
            	break;
        case '6':
            	BIG[0] = 101058174;
            	BIG[1] = 2118534782;
            	break;
        case '7':
           	BIG[0] = 2016423998;
            	BIG[1] = 808464504;
            	break;
        case '8':
            	BIG[0] = 2118271614;
            	BIG[1] = 2118271614;
            	break;
        case '9':
            	BIG[0] = 1111638654;
            	BIG[1] = 2120245374;
            	break;
        case 'A':
            	BIG[0] = 2118271614;
            	BIG[1] = 1111638594;
            	break;
        case 'B':
            	BIG[0] = 2116166206;
            	BIG[1] = 2118271554;
            	break;
        case 'C':
            	BIG[0] = 33686142;
            	BIG[1] = 2114060802;
            	break;
        case 'D':
            	BIG[0] = 1145325182;
            	BIG[1] = 2118534212;
            	break;
        case 'E':
            	BIG[0] = 2114060926;
            	BIG[1] = 2114060926;
            	break;
        case 'F':
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
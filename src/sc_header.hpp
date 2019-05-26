#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include "mt_header.hpp"
#ifndef sc_header_hpp_
#define sc_header_hpp_

#define ErrorMemoryOut 0b01 // M
#define ErrorInvalidReg 0b10 // R
#define ErrorWrongCom 0b11 // E
#define ErrorTimer 0b100 // T
#define ErrorDivisionZero 0b101 // O
#define ErrorInvalidValue 0b110 // P


int massive[100];

int registr;

int flag;

int sc_memoryInit(void);

int sc_memorySet(int adress, int value);

int sc_memoryGet(int adress, int *value);

int sc_memorySave(std::string filename);

int sc_memoryLoad(std::string filename);

int sc_memoryPrint(int x, int y);

int sc_regInit(void);

int sc_regSet(int registr, int value);

int sc_regGet(int registr, int *value);

int sc_regPrint(void);

int sc_commandEncode (int command, int operand, int *value);

int sc_commandDecode(int value, int *command, int *operand);

int sc_memoryInit(void)
{
	for(auto i = 0; i < 100; i++)
		massive[i] = 0;
	return 0;
}

int sc_memorySet(int adress, int value)
{
	if(adress > 99 || adress < 0)
	{
		sc_regSet(ErrorMemoryOut, 1);
	}
	else
	{
		massive[adress] = value;
	}
	return value;
}

int sc_memoryGet(int adress, int *value)
{
	if(adress > 99 || adress < 0)
	{
		sc_regSet(ErrorMemoryOut, 1);
	}
	else
	{
		*value = massive[adress];
		return *value;
	}
	return *value;
}

int sc_memorySave(std::string filename)
{
	std::ofstream file_open(filename, std::ios::binary);
	if(file_open.is_open())
	{
		for(auto i = 0; i < 100; i++)
		{
			file_open.write((char*) &massive, sizeof(massive));
		}
	}
	file_open.close();
	return 0;
}

int sc_memoryLoad(std::string filename)
{
	std::ifstream file_open(filename, std::ios::binary);
	file_open.read((char*)massive, sizeof(massive));
    	file_open.close();
    	return 0;
}

int sc_memoryPrint(int adress)
{
	for(auto i = 0; i < 10; i++)
	{
		mt_gotoXY(3 + i, 3);
		for(auto j = 0; j < 10; j++)
		{
			if((i * 10) + j == adress)
			{
				mt_setbgcolor(BLUE);
				mt_setfgcolor(BLACK);
			}
			std::cout.unsetf(std::ios::dec);
			std::cout.setf(std::ios::hex);
			std::cout << "+" << std::setw(4) << std::setfill('0') 
				  << massive[10 * i + j] << " ";
			std::cout.unsetf(std::ios::hex);
			std::cout.setf(std::ios::dec);
			mt_setbgcolor(BLACK);
			mt_setfgcolor(WHITE);
		}
	}
	mt_gotoXY(26, 400);
	return 0;
}

int sc_regInit(void)
{
	flag = 0;
	return 0;
}

int sc_regSet(int registr, int value)
{
	if (registr == ErrorMemoryOut || registr == ErrorWrongCom || registr == ErrorInvalidReg || registr == ErrorTimer || registr == ErrorDivisionZero
	|| registr == ErrorInvalidValue)
	{
		if (value == 0)
		{
			flag = flag & ~registr;
		}
		else if (value == 1)
		{
			flag = flag | registr;
		}
		else
		{
			return 1;
		}
	}
	return 0;
}

int sc_regGet(int registr, int *value)
{
	if (registr == ErrorMemoryOut || registr == ErrorWrongCom || registr == ErrorInvalidReg || registr == ErrorTimer || registr == ErrorDivisionZero
	|| registr == ErrorInvalidValue)
	{
		if ((flag & registr) != 0)
		{
			*value = 1;
		}
		else
		{
			*value = 0;
		}
	}
	return 0;
}

int sc_regPrint(void)
{
	int value;
	mt_gotoXY(3, 94);
	sc_regGet(ErrorMemoryOut, &value);
	if(value)
		mt_setfgcolor(RED);
	else
		mt_setfgcolor(GREEN);
	std::cout << "M";
	mt_setfgcolor(WHITE);
	mt_gotoXY(5, 94);
	sc_regGet(ErrorInvalidReg, &value);
	if(value)
		mt_setfgcolor(RED);
	else
		mt_setfgcolor(GREEN);
	std::cout << "R";
	mt_setfgcolor(WHITE);
	mt_gotoXY(7, 94);
	sc_regGet(ErrorWrongCom, &value);
	if(value)
		mt_setfgcolor(RED);
	else
		mt_setfgcolor(GREEN);
	std::cout << "W";
	mt_gotoXY(9, 94);
	sc_regGet(ErrorDivisionZero, &value);
	if(value)
		mt_setfgcolor(RED);
	else
		mt_setfgcolor(GREEN);
	std::cout << "0";
	mt_setfgcolor(WHITE);
	mt_gotoXY(11, 94);
	sc_regGet(ErrorInvalidReg, &value);
	if(value)
		mt_setfgcolor(RED);
	else
		mt_setfgcolor(GREEN);
	std::cout << "V";
	mt_setfgcolor(WHITE);
	mt_gotoXY(13, 94);
	sc_regGet(ErrorTimer, &value);
	if(value)
		mt_setfgcolor(RED);
	else
		mt_setfgcolor(GREEN);
	std::cout << "T";
	mt_setfgcolor(WHITE);

	mt_gotoXY(26, 400);
}

int sc_commandEncode(int command, int operand, int *value)
{
	if (command < 0x10
		|| (command > 0x11 && command < 0x20)
		|| (command > 0x21 && command < 0x30)
		|| (command > 0x33 && command < 0x40)
		|| (command > 0x43 && command < 0x51)
		|| command > 0x76)
	{
		sc_regSet(ErrorWrongCom, 1);
		return 1;
	}

	if (operand > 0x127 || operand < 0)
	{
		sc_regSet(ErrorInvalidReg, 1);
		return 1;
	}

	*value = (command << 7) | operand;

	return 0;
}


int sc_commandDecode(int value, int *command, int *operand)
{
	if ((value >> 14) != 0)
	{
		return 1;
	}
	*command = value >> 7;
	*operand = value & 0x7F;
	return 0;
}

#endif

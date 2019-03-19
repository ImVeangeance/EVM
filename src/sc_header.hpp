#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include "mt_header.hpp"
#ifndef sc_header_hpp_
#define sc_header_hpp_

#define ErrorMemoryOut 0b01
#define ErrorInvalidReg 0b10
#define ErrorWrongCom 0b11

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

int sc_regPrint(int x, int y);

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

int sc_memoryPrint(int x, int y)
{
	std::cout.unsetf(std::ios::dec);
	std::cout.setf(std::ios::hex);
	for(auto i = 0; i < 10; i++)
	{
			mt_gotoXY(x + i, y);
		for(auto j = 0; j < 10; j++)
		{
			std::cout.unsetf(std::ios::dec);
			std::cout.setf(std::ios::hex);
			std::cout << "+" << std::setw(4) << std::setfill('0') 
				  << massive[10 * i + j] << " ";
			std::cout.unsetf(std::ios::hex);
			std::cout.setf(std::ios::dec);
		}
		//std::cout << "\n";
	}
	//std::cout << "\n";
}

int sc_regInit(void)
{
	flag = 0;
	return 0;
}

int sc_regSet(int registr, int value)
{
	if (registr == ErrorMemoryOut || registr == ErrorWrongCom || registr == ErrorInvalidReg)
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
	if (registr == ErrorMemoryOut || registr == ErrorWrongCom || registr == ErrorInvalidReg)
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

int sc_regPrint(int x, int y)
{
	int value;
	mt_gotoXY(x, y);
	sc_regGet(ErrorMemoryOut, &value);
	std::cout << "ErrorMemoryOut" << " - " << value << "\n";
	mt_gotoXY(x + 1, y);
	sc_regGet(ErrorInvalidReg, &value);
	std::cout << "ErrorInvalidReg" << " - " << value << "\n";
	mt_gotoXY(x + 2, y);
	sc_regGet(ErrorWrongCom, &value);
	std::cout << "ErrorWrongCom" << " - " << value << "\n";
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

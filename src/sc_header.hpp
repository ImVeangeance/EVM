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
	mt_gotoXY(x, y + 2);
	sc_regGet(ErrorMemoryOut, &value);
	std::cout << value;
	mt_gotoXY(x , y + 4);
	sc_regGet(ErrorInvalidReg, &value);
	std::cout << value;
	mt_gotoXY(x , y + 6);
	sc_regGet(ErrorWrongCom, &value);
	std::cout << value;
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

/*

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

*/

#endif

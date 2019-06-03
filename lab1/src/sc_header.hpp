#include <iostream>
#include <termios.h>
#include <limits>
#include <unistd.h>
#include <fstream>
#include <iomanip>
#include <termios.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/stat.h>
#ifndef sc_header_hpp_
#define sc_header_hpp_

#define ErrorMemoryOut 0b01 // M // VIWEL ZA GRANICI MASSIVA [0;99]
#define ErrorInvalidReg 0b10 // R // REGISRT NEPRAVIL"NII
#define ErrorWrongCom 0b100 // E // NEPRAVIL'NAYA COMANDA
#define ErrorTimer 0b1000 // T // OSTANOVKA PROGRAMMI
#define ErrorDivisionZero 0b10000 // O // DELENIE NA 0
#define ErrorInvalidValue 0b100000 // P // Nepravil'noe zna4enie elementa > 32bit ili < 0


short int massive[100]; // PAMYAT'

int x;

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

int sc_memoryInit(void) // obnulenie massiva
{
	for(auto i = 0; i < 100; i++)
		massive[i] = 0; //= std::numeric_limits<int>::min(-65535);
	return 0;
}

int sc_memorySet(int adress, int value) // sohranyaet zna4enie VALUE v tekuwii element ADRESS
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

int sc_memoryGet(int adress, int *value) // polu4aet zna4enie ADRESS
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

int sc_memorySave(std::string filename) // sohranenie massiva v file
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

int sc_memoryLoad(std::string filename) // zagruzka massive iz faila
{
	std::ifstream file_open(filename, std::ios::binary);
	file_open.read((char*)massive, sizeof(massive));
    	file_open.close();
    	return 0;
}

int sc_regInit(void) // obyavlyaet flag
{
	flag = 0;
	return 0;
}

int sc_regSet(int registr, int value) // sohranyaet owibku
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

int sc_regGet(int registr, int *value) // polu4aet svedeniya, est' li owibka
{
	if (registr == ErrorMemoryOut || registr == ErrorWrongCom || registr == ErrorInvalidReg || registr == ErrorTimer || registr == ErrorDivisionZero
	|| registr == ErrorInvalidValue)
	{
		if ((flag & registr) != 0) // ternarnii operacii
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

int sc_commandEncode(int command, int operand, int *value) // codirovka comandi
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


int sc_commandDecode(int value, int *command, int *operand) // decodirovka
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

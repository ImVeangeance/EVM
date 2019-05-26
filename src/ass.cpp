#include "ass.hpp"

#define SIZE 100

int read_file(char *file_name)
{
	char *buf = NULL;
	size_t len = 0;

	FILE *in = fopen(file_name, "r");
	if(!in) {
		printf("No such file\n");
		return 1;
	}

	sc_memoryInit();

	while (getline(&buf, &len, in) != -1) {
		if (read_string(buf, len))
			return 1;
	}

	fclose(in);

	free(buf);

	return 0;
}

int read_string(char *str, int len)
{
	int value = 0;
	int ind;
	int command, operand;
	int lb = 0, rb = 0;
	char *buf = (char*) malloc(sizeof(buf) * len);
	search_space(str, buf, &lb, &rb, len);
	for (int i = lb; i < rb; i++)
	{
		if (!isdigit(str[i]))
			return 1;
	}
	ind = get_number(str, buf, lb, rb);
	skip_space(str, &lb, &rb, len);

	search_space(str, buf, &lb, &rb, len);
	for (int i = lb; i < rb; i++) {
		if (!isalpha(str[i]) && str[i] != '=')
			return 1;
	}
	if (!(command = get_command(str, buf, lb, rb)))
		return 1;
    skip_space(str, &lb, &rb, len);

    search_space(str, buf, &lb, &rb, len);
	for (int i = lb; i < rb; i++) {
		if (i == lb && str[i] == '+')
			continue;
		if (!isdigit(str[i]))
			return 1;
	}
	operand = get_number(str, buf, lb, rb);
	skip_space(str, &lb, &rb, len);

	if (command != 1)
	{
        sc_commandEncode(command, operand, &value);
	}
	else
	{
		value |= operand;
	}
	sc_memorySet(ind, value);
	free(buf);
	return 0;
}

int skip_space(char *str, int *lb, int *rb, int len)
{
	while ((str[*rb] == ' ' || str[*rb] == '\t') && *rb < len)
		(*rb)++;
	*lb = *rb;
	#if 0
	printf("Скип пробела: ");
	printf("%d-", *lb);
	printf("%d ", *rb);
	if (str[*rb] != '\n') {
		printf("%c\n", str[*rb]);
	} else {
		printf("\\n\n");
	}
	#endif
	return 0;
}

int search_space(char *str, char *buf, int *lb, int *rb, int len)
{
	while (str[*rb] != ' ' && str[*rb] != '\t' && str[*rb] != '\n' && *rb < len)
		(*rb)++;

	#if 0
	char tmp;
	printf("До пробела: ");
	printf("%d-", *lb);
	printf("%d\n", *rb);
	buf = strcpy(buf, str);
	tmp = buf[*rb];
	buf[*rb] = '\0';
	printf("%s\n", &buf[*lb]);
	buf[*rb] = tmp;
	#endif

	return 0;
}

int get_command(char *str, char *buf, int lb, int rb)
{
	buf = strcpy(buf, str);
	buf[rb] = '\0';

	if (!strcmp(&buf[lb], "READ"))
		return READ;
	if (!strcmp(&buf[lb], "WRITE"))
		return WRITE;
	if (!strcmp(&buf[lb], "LOAD"))
		return LOAD;
	if (!strcmp(&buf[lb], "STORE"))
		return STORE;
	if (!strcmp(&buf[lb], "ADD"))
		return ADD;
	if (!strcmp(&buf[lb], "SUB"))
		return SUB;
	if (!strcmp(&buf[lb], "DIVIDE"))
		return DIVIDE;
	if (!strcmp(&buf[lb], "MUL"))
		return MUL;
	if (!strcmp(&buf[lb], "JUMP"))
		return JUMP;
	if (!strcmp(&buf[lb], "JNEG"))
		return JNEG;
	if (!strcmp(&buf[lb], "JZ"))
		return JZ;
	if (!strcmp(&buf[lb], "HALT"))
		return HALT;
	if (!strcmp(&buf[lb], "="))
		return 1;

	return 0;
}

int get_number(char *str, char *buf, int lb, int rb)
{
	buf = strcpy(buf, str);
	buf[rb] = '\0';
	return atoi(&buf[lb]);
}

int CU(void)
{
	int value = 0;
	int command;
	int operand;
	sc_memoryGet(instructionCounter, &value);
	if (sc_commandDecode(value, &command, &operand))
	{
		sc_regSet(ErrorWrongCom, 1);
		sc_regSet(ErrorTimer, 1);
		return 1;
	}

	if (command >= 0x30 && command <= 0x33)
	{
		ALU(command, operand);
	}
	else
	{
		switch (command)
		{
			case READ:
			{
				mt_gotoXY(24, 14);
				for (int i = 0; i < 70; i++)
					printf(" ");
				mt_gotoXY(24, 15);
				scanf("%d", &value);
				sc_memorySet(operand, value);
				mt_gotoXY(24, 14);
				for (int i = 0; i < 70; i++)
					printf(" ");
			}
				break;
			case WRITE:
				mt_gotoXY(24, 14);
				for (int i = 0; i < 70; i++) {
					printf(" ");
				}

				sc_memoryGet(operand, &value);
				mt_gotoXY(24, 15);
				printf("%d\n", value);
				break;
			case LOAD:
				sc_memoryGet(operand, &accumulator);
				break;
			case STORE:
				sc_memorySet(operand, accumulator);
				break;
			case JUMP:
				if (operand >= SIZE || operand < 0) {
					sc_regSet(ErrorMemoryOut, 1);
					break;
				}
				instructionCounter = --operand;
				break;
			case JNEG:
				if (accumulator < 0) {
					if (operand >= SIZE || operand < 0)
					{
						sc_regSet(ErrorMemoryOut, 1);
						break;
					}
					instructionCounter = --operand;
				}
				break;
			case JZ:
				if (accumulator == 0) {
					if (operand >= SIZE || operand < 0) {
						sc_regSet(ErrorMemoryOut, 1);
						break;
					}
					instructionCounter = --operand;
				}
				break;
			case HALT:
				sc_regSet(ErrorTimer, 0);
				return 1;
				break;
			case JNP:
				if ((accumulator % 2) != 0) {
					if (operand >= SIZE || operand < 0) {
						sc_regSet(ErrorMemoryOut, 1);
						break;
					}
					instructionCounter = --operand;
				}
				break;
		}
	}

	if (instructionCounter + 1 < SIZE)
	{
		instructionCounter++;
	}
	else
	{
		sc_regSet(ErrorMemoryOut, 1);
	}

	return 0;
}

int ALU(int command, int operand)
{
	int value;
	sc_memoryGet(operand, &value);
	switch (command)
	{
		case ADD:
			if (accumulator + value > 0xFFFF){
				sc_regSet(ErrorInvalid, 1);
				break;
			}
			accumulator += value;
			break;
		case SUB:
			if (accumulator - value < -0xFFFE) {
				sc_regSet(ErrorInvalid, 1);
				break;
			}
			accumulator -= value;
			break;
		case DIVIDE:
			if (value == 0) {
				sc_regSet(ErrorDivisionZero, 1);
				break;
			}
			accumulator /= value;
			break;
		case MUL:
			if (accumulator * value > 0xFFFF) {
				sc_regSet(ErrorInvalid, 1);
				break;
			}
			accumulator *= value;
			break;
	}
	return 0;
}

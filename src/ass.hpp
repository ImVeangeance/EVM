#ifndef ass_hpp_
#define ass_hpp_

int accumulator;
int instructionCounter;

#define READ 0x10
#define WRITE 0x11

#define LOAD 0x20
#define STORE 0x21

#define ADD 0x30
#define SUB 0x31
#define DIVIDE 0x32
#define MUL 0x33

#define JUMP 0x40
#define JNEG 0x41
#define JZ 0x42
#define HALT 0x43

#define JNP 0x59

int CU(void);
int ALU(int command, int operand);
int read_file(char *file_name);
int read_string(char *buf, int len);
int skip_space(char *str, int *lb, int *rb, int len);
int search_space(char *str, char *buf, int *lb, int *rb, int len);
int get_command(char *str, char *buf, int lb, int rb);
int get_number(char *str, char *buf, int lb, int rb);

#endif

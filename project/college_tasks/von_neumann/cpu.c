/*************************************************************************
	> File Name: testcpu1.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Sat 10 Jul 2021 04:50:45 PM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define CMD_LEN 32
#define MEM_SIZE 32768
#define REG_LEN 2
#define CODE_GROUP 4
#define DATA_GROUP 2
#define OUT_LINES 16
#define CODE_LINE 8
#define DATA_LINE 16
#define EIGHTBYTE 256
typedef struct reg
{
	short genReg[9];//寄存器1到8
	short ir[2];//指令寄存器
	short ip;//程序计数器
	short flag;//标志寄存器
	short numReg;//立即数寄存器
}Register;
short* Init(Register* Reg);//主存初始化
void ReadCmdFile(short* memory);
short byte_to_short(char* s, int start);//把从start处后8位得字符串翻译成short型整数
void Getcmd(short* memory, Register* Reg);//取指令
short State_trans(short* memory, Register* Reg);
void Data_transfer(short* memory, Register* Reg);
void Arith_add(short* memory, Register* Reg);//加法
void Arith_sub(short* memory, Register* Reg);//减法
void Arith_multiply(short* memory, Register* Reg);//乘法
void Arith_div(short* memory, Register* Reg);//除法
void And_oper(short* memory, Register* Reg);//与
void Or_oper(short* memory, Register* Reg);
void Not_oper(short* memory, Register* Reg);
void Compare(short* memory, Register* Reg);
void Jump(short* memory, Register* Reg);
void Input(short* memory, Register* Reg);
void Output(short* memory, Register* Reg);
void PutReg(Register* Reg);
void Outmemory(short* memory);
int main()
{
	int stop = 0;
	Register Reg;//寄存器
	short* memory = Init(&Reg);//初始化内存和寄存器
	ReadCmdFile(memory);
	while (!stop)
	{
		Getcmd(memory, &Reg);
		stop = State_trans(memory, &Reg);
	}
	Outmemory(memory);
	free(memory);
	return 0;
}
short* Init(Register* Reg)
{
	int i = 0;
	short* p = (short*)malloc(sizeof(short) * MEM_SIZE);
	for (i = 0; i < MEM_SIZE; i++)
	{
		p[i] = 0;
	}
	Reg->flag = 0;
	for (i = 0; i < 9; i++)
	{
		Reg->genReg[i] = 0;
	}
	Reg->ip = 0;
	Reg->ir[0] = 0;
	Reg->ir[1] = 0;
	Reg->numReg = 0;
	return p;
}
short byte_to_short(char* s, int start)//把从start处后8位得字符串翻译成short型整数
{
	int i = 0, j = 7;
	short sum = 0;
	for (i = start; i < start + 8; i++)
	{
		sum += (s[i] - '0') * pow(2, j);
		j--;
	}
	return sum;
}
void ReadCmdFile(short* memory)
{
	FILE* fp = fopen("dict.dic", "r");
	char s[CMD_LEN + 1] = "";
	int i = 0;
	while (fscanf(fp, "%s", s))
	{
		if (feof(fp))
			break;
		memory[i++] = byte_to_short(s, 0);
		memory[i++] = byte_to_short(s, 8);
		memory[i++] = byte_to_short(s, 16);
		memory[i++] = byte_to_short(s, 24);
	}
}
void Getcmd(short* memory, Register* Reg)//取指令
{
	Reg->ir[0] = memory[Reg->ip];
	Reg->ir[1] = memory[Reg->ip + 1];
	if (memory[Reg->ip + 2] >= 128)//立即数有可能是负数
		Reg->numReg = (memory[Reg->ip + 2] - 256) * EIGHTBYTE + memory[Reg->ip + 3];
	else Reg->numReg = memory[Reg->ip + 2] * EIGHTBYTE + memory[Reg->ip + 3];
	Reg->ip += 4;
}
short State_trans(short* memory, Register* Reg)
{
	int type = Reg->ir[0];
	int stopflag = 0;
	switch (type)
	{
	case 0://停机
		stopflag = 1;
		break;
	case 1:
		Data_transfer(memory, Reg);
		break;
	case 2:
		Arith_add(memory, Reg);
		break;
	case 3:
		Arith_sub(memory, Reg);
		break;
	case 4:
		Arith_multiply(memory, Reg);
		break;
	case 5:
		Arith_div(memory, Reg);
		break;
	case 6:
		And_oper(memory, Reg);
		break;
	case 7:
		Or_oper(memory, Reg);
		break;
	case 8:
		Not_oper(memory, Reg);
		break;
	case 9:
		Compare(memory, Reg);
		break;
	case 10:
		Jump(memory, Reg);
		break;
	case 11:
		Input(memory, Reg);
		break;
	case 12:
		Output(memory, Reg);
		break;
	}
	PutReg(Reg);
	if (stopflag)
		return 1;
	else return 0;
}
void PutReg(Register* Reg)
{
	printf("ip = %hd\n", Reg->ip);
	printf("flag = %hd\n", Reg->flag);
	printf("ir = %hd\n", Reg->ir[0] * EIGHTBYTE + Reg->ir[1]);
	printf("ax1 = %hd ax2 = %hd ax3 = %hd ax4 = %hd\n", Reg->genReg[1], Reg->genReg[2], Reg->genReg[3], Reg->genReg[4]);
	printf("ax5 = %hd ax6 = %hd ax7 = %hd ax8 = %hd\n", Reg->genReg[5], Reg->genReg[6], Reg->genReg[7], Reg->genReg[8]);
}
void Outmemory(short* memory)
{
	int i, j, count = 0, sum;
	printf("\ncodeSegment :\n");
	for (i = 0; i < 16; i++)
	{
		for (j = 0; j < 8; j++)
		{
			sum = memory[count] * 16777216 + memory[count + 1] * 65536 + memory[count + 2] * 256 + memory[count + 3];
			printf("%d ", sum);
			count += 4;
		}
		printf("\n");
	}
	printf("\ndataSegment :\n");
	count = 16384;
	for (i = 0; i < 16; i++)
	{
		for (j = 0; j < 16; j++)
		{
			sum = memory[count] + memory[count + 1] * 256;//特别诡异的地方
			printf("%d ", sum);
			count += 2;
		}
		printf("\n");
	}
}
void Data_transfer(short* memory, Register* Reg)
{
	short Sreg = Reg->ir[1] % 16;
	short Dreg = Reg->ir[1] / 16;
	if (Sreg == 0)//立即数->R
	{
		Reg->genReg[Dreg] = Reg->numReg;
	}
	else if (Sreg >= 5 && Dreg <= 4)//M->R
	{
		Reg->genReg[Dreg] = memory[Reg->genReg[Sreg]];
	}
	else if (Sreg >= 5 && Dreg >= 5)//M->M
	{
		memory[Reg->genReg[Dreg]] = memory[Reg->genReg[Sreg]];
	}
	else if (Sreg <= 4 && Dreg >= 5)//R->M
	{
		memory[Reg->genReg[Dreg]] = Reg->genReg[Sreg];
	}
	else if (Sreg <= 4 && Dreg <= 4)//R->R
	{
		Reg->genReg[Dreg] = Reg->genReg[Sreg];
	}
}
void Arith_add(short* memory, Register* Reg)//加法
{
	short Sreg = Reg->ir[1] % 16;
	short Dreg = Reg->ir[1] / 16;
	if (Sreg == 0 && Dreg <= 4)//立即数->R
	{
		Reg->genReg[Dreg] += Reg->numReg;
	}
	else if (Sreg == 0 && Dreg >= 5)//立即数->M
	{
		memory[Reg->genReg[Dreg]] += Reg->numReg;
	}
	else if (Sreg >= 5 && Dreg <= 4)//M->R
	{
		Reg->genReg[Dreg] += memory[Reg->genReg[Sreg]];
	}
	else if (Sreg >= 5 && Dreg >= 5)
	{
		memory[Reg->genReg[Dreg]] += memory[Reg->genReg[Sreg]];
	}
	else if (Sreg <= 4 && Dreg >= 5)//R->M
	{
		memory[Reg->genReg[Dreg]] += Reg->genReg[Sreg];
	}
	else if (Sreg <= 4 && Dreg <= 4)//R->R
	{
		Reg->genReg[Dreg] += Reg->genReg[Sreg];
	}
}
void Arith_sub(short* memory, Register* Reg)//减法
{
	short Sreg = Reg->ir[1] % 16;
	short Dreg = Reg->ir[1] / 16;
	if (Sreg == 0 && Dreg <= 4)//立即数->R
	{
		Reg->genReg[Dreg] -= Reg->numReg;
	}
	else if (Sreg == 0 && Dreg >= 5)
	{
		memory[Reg->genReg[Dreg]] -= Reg->numReg;
	}
	else if (Sreg >= 5 && Dreg <= 4)//M->R
	{
		Reg->genReg[Dreg] -= memory[Reg->genReg[Sreg]];
	}
	else if (Sreg >= 5 && Dreg >= 5)//M->M
	{
		memory[Reg->genReg[Dreg]] -= memory[Reg->genReg[Sreg]];
	}
	else if (Sreg <= 4 && Dreg >= 5)//R->M
	{
		memory[Reg->genReg[Dreg]] -= Reg->genReg[Sreg];
	}
	else if (Sreg <= 4 && Dreg <= 4)//R->R
	{
		Reg->genReg[Dreg] -= Reg->genReg[Sreg];
	}
}
void Arith_multiply(short* memory, Register* Reg)//乘法
{
	short Sreg = Reg->ir[1] % 16;
	short Dreg = Reg->ir[1] / 16;
	if (Sreg == 0 && Dreg <= 4)//立即数->R
	{
		Reg->genReg[Dreg] *= Reg->numReg;
	}
	else if (Sreg == 0 && Dreg >= 5)
	{
		memory[Reg->genReg[Dreg]] *= Reg->numReg;
	}
	else if (Sreg >= 5 && Dreg <= 4)//M->R
	{
		Reg->genReg[Dreg] *= memory[Reg->genReg[Sreg]];
	}
	else if (Sreg >= 5 && Dreg >= 5)
	{
		memory[Reg->genReg[Dreg]] *= memory[Reg->genReg[Sreg]];
	}
	else if (Sreg <= 4 && Dreg >= 5)//R->M
	{
		memory[Reg->genReg[Dreg]] *= Reg->genReg[Sreg];
	}
	else if (Sreg <= 4 && Dreg <= 4)//R->R
	{
		Reg->genReg[Dreg] *= Reg->genReg[Sreg];
	}
}
void Arith_div(short* memory, Register* Reg)//除法
{
	short Sreg = Reg->ir[1] % 16;
	short Dreg = Reg->ir[1] / 16;
	if (Sreg == 0 && Dreg <= 4)//立即数->R
	{
		Reg->genReg[Dreg] /= Reg->numReg;
	}
	else if (Sreg == 0 && Dreg >= 5)
	{
		memory[Reg->genReg[Dreg]] /= Reg->numReg;
	}
	else if (Sreg >= 5 && Dreg <= 4)//M->R
	{
		Reg->genReg[Dreg] /= memory[Reg->genReg[Sreg]];
	}
	else if (Sreg >= 5 && Dreg >= 5)
	{
		memory[Reg->genReg[Dreg]] /= memory[Reg->genReg[Sreg]];
	}
	else if (Sreg <= 4 && Dreg >= 5)//R->M
	{
		memory[Reg->genReg[Dreg]] /= Reg->genReg[Sreg];
	}
	else if (Sreg <= 4 && Dreg <= 4)//R->R
	{
		Reg->genReg[Dreg] /= Reg->genReg[Sreg];
	}
}
void And_oper(short* memory, Register* Reg)//与
{
	short Sreg = Reg->ir[1] % 16;
	short Dreg = Reg->ir[1] / 16;
	if (Sreg == 0 && Dreg <= 4)//立即数 && R
	{
		if (Reg->genReg[Dreg] && Reg->numReg)
			Reg->genReg[Dreg] = 1;
		else Reg->genReg[Dreg] = 0;
	}
	else if (Sreg == 0 && Dreg >= 5)//立即数 && M
	{
		if (memory[Reg->genReg[Dreg] && Reg->numReg])
			memory[Reg->genReg[Dreg]] = 1;
		else memory[Reg->genReg[Dreg]] = 0;
	}
	else if (Sreg >= 5 && Dreg <= 4)//M && R
	{
		if (Reg->genReg[Dreg] && memory[Reg->genReg[Sreg]])
			Reg->genReg[Dreg] = 1;
		else Reg->genReg[Dreg] = 0;
	}
	else if (Sreg >= 5 && Dreg >= 5)//M && M
	{
		if (memory[Reg->genReg[Dreg]] && memory[Reg->genReg[Sreg]])
			memory[Reg->genReg[Dreg]] = 1;
		else memory[Reg->genReg[Dreg]] = 0;
	}
	else if (Sreg <= 4 && Dreg >= 5)
	{
		if (memory[Reg->genReg[Dreg]] && Reg->genReg[Sreg])
			memory[Reg->genReg[Dreg]] = 1;
		else memory[Reg->genReg[Dreg]] = 0;
	}
	else if (Sreg <= 4 && Dreg <= 4)//R && R
	{
		if (Reg->genReg[Dreg] && Reg->genReg[Sreg])
			Reg->genReg[Dreg] = 1;
		else Reg->genReg[Dreg] = 0;
	}
}
void Or_oper(short* memory, Register* Reg)
{
	short Sreg = Reg->ir[1] % 16;
	short Dreg = Reg->ir[1] / 16;
	if (Sreg == 0 && Dreg <= 4)//立即数 && R
	{
		if (Reg->genReg[Dreg] || Reg->numReg)
			Reg->genReg[Dreg] = 1;
		else Reg->genReg[Dreg] = 0;
	}
	else if (Sreg == 0 && Dreg >= 5)//立即数 && M
	{
		if (memory[Reg->genReg[Dreg] || Reg->numReg])
			memory[Reg->genReg[Dreg]] = 1;
		else memory[Reg->genReg[Dreg]] = 0;
	}
	else if (Sreg >= 5)//M && R
	{
		if (Reg->genReg[Dreg] || memory[Reg->genReg[Sreg]])
			Reg->genReg[Dreg] = 1;
		else Reg->genReg[Dreg] = 0;
	}
}
void Not_oper(short* memory, Register* Reg)
{
	short Sreg = Reg->ir[1] % 16;
	short Dreg = Reg->ir[1] / 16;
	if (Sreg == 0)//
	{
		if (!Reg->genReg[Dreg])
			Reg->genReg[Dreg] = 1;
		else Reg->genReg[Dreg] = 0;
	}
	else if (Sreg >= 5)
	{
		if (!memory[Reg->genReg[Sreg]])
			memory[Reg->genReg[Sreg]] = 1;
		else memory[Reg->genReg[Sreg]] = 0;
	}
}
void Compare(short* memory, Register* Reg)
{
	short Sreg = Reg->ir[1] % 16;
	short Dreg = Reg->ir[1] / 16;
	if (Sreg == 0 && Dreg <= 4)
	{
		if (Reg->genReg[Dreg] == Reg->numReg)
			Reg->flag = 0;
		else if (Reg->genReg[Dreg] > Reg->numReg)
			Reg->flag = 1;
		else if (Reg->genReg[Dreg] < Reg->numReg)
			Reg->flag = -1;
	}
	else if (Sreg == 0 && Dreg >= 5)
	{
		if (memory[Reg->genReg[Dreg]] == Reg->numReg)
			Reg->flag = 0;
		else if (memory[Reg->genReg[Dreg]] > Reg->numReg)
			Reg->flag = 1;
		else Reg->flag = -1;
	}
	else if (Sreg >= 5)
	{
		if (Reg->genReg[Dreg] == memory[Reg->genReg[Sreg]])
			Reg->flag = 0;
		else if (Reg->genReg[Dreg] > memory[Reg->genReg[Sreg]])
			Reg->flag = 1;
		else if (Reg->genReg[Dreg] < memory[Reg->genReg[Sreg]])
			Reg->flag = -1;
	}
	else if (Sreg <= 4)
	{
		if (Reg->genReg[Dreg] == Reg->genReg[Sreg])
			Reg->flag = 0;
		else if (Reg->genReg[Dreg] > Reg->genReg[Sreg])
			Reg->flag = 1;
		else  Reg->flag = -1;
	}
}
void Jump(short* memory, Register* Reg)
{
	int state = Reg->ir[1];
	if (state == 0)//无条件跳转
	{
		Reg->ip += Reg->numReg - 4;
	}
	else if (state == 1)
	{
		if (Reg->flag == 0)
			Reg->ip += Reg->numReg - 4;
	}
	else if (state == 2)
	{
		if (Reg->flag == 1)
			Reg->ip += Reg->numReg - 4;
	}
	else if (state == 3)
	{
		if (Reg->flag == -1)
			Reg->ip += Reg->numReg - 4;
	}
}
void Input(short* memory, Register* Reg)
{
	short Dreg = Reg->ir[1] / 16;
	printf("in:\n");
	if (Dreg <= 4)
		scanf("%hd", &Reg->genReg[Dreg]);
	else scanf("%hd", &memory[Reg->genReg[Dreg]]);
}
void Output(short* memory, Register* Reg)
{
	short Dreg = Reg->ir[1] / 16;
	printf("out: ");
	if (Dreg <= 4)
		printf("%hd\n", Reg->genReg[Dreg]);
	else printf("%hd\n", memory[Reg->genReg[Dreg]]);
}

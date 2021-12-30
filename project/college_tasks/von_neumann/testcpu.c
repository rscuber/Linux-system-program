/*************************************************************************
	> File Name: testcpu1.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Sat 10 Jul 2021 04:50:45 PM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define EIGHTBYTE 256 

typedef struct reg
{
	short greg[9];//寄存器1到8
	short ir[2];//指令寄存器
	short ip;//程序计数器
	short flag;//标志寄存器
	short nreg;//立即数寄存器
}Register;

void PutReg(Register*);
void Outmemory(short*);
short* Init(Register* );//主存初始化
void ReadCmdFile(short* );
short byte_to_short(char*, int);//把从start处后8位得字符串翻译成short型整数
void Getcmd(short* , Register*);//取指令
short s_trans(short*, Register* );
void Data_transfer(short*, Register* );
void Arith_add(short* memory, Register*);//加法
void Arith_multiply(short* , Register*);//乘法
void Arith_sub(short* memory, Register*);//减法
void Arith_div(short*, Register* );//除法
void Or_oper(short*, Register*);
void And_oper(short*, Register*);//与
void Not_oper(short*, Register*);
void Output(short*, Register*);
void Compare(short*, Register*);
void Jump(short*, Register*);
void Input(short*, Register*);

short* __init(Register* Reg) {
	Reg->ip = 0;
	Reg->ir[0] = 0;
	Reg->ir[1] = 0;
	Reg->nreg = 0;
}

short* Init(Register* Reg)
{
	int i = 0;
	short* p = (short*)malloc(sizeof(short) * 32768);
    memset(p, 0, sizeof(short) * 32768);
	Reg->flag = 0;
    memset(Reg->greg, 0, sizeof(short) * 9);
    __init(Reg);
	return p;
}

int calpow(int x, int n) {
    if (x == 0) return 0;
    if (n == 0) return 1;
    int ans  = 1;
    while (n--) {
        ans *= x;
    }
    return ans;
}

short byte_to_short(char* s, int start)//把从start处后8位得字符串翻译成short型整数
{
	short sum = 0;
	for (int i = start, j = 7; i < start + 8; i++)
	{
		sum += (s[i] - '0') * calpow(2, j);
		j--;
	}
	return sum;
}

void ReadCmdFile(short* memory)
{
	FILE* fp = fopen("dict.dic", "r");
    if (!fp) {
        return ;
    }
	char s[40] = {0};
	int i = 0;
	while (!feof(fp))
	{
        fgets(s, 33, fp);
		memory[i++] = byte_to_short(s, 0);
		memory[i++] = byte_to_short(s, 8);
		memory[i++] = byte_to_short(s, 16);
		memory[i++] = byte_to_short(s, 24);
	}
    return ;
}

void Getcmd(short* memory, Register* Reg)//取指令
{
	Reg->ir[0] = memory[Reg->ip];
	Reg->ir[1] = memory[Reg->ip + 1];
	if (memory[Reg->ip + 2] >= 128)//立即数有可能是负数
		Reg->nreg = (memory[Reg->ip + 2] - EIGHTBYTE) * EIGHTBYTE + memory[Reg->ip + 3];
	else Reg->nreg = memory[Reg->ip + 2] * EIGHTBYTE + memory[Reg->ip + 3];
	Reg->ip += 4;
    return ;
}

short s_trans(short* memory, Register* Reg)
{
	int type = Reg->ir[0];
	int endflag = 0;
	switch (type)
	{
	case 0://停机
		endflag = 1;
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
	if (endflag)
		return 1;
	else return 0;
}
void PutReg(Register* Reg)
{
	printf("ip = %hd\n", Reg->ip);
	printf("flag = %hd\n", Reg->flag);
	printf("ir = %hd\n", Reg->ir[0] * EIGHTBYTE + Reg->ir[1]);
	printf("ax1 = %hd ax2 = %hd ax3 = %hd ax4 = %hd\n", Reg->greg[1], Reg->greg[2], Reg->greg[3], Reg->greg[4]);
	printf("ax5 = %hd ax6 = %hd ax7 = %hd ax8 = %hd\n", Reg->greg[5], Reg->greg[6], Reg->greg[7], Reg->greg[8]);
}


void outcode(short *memory) {
    int i, j, count = 0, sum;
    	printf("\ncodeSegment :\n");
    	for (i = 0; i < 16; i++)
    	{
    		for (j = 0; j < 8; j++)
    		{
    			sum = memory[count] * 16777216 + memory[count + 1] * 65536 + memory[count + 2] * EIGHTBYTE + memory[count + 3];
    			printf("%d ", sum);
    			count += 4;
    		}
    		printf("\n");
        }	
    return ;
}

void outdata(short* memory)
{
    int sum;
	printf("\ndataSegment :\n");
	int count = 16384;
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			sum = memory[count] + memory[count + 1] * EIGHTBYTE;//特别诡异的地方
			printf("%d ", sum);
			count += 2;
		}
		printf("\n");
	}
    return ;
}

void Outmemory(short* memory)
{
    outcode(memory);
    outdata(memory);
}


void Data_transfer(short* memory, Register* Reg)
{
	short Sreg = Reg->ir[1] % 16;
	short Dreg = Reg->ir[1] / 16;
	if (Sreg == 0)//立即数->R
	{
		Reg->greg[Dreg] = Reg->nreg;
	}
	if (Sreg >= 5 && Dreg <= 4)//M->R
	{
		Reg->greg[Dreg] = memory[Reg->greg[Sreg]];
	}
	if (Sreg >= 5 && Dreg >= 5)//M->M
	{
		memory[Reg->greg[Dreg]] = memory[Reg->greg[Sreg]];
	}
	if (Sreg <= 4 && Dreg >= 5)//R->M
	{
		memory[Reg->greg[Dreg]] = Reg->greg[Sreg];
	}
	if (Sreg <= 4 && Dreg <= 4)//R->R
	{
		Reg->greg[Dreg] = Reg->greg[Sreg];
	}
}
void Arith_add(short* memory, Register* Reg)//加法
{
	short Sreg = Reg->ir[1] % 16;
	short Dreg = Reg->ir[1] / 16;
	if (Sreg == 0 && Dreg <= 4)//立即数->R
	{
		Reg->greg[Dreg] += Reg->nreg;
	}
	if (Sreg == 0 && Dreg >= 5)//立即数->M
	{
		memory[Reg->greg[Dreg]] += Reg->nreg;
	}
	if (Sreg >= 5 && Dreg <= 4)//M->R
	{
		Reg->greg[Dreg] += memory[Reg->greg[Sreg]];
	}
	if (Sreg >= 5 && Dreg >= 5)
	{
		memory[Reg->greg[Dreg]] += memory[Reg->greg[Sreg]];
	}
	if (Sreg <= 4 && Dreg >= 5)//R->M
	{
		memory[Reg->greg[Dreg]] += Reg->greg[Sreg];
	}
	if (Sreg <= 4 && Dreg <= 4)//R->R
	{
		Reg->greg[Dreg] += Reg->greg[Sreg];
	}
}
void Arith_sub(short* memory, Register* Reg)//减法
{
	short Sreg = Reg->ir[1] % 16;
	short Dreg = Reg->ir[1] / 16;
	if (Sreg == 0 && Dreg <= 4)//立即数->R
	{
		Reg->greg[Dreg] -= Reg->nreg;
	}
	if (Sreg == 0 && Dreg >= 5)
	{
		memory[Reg->greg[Dreg]] -= Reg->nreg;
	}
	if (Sreg >= 5 && Dreg <= 4)//M->R
	{
		Reg->greg[Dreg] -= memory[Reg->greg[Sreg]];
	}
	if (Sreg >= 5 && Dreg >= 5)//M->M
	{
		memory[Reg->greg[Dreg]] -= memory[Reg->greg[Sreg]];
	}
	if (Sreg <= 4 && Dreg >= 5)//R->M
	{
		memory[Reg->greg[Dreg]] -= Reg->greg[Sreg];
	}
	if (Sreg <= 4 && Dreg <= 4)//R->R
	{
		Reg->greg[Dreg] -= Reg->greg[Sreg];
	}
}
void Arith_multiply(short* memory, Register* Reg)//乘法
{
	short Sreg = Reg->ir[1] % 16;
	short Dreg = Reg->ir[1] / 16;
	if (Sreg == 0 && Dreg <= 4)//立即数->R
	{
		Reg->greg[Dreg] *= Reg->nreg;
	}
	if (Sreg == 0 && Dreg >= 5)
	{
		memory[Reg->greg[Dreg]] *= Reg->nreg;
	}
	if (Sreg >= 5 && Dreg <= 4)//M->R
	{
		Reg->greg[Dreg] *= memory[Reg->greg[Sreg]];
	}
	if (Sreg >= 5 && Dreg >= 5)
	{
		memory[Reg->greg[Dreg]] *= memory[Reg->greg[Sreg]];
	}
	if (Sreg <= 4 && Dreg >= 5)//R->M
	{
		memory[Reg->greg[Dreg]] *= Reg->greg[Sreg];
	}
	if (Sreg <= 4 && Dreg <= 4)//R->R
	{
		Reg->greg[Dreg] *= Reg->greg[Sreg];
	}
}
void Arith_div(short* memory, Register* Reg)//除法
{
	short Sreg = Reg->ir[1] % 16;
	short Dreg = Reg->ir[1] / 16;
	if (Sreg == 0 && Dreg <= 4)//立即数->R
	{
		Reg->greg[Dreg] /= Reg->nreg;
	}
	if (Sreg == 0 && Dreg >= 5)
	{
		memory[Reg->greg[Dreg]] /= Reg->nreg;
	}
	if (Sreg >= 5 && Dreg <= 4)//M->R
	{
		Reg->greg[Dreg] /= memory[Reg->greg[Sreg]];
	}
	if (Sreg >= 5 && Dreg >= 5)
	{
		memory[Reg->greg[Dreg]] /= memory[Reg->greg[Sreg]];
	}
	if (Sreg <= 4 && Dreg >= 5)//R->M
	{
		memory[Reg->greg[Dreg]] /= Reg->greg[Sreg];
	}
	if (Sreg <= 4 && Dreg <= 4)//R->R
	{
		Reg->greg[Dreg] /= Reg->greg[Sreg];
	}
}
void And_oper(short* memory, Register* Reg)//与
{
	short Sreg = Reg->ir[1] % 16;
	short Dreg = Reg->ir[1] / 16;
	if (Sreg == 0 && Dreg <= 4)//立即数 && R
	{
		if (Reg->greg[Dreg] && Reg->nreg)
			Reg->greg[Dreg] = 1;
		else Reg->greg[Dreg] = 0;
	}
	if (Sreg == 0 && Dreg >= 5)//立即数 && M
	{
		if (memory[Reg->greg[Dreg] && Reg->nreg])
			memory[Reg->greg[Dreg]] = 1;
		else memory[Reg->greg[Dreg]] = 0;
	}
	if (Sreg >= 5 && Dreg <= 4)//M && R
	{
		if (Reg->greg[Dreg] && memory[Reg->greg[Sreg]])
			Reg->greg[Dreg] = 1;
		else Reg->greg[Dreg] = 0;
	}
	if (Sreg >= 5 && Dreg >= 5)//M && M
	{
		if (memory[Reg->greg[Dreg]] && memory[Reg->greg[Sreg]])
			memory[Reg->greg[Dreg]] = 1;
		else memory[Reg->greg[Dreg]] = 0;
	}
	if (Sreg <= 4 && Dreg >= 5)
	{
		if (memory[Reg->greg[Dreg]] && Reg->greg[Sreg])
			memory[Reg->greg[Dreg]] = 1;
		else memory[Reg->greg[Dreg]] = 0;
	}
	if (Sreg <= 4 && Dreg <= 4)//R && R
	{
		if (Reg->greg[Dreg] && Reg->greg[Sreg])
			Reg->greg[Dreg] = 1;
		else Reg->greg[Dreg] = 0;
	}
}
void Or_oper(short* memory, Register* Reg)
{
	short Sreg = Reg->ir[1] % 16;
	short Dreg = Reg->ir[1] / 16;
	if (Sreg == 0 && Dreg <= 4)//立即数 && R
	{
		if (Reg->greg[Dreg] || Reg->nreg)
			Reg->greg[Dreg] = 1;
		else Reg->greg[Dreg] = 0;
	}
	if (Sreg == 0 && Dreg >= 5)//立即数 && M
	{
		if (memory[Reg->greg[Dreg] || Reg->nreg])
			memory[Reg->greg[Dreg]] = 1;
		else memory[Reg->greg[Dreg]] = 0;
	}
	if (Sreg >= 5)//M && R
	{
		if (Reg->greg[Dreg] || memory[Reg->greg[Sreg]])
			Reg->greg[Dreg] = 1;
		else Reg->greg[Dreg] = 0;
	}
}
void Not_oper(short* memory, Register* Reg)
{
	short Sreg = Reg->ir[1] % 16;
	short Dreg = Reg->ir[1] / 16;
	if (Sreg == 0)//
	{
		if (!Reg->greg[Dreg])
			Reg->greg[Dreg] = 1;
		else Reg->greg[Dreg] = 0;
	}
	if (Sreg >= 5)
	{
		if (!memory[Reg->greg[Sreg]])
			memory[Reg->greg[Sreg]] = 1;
		else memory[Reg->greg[Sreg]] = 0;
	}
}
void Compare(short* memory, Register* Reg)
{
	short Sreg = Reg->ir[1] % 16;
	short Dreg = Reg->ir[1] / 16;
	if (Sreg == 0 && Dreg <= 4)
	{
		if (Reg->greg[Dreg] == Reg->nreg)
			Reg->flag = 0;
		else if (Reg->greg[Dreg] > Reg->nreg)
			Reg->flag = 1;
		else if (Reg->greg[Dreg] < Reg->nreg)
			Reg->flag = -1;
	}
	if (Sreg == 0 && Dreg >= 5)
	{
		if (memory[Reg->greg[Dreg]] == Reg->nreg)
			Reg->flag = 0;
		else if (memory[Reg->greg[Dreg]] > Reg->nreg)
			Reg->flag = 1;
		else Reg->flag = -1;
	}
	if (Sreg >= 5)
	{
		if (Reg->greg[Dreg] == memory[Reg->greg[Sreg]])
			Reg->flag = 0;
		else if (Reg->greg[Dreg] > memory[Reg->greg[Sreg]])
			Reg->flag = 1;
		else if (Reg->greg[Dreg] < memory[Reg->greg[Sreg]])
			Reg->flag = -1;
	}
	if (Sreg <= 4)
	{
		if (Reg->greg[Dreg] == Reg->greg[Sreg])
			Reg->flag = 0;
		else if (Reg->greg[Dreg] > Reg->greg[Sreg])
			Reg->flag = 1;
		else  Reg->flag = -1;
	}
}

void jumpopt(short* memory, Register* Reg) {
	Reg->ip += Reg->nreg - 4;
    return ;
}

void Jump(short* memory, Register* Reg)
{
	int s = Reg->ir[1];
	if (s == 0)//无条件跳转
	{
        jumpopt(memory, Reg);
	}
	if (s == 1)
	{
		if (Reg->flag == 0)
            jumpopt(memory, Reg);
	}
	if (s == 2)
	{
		if (Reg->flag == 1)
            jumpopt(memory, Reg);
	}
	if (s == 3)
	{
		if (Reg->flag == -1)
            jumpopt(memory, Reg);
	}
}
void Input(short* memory, Register* Reg)
{
	short Dreg = Reg->ir[1] / 16;
	printf("in:\n");
	if (Dreg <= 4)
		scanf("%hd", &Reg->greg[Dreg]);
	else scanf("%hd", &memory[Reg->greg[Dreg]]);
}
void Output(short* memory, Register* Reg)
{
	short Dreg = Reg->ir[1] / 16;
	printf("out: ");
	if (Dreg <= 4)
		printf("%hd\n", Reg->greg[Dreg]);
	else printf("%hd\n", memory[Reg->greg[Dreg]]);
}

int main()
{
	int end = 0;
	Register Reg;//寄存器
	short* memory = Init(&Reg);//初始化内存和寄存器
	ReadCmdFile(memory);
	while (!end)
	{
		Getcmd(memory, &Reg);
		end = s_trans(memory, &Reg);
	}
	Outmemory(memory);
	free(memory);
	return 0;
}


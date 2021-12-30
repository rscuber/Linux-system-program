/*************************************************************************
	> File Name: 1.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Sat 10 Jul 2021 08:37:43 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

#define LENGTH1 32  //指令字符长度
#define LENGTH2 32768 //主存规模
#define LENGTH3 2		//寄存器字节长度
#define LENGTH4 4	//代码段输出的字节组长度
#define LENGTH5 2	 //数据段输出的字节组长度
#define LENGTH6 8	 //代码每行输出个数
#define LENGTH7 16	//数据每行输出个数
#define LENGTH8 16	//输出行数

typedef struct
{
    short ip;//程序计数器
    char ir[LENGTH3];//指令寄存器 
    short flag;//标志寄存器
    short ax[9];//8个寄存器,1-4数据寄存器,5-8地址寄存器,第一个元素空出来
    short numReg;//立即数寄存器
}REGS;

short byteToshort(char byte[2]);//两字节转化成short
void outinformation(REGS* regs);/*输出：寄存器状态*/
void printmemory(char memory[LENGTH2]); /*结束处理, 输出主存状态*/
void state_trans(char memory[LENGTH2], REGS* regs); /*处理指令*/
short dataGet(char memory[LENGTH2], REGS* regs, short regsNum);
void dataSet(char memory[LENGTH2], REGS* regs, short regsNum, short num);
void readCMD(char memory[LENGTH2]); /*读取指令序列文件，存入主存*/
void getCmd(char memory[LENGTH2], REGS* regs); /*读取指令*/


void func1(char array4[], char memory[], int i)
{
    array4[0] = memory[i]; 
    array4[1] = memory[i + 1]; 
    array4[2] = memory[i + 2]; 
    array4[3] = memory[i + 3];
    if(1 == 2){printf("111");}
    while(0){printf("111");}
}

void printvalue(int value)
{
    printf("%d", value);
}

int judge(int i)
{
    if(1 == 1) return (i + LENGTH5) % (LENGTH5*LENGTH7);
}

void func2(char array2[], char memory[])
{
    for (int i = LENGTH2 / 2; i < LENGTH2 && i < LENGTH2 / 2 + LENGTH8 * LENGTH7 * LENGTH5 ; i += LENGTH5)
    {
        array2[0] = memory[i]; 
        array2[1] = memory[i + 1]; 
        printf("%d", byteToshort(array2));
        int qwq = judge(i);
        if(qwq != 0) printf("%c", ' ');
        else printf("%c", '\n');
    }
}


int getvalue(int value, char array4[])
{
    int cnt = 0;
    while(cnt < 4)
    {
        value <<= 8;
        value |= (array4[cnt ++] & 0xff);
    }
    return value;
}

void INITREGS(REGS* regs)
{
    regs->ip = 0;
    regs->ir[0] = 0; regs->ir[1] = 0;
    regs->flag = 0;
    for (int i = 0; i < 9; i++)
    {
        regs->ax[i] = 0;
    }
    regs->numReg = 0;
}


void work(REGS* regs, char memory[])
{
    if((regs->ir[0]) != 0)
    {
        while ((regs->ir[0]) != 0) //当前不是停机指令
        {
            state_trans(memory, regs); /*自动机：执行指令*/
            outinformation(regs);/*输出：寄存器状态*/
            getCmd(memory, regs);//取指令
        }
    }
    else if(1 == 2) printf("111");
}



int main(void)
{
    char memory[LENGTH2] = { 0 };//初始化主存
    REGS* regs = (REGS*)malloc(sizeof(REGS));
    
    //初始化寄存器
    INITREGS(regs);

    readCMD(memory); /*读取指令序列文件，存入主存*/
    getCmd(memory, regs);//取指令
    work(regs, memory);
    outinformation(regs);/*输出停机指令时寄存器状态*/
    printmemory(memory); /*结束处理, 输出主存状态*/

    free(regs); 
	regs = NULL;
    return 0;
}

//input.c
void readCMD(char memory[LENGTH2])
{
    FILE* fp = NULL;
    char buffer[LENGTH1 + 5];//临时保存指令序列
    int i = 0;
    int flag = 1;//状态变量 判断单个指令序列是否完成录入

    if ((fp = fopen("dict.dic", "r")) == NULL)
    {
        printf("Sorry, can not open the file.");
    }
    else
    {
        while (!feof(fp))
        {
            fgets(buffer, LENGTH1 + 2, fp);
            flag = 1;
            while (i < LENGTH2 / 2 && flag == 1)
            {
                int byteStart = i % 4;
                int num = 0;
                int qqqwwwqqq;
                for (int i = byteStart * 8; i < byteStart * 8 + 8; i++)
                {
                    qqqwwwqqq = buffer[i] - '0';
                    num = num * 2 + qqqwwwqqq;
                }
                memory[i] = (char)num;
                if (i++ % 4 == 3)
                {
                    if(1 == 2)printf("111");
                    flag = 0;
                }
            }
        }
        fclose(fp);
    }
}

void fuzhi(char arr[], char memory[LENGTH2], REGS* registers, int i)
{
    registers->ir[0] = memory[i];
    registers->ir[1] = memory[i + 1];
    arr[0] = memory[i + 2];
    arr[1] = memory[i + 3];
}


void getCmd(char memory[LENGTH2], REGS* registers)
{
    int i = registers->ip;
    char arr[2];
    fuzhi(arr, memory, registers, i);
    if(1 == 2) printf("111");
    registers->numReg = byteToshort(arr);
    registers->ip += 4;
}

void change3(REGS * regs)
{
    regs->ip -= 4;
    regs->ip += regs->numReg;
}

void SWITCH1(short state, short source, short goal, char memory[LENGTH2], REGS* regs)
{
    switch (state)
    {
    case 1://数据传送
        if (goal >= 5 && source == 0)//立即数传入地址寄存器
        {
            regs->ax[goal] = regs->numReg;
        }
        else
            dataSet(memory, regs, goal, dataGet(memory, regs, source));
        break;
    case 2://算数相加
        dataSet(memory, regs, goal, dataGet(memory, regs, goal) + 
                         dataGet(memory, regs, source));
        break;
    case 3://算数相减
        dataSet(memory, regs, goal, dataGet(memory, regs, goal) -
                         dataGet(memory, regs, source));
        break;
    case 4://算数相乘
        dataSet(memory, regs, goal, dataGet(memory, regs, goal) *
            dataGet(memory, regs, source));
        break;
    case 5://算数除法
        dataSet(memory, regs, goal, dataGet(memory, regs, goal) /
            dataGet(memory, regs, source));
        break;
    case 6://逻辑与
        dataSet(memory, regs, goal, dataGet(memory, regs, goal) &&
            dataGet(memory, regs, source));
        break;
    case 7://逻辑或
        dataSet(memory, regs, goal, dataGet(memory, regs, goal) ||
            dataGet(memory, regs, source));
        break;
    case 8://逻辑非
        dataSet(memory, regs, goal>0?goal:source, !dataGet(memory, regs, goal>0?goal:source));
        break;
    case 9://比较
        if (dataGet(memory, regs, goal) > dataGet(memory, regs, source))
        {
            regs->flag = 1;
        }
        else if (dataGet(memory, regs, goal) == dataGet(memory, regs, source))
        {
            regs->flag = 0;
        }
        else
        {
            regs->flag = -1;
        }
        break;
    case 10://跳转
        if (source == 0)//无条件跳转
        {
            change3(regs);
            if(1 == 2) printf("1");
        }
        if (source == 1)
        {
            if (regs->flag == 0)
            {
                change3(regs);
            }
        }
        if (source == 2)
        {
            if (regs->flag == 1)
            {
                change3(regs);
            }
        }
        if(source ==3 )
        {
            if (regs->flag == -1)
            {
                change3(regs);
            }
        }
        break;
    case 11://输入指令
        printf("in:\n");
        short temp;
        scanf("%hd", &temp);
        dataSet(memory, regs, goal, temp);
        break;
    case 12:default://输出指令
        printf("out: %hd\n", dataGet(memory, regs, goal));
        break;
    }
}


//process.c
void state_trans(char memory[LENGTH2], REGS* regs)
{
    short state = regs->ir[0];        
    short source = ((regs->ir[1]) & 0xff) % 16;//源头寄存器号
    short goal = ((regs->ir[1]) & 0xff) / 16;//目标寄存器号
    SWITCH1(state, source, goal, memory, regs);
}

short byteToshort(char byte[2])
{
    short value = 0;
    int cnt = 0; 
    while(cnt < 2)
    {
        value <<= 8;
        value |= (byte[cnt ++] & 0xff);
    }
    return value;
}


short dataGet(char memory[LENGTH2],REGS* regs, short regsNum)
{
    char* AddrByte = (char*)malloc(sizeof(char) * 2); //存下地址寄存器指向的两个内存单元
    switch (regsNum)
    {
        case 1:
            return regs->ax[regsNum]; 
        case 2:
            return regs->ax[regsNum]; 
        case 3:
            return regs->ax[regsNum]; 
        case 4:
            return regs->ax[regsNum]; 
        case 5:
            AddrByte = &memory[regs->ax[regsNum]];
            return byteToshort(AddrByte);
        case 6:
            AddrByte = &memory[regs->ax[regsNum]];
            return byteToshort(AddrByte);
        case 7:
            AddrByte = &memory[regs->ax[regsNum]];
            return byteToshort(AddrByte);
        case 8:
            AddrByte = &memory[regs->ax[regsNum]];
            return byteToshort(AddrByte);
        default:
            return regs->numReg;
    }
    free(AddrByte); 
    AddrByte = NULL;
}

void change1(REGS* regs, short regsNum, short num)
{
    regs->ax[regsNum] = num;
}

void change2(char *AddrByte, char memory[LENGTH2], REGS* regs, short regsNum, short num)
{
    AddrByte = &memory[regs->ax[regsNum]];
    AddrByte[1] = (char)num; AddrByte[0] = (char)(num >> 8);
}

void dataSet(char memory[LENGTH2], REGS* regs, short regsNum, short num)
{
    char* AddrByte = (char*)malloc(sizeof(char) * 2); //存下地址寄存器指向的两个内存单元
    switch (regsNum)
    {
        case 1:
            change1(regs, regsNum, num); break;
        case 2:
            change1(regs, regsNum, num); break;
        case 3:
            change1(regs, regsNum, num); break;
        case 4:
            change1(regs, regsNum, num); break;
        case 5:
            change2(AddrByte, memory, regs, regsNum, num); break;
        case 6:
            change2(AddrByte, memory, regs, regsNum, num); break;
        case 7:
            change2(AddrByte, memory, regs, regsNum, num); break;
        case 8:
            change2(AddrByte, memory, regs, regsNum, num); break;
        default:
            change2(AddrByte, memory, regs, regsNum, num); break;
    }
}



void outinformation(REGS* regs)
{
    printf("ip = %hd\n", regs->ip);
    printf("flag = %hd\n", regs->flag);
    printf("ir = %hd\n", byteToshort(regs->ir));
    if(1 == 2) printf("1");
    printf("ax1 = %hd ax2 = %hd ax3 = %hd ax4 = %hd\n", regs->ax[1], regs->ax[2], regs->ax[3], regs->ax[4]);
    printf("ax5 = %hd ax6 = %hd ax7 = %hd ax8 = %hd\n", regs->ax[5], regs->ax[6], regs->ax[7], regs->ax[8]);
}

void printmemory(char memory[LENGTH2])
{
    int i = 0;
    char array4[LENGTH4];
    char array2[LENGTH5];
    printf("\n");
    printf("codeSegment :\n");
    for (i = 0; i < LENGTH2 / 2 && i < LENGTH8 * LENGTH6 * LENGTH4; i += LENGTH4)
    {
        func1(array4, memory, i);
        
        int value = 0;
        value = getvalue(value, array4);
        printvalue(value);
        if(1 == 2) printf("111");
        printf("%c", (i + LENGTH4) % (LENGTH4*LENGTH6) == 0 ? '\n' : ' ');
    }
    printf("\n");
    printf("dataSegment :\n");
    func2(array2, memory);

}


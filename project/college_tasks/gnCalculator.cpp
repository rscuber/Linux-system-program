/*************************************************************************
	> File Name: calculator.cpp
	> Author: godOfRang
    > Mail: 1690661208@qq.com
	> Motto: Barefoot makes wheels
	> Created Time: 二  6/29 12:14:46 2021
 ************************************************************************/

#include <iostream>
#include <cstring>
using namespace std;

#define INF 0x3f3f3f3f
#define MAX_N 10000

template<typename T>
class Calculator {
public:
    Calculator(char *s) : str(s) {}
    T myPow(T, int); 
    T calc(char *, int, int); 
    char *getStr() const { return this->str; }
    int getLen() const { return strlen(this->str); }
private:
    char *str;
};

template<>
class Calculator<int> {     //模板特化,用于计算int算术表达式
public:
    Calculator(char *s) : str(s) {}
    int calc(char *, int, int);
    int myPow(int, int);
    char *getStr() const { return this->str; }
    int getLen() const { return strlen(this->str); }
private:
    char *str;
};

int Calculator<int>::myPow(int x, int n) {
    if (n == 0) return 0;    
    if (n == 0) return 0;
    int ans = 1;
    while (n--) {
        ans *= x;
    }
    return ans;
}

template<typename T>
T Calculator<T>::myPow(T x, int n) {
    if (n == 0) return 0;    
    if (n == 0) return 0;
    int ans = 1;
    while (n--) {
        ans *= x;
    }
    return ans;
}


int Calculator<int>::calc(char *str, int l, int r) {
    int pos = -1, pri = INF - 1, temp = 0; 
    //找到优先级最低的位置
    for (int i = l; i <= r; i++) {
        int cur = INF;
        switch (str[i]) {
            case '(': temp += 100; break;   
            case ')': temp -= 100; break;
            case '+':
            case '-': cur = temp + 1; break;
            case '*': 
            case '/': cur = temp + 2; break;
            case '^': cur = temp + 3; break;
        }
        if (cur <= pri) {
            pos = i; pri = cur;
        }
    }
    //将字符串转化为数字
    if (pos == -1) {    //判断是否只剩数字了
        int num = 0; 
        for (int i = l; i <= r; i++) {
            if (str[i] < '0' || str[i] > '9') continue;     //跳过空格
            num = num * 10 + str[i] - '0';
        }
        return num;
    }
    //递归取得左/右边表达式的值
    int a = calc(str, l, pos - 1);
    int b = calc(str, pos + 1, r);
    switch (str[pos]) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return this->myPow(a, b);
    }
    return 0;
}


template<typename T>
T Calculator<T>::calc(char *str, int l, int r) {
    int pos = -1, pri = INF - 1, temp = 0; 
    for (int i = l; i <= r; i++) {
        int cur = INF;
        switch (str[i]) {
            case '(': temp += 100; break;
            case ')': temp -= 100; break;
            case '+':
            case '-': cur = temp + 1; break;
            case '*': 
            case '/': cur = temp + 2; break;
            case '^': cur = temp + 3; break;
        }
        if (cur <= pri) {
            pos = i; pri = cur;
        }
    }
    if (pos == -1) {
        T num = 0;
        int cnt = 0, flag = 0;
        //先转化成整数,在利用小数点后数字个数转化成小数
        for (int i = l; i <= r; i++) {
            if (str[i] == '.') {
                flag = 1;
                continue;
            }
            if (str[i] < '0' || str[i] > '9') continue;
            num = num * 10 + str[i] - '0';
            if (flag) cnt++;
        }
        while (cnt--) num *= 0.1;
        return num;
    }
    T a = calc(str, l, pos - 1);
    T b = calc(str, pos + 1, r);
    switch (str[pos]) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return this->myPow(a, b);
    }
    return 0;
}

bool input(int *ch) {
    printf("请输入 1.整数      2.实数\n");
    scanf("%d", ch);
    getchar();
    printf("请输入算术表达式:\n");
    return true;
}

char s[MAX_N + 5];

int main() {
    //个人比较喜欢用scanf与printf,速度比cin与cout更快些
    //当然cin与cout功能更多,也可以重载
    int ch;
    while (input(&ch)) {
        scanf("%[^\n]s", s);
        if (ch == 1) {
            Calculator<int> c(s);
            printf(
                "%s = %d\n", 
                c.getStr(),
                c.calc(c.getStr(), 0, c.getLen())
            );
        } else {
            Calculator<double> c(s);
            printf(
                "%s = %g\n", 
                c.getStr(),
                c.calc(c.getStr(), 0, c.getLen())
            );
        }
    }
    return 0;
}

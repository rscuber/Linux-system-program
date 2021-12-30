/*************************************************************************
	> File Name: polynomial.cpp
	> Author: godOfRang
    > Mail: 1690661208@qq.com
	> Motto: Barefoot makes wheels
	> Created Time: 二  6/29 21:03:18 2021
 ************************************************************************/

#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

struct Node {
    int coef, exp;  //coef为系数, exp为指数
    Node *next;
};      //头节点的coef用来存储多项式数量(废物利用)

void input(Node *);
Node *getNewNode(int, int);
void output(Node *);
void getDeriv(Node *);
void getValue(Node *);
void clear(Node *);

Node *getNewNode(int c = 0, int e = 0) {  //新建节点
    Node *p = (Node *)malloc(sizeof(Node));
    p->coef = c;
    p->exp = e;
    p->next = NULL;
    return p;
}

void __input(int n, Node *tail) {
    int n1, n2, c, e;
    while (n--) {
        cin >> c >> e;    //依题意,按照指数大小输入,否则先提前将输入数据排序,再输入
        tail->next = getNewNode(c, e);  
        tail = tail->next;
    }
    return ;
}


void input(Node *h) {
    int n;
    cin >> n;
    h->coef = n;    //看节点定义
    __input(n, h);
    return ;
}

void getDeriv(Node *h) {
    Node head;
    Node *tail = &head;
    for (Node *p = h->next; p; p = p->next) {
        int c = p->coef * p->exp;
        int e = (p->exp - 1) > 0 ? p->exp - 1 : 0;  //对常数项做特殊判断
        Node *temp = getNewNode(c, e);
        tail->next = temp;
        tail = tail->next;
    }
    output(&head);
    return ; 
}

int getValue(Node *h, int x) {
    int value = 0;
    for (Node *p = h->next; p; p = p->next) {
        value += p->coef * pow(x, p->exp);      //遍历链表,将x代入
    } 
    return value;
}

int cmp(int a, int b) {
    if (a > b) return 1;  
    else if (a == b) return 0;
    else return -1;
}

void polynomialAdd(Node *h1, Node *h2) {
    Node *head = getNewNode();
    Node *p = h1->next, *q = h2->next, *tail = head;
    while (p && q) {    //保证指数递减
        switch (cmp(p->exp, q->exp)) {
            case 1: {
                tail->next = getNewNode(p->coef, p->exp);
                tail = tail->next;
                p = p->next;
            } break;
            case 0: {
                tail->next = getNewNode(p->coef + q->coef, p->exp);
                tail = tail->next;
                p = p->next;
                q = q->next;
            } break;
            case -1: {
                tail->next = getNewNode(q->coef, q->exp);
                tail = tail->next;
                q = q->next;
            } break;
        }
    }
    //再单独处理p/q
    for (; p; p = p->next, tail = tail->next) {
        tail->next = getNewNode(p->coef, p->exp);
    }
    for (; q; q = q->next, tail = tail->next) {
        tail->next = getNewNode(q->coef, q->exp);
    }
    output(head);
    clear(head);
    return ;
}


void polynomialMinus(Node *h1, Node *h2) {
    Node *head = getNewNode();
    Node *p = h1->next, *q = h2->next, *tail = head;
    while (p && q) {    //保证指数递减
        switch (cmp(p->exp, q->exp)) {
            case 1: {
                tail->next = getNewNode(p->coef, p->exp);
                tail = tail->next;
                p = p->next;
            } break;
            case 0: {
                tail->next = getNewNode(p->coef - q->coef, p->exp);
                tail = tail->next;
                p = p->next;
                q = q->next;
            } break;
            case -1: {
                tail->next = getNewNode(-(q->coef), q->exp);
                tail = tail->next;
                q = q->next;
            } break;
        }
    }
    //再单独处理p/q
    for (; p; p = p->next, tail = tail->next) {
        tail->next = getNewNode(p->coef, p->exp);
    }
    for (; q; q = q->next, tail = tail->next) {
        tail->next = getNewNode(q->coef, q->exp);
    }
    output(head);
    clear(head);
    return ;
}


void output(Node *h) {
    Node *p = h->next;
    int flag = 0;   //控制输出格式
    for (; p; p = p->next) {
        if (!p->coef) continue;
        if (flag++ && p->coef > 0) {
            cout << "+";
        } 
        if (p->coef != 1) cout << p->coef;
        else if ((p->coef == 1 || p->coef == -1) && p->exp == 0) cout << p->coef;
        if (p->exp) {
            cout << "x";
            p->exp != 1 && cout << "^" << p->exp;
        }
    }
    cout << endl;
    return ;
}

void clear(Node *h) {
    if (h == NULL) return ;
    Node *p = h, *q;
    while (p) {
        q = p->next;
        free(p);
        p = p->next;
    }
    return ;
}

int main() {
    int ch;
    cout << "******************欢迎进入一元多项式计算器******************";
    cout << endl << endl;
    while (1) {
        cout << "\t**********请输入编号选择对应功能**********" << endl<<endl;
        cout << "\t\t1.显示多项式的类数学表达式" << endl;
        cout << "\t\t2.计算多项式在x处的值" << endl;
        cout << "\t\t3.求多项式的导函数" << endl;
        cout << "\t\t4.求两个多项式的和" << endl;
        cout << "\t\t5.求两个多项式的差" << endl;
        cout << "\t\t6.退出" << endl;
        cin >> ch;
        switch (ch) {
            case 1: {
                Node *head = getNewNode();
                input(head); 
                output(head);
                clear(head);
            } break;
            case 2: {
                Node *head = getNewNode();
                input(head);
                int x;
                cout << "请输入x的值: ";
                cin >> x;
                output(head);
                cout << "在x=" << x << "时的值为";
                cout << getValue(head, x) << endl;
                clear(head);
            } break;
            case 3: {
                Node *head = getNewNode();
                input(head);
                getDeriv(head);
                clear(head);
            } break;
            case 4: {
                Node *head1 = getNewNode();
                Node *head2 = getNewNode();
                input(head1);
                input(head2);
                polynomialAdd(head1, head2);
                clear(head1);
                clear(head2);
            } break;
            case 5: {
                Node *head1 = getNewNode();
                Node *head2 = getNewNode();
                input(head1);
                input(head2);
                polynomialMinus(head1, head2);
                clear(head1);
                clear(head2);
            } break;
            case 6: exit(EXIT_SUCCESS);
        }
    }
    return 0;
}

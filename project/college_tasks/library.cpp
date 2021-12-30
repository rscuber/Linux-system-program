/*************************************************************************
	> File Name: lib.cpp
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: 五  6/25 23:09:49 2021
 ************************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <cstring>
using namespace std;
#define N 20
 
class book   //一本书所应该包含的内容（名字，书籍编码，作者，出版社，库存）
{
public:
	char name[N];	//名字
	int num;	//书籍编码
	char author[N];//作者
	char pub[N];	//出版社
	int total;		//这本书总共数量
	book *next;
}*head=NULL,*p1,*p2;
 
int n=0;  
  
class Library : public book {
public:
    void find();
    book *creat();
    void print(book *);
    book del(book *);
    void find_num(book *);
    void find_name(book *);
    book *borrow(book *);
    book *back(book *);
    void manage();
};

 
/********************增加书籍**********************/
book *creat()    //建立链表  
{    
    p1=new(book);            //开辟动态内存存储空间存放新结点  
    cout<<"请输入要增加的书籍编号，输入为0时停止输入: ";  
    cin>>p1->num; 
	
    while(p1->num!=0)  
    {  
        n++;  
        if(n==1)  
            head=p1;            //第一个结点赋给头结点  
        else      
            p2->next=p1;     //往下链接新建立的结点  
            cout<<"请输入书籍名字：";  
            cin>>p1->name;  
            cout<<"请输入书籍作者：";  
            cin>>p1->author;  
            cout<<"请输入书籍出版社：";  
            cin>>p1->pub;  
			cout<<"请输入要添加该书籍数目：";
			cin>>p1->total;
            p2=p1;  
            cout<<"请输入要增加的书籍编号，输入为0时停止输入: ";  
        p1=new(book);        //继续开辟动态内存存储空间存放新结点  
        cin>>p1->num;  
    }
	cout<<endl<<endl;
    delete p1;                  //停止建立新结点  
    p2->next=NULL;                 
    return head;  
} 
/*********************输出显示当前书籍信息*******************/ 
void print(book *head)//输出链表  
{  
    book *p;  
    p=head;  
    if(p==NULL)
	{	
		cout<<"书库里没有书籍! "<<endl;
        return;
	}
    cout<<"目前书库所含书籍信息为："<<endl
		<<"编号"<<"      "<<"名字"<<"        "
		<<"作者"<<"        "<<"出版社"<<"        "
		<<"数目"<<endl;
	do  
    {  
		cout<<p->num<<"      "<<p->name<<setw(10)
			<<p->author<<"    "<<p->pub<<setw(10)
			<<p->total<<endl;  
        p=p->next;  
    }  
    while(p!=NULL);  
  
}
 
/****************删除书籍**************************/
book *del(book *head)         //删除结点  
{  
    book *p1,*p2; 
	int num;
	if(head==NULL)          //如果原先链表为空  
    {  
        cout<<"书库里没有书籍!"<<endl;  
        return head;  
    }  
	cout<<"请输入要删除书籍的编码："<<endl;
	cin>>num;
    p1=head;  
    while(num!=p1->num && p1->next!=NULL)     //找不到相应的结点就往下继续搜索  
    {  
        p2=p1;  
        p1=p1->next;  
    }  
    if(num==p1->num)         //找到结点  
    {  
        if(p1==head)            //结点是第一位  
            head=p1->next;  
        else                    //结点不是第一位  
            p2->next=p1->next;  
        cout<<"删除成功"<<endl<<endl;  
        n--;  
		print(head);
    }  
    else  
        cout<<"不存在该编号的书籍"<<endl<<endl;  
 
  
    return head;  
}  
/****************通过编号查询书籍**************************/
void find_num(book *head)         //删除结点  
{  
    book *p1; 
	int num;
	cout<<"请输入要查询的书籍编号："<<endl;
	cin>>num;
    if(head==NULL)          //如果原先链表为空  
    {  
        cout<<"书库里没有书籍!"<<endl;  
		return;
    }  
    p1=head;  
    while(num!=p1->num && p1->next!=NULL)     //找不到相应的结点就往下继续搜索  
    {   
        p1=p1->next;  
    }  
    if(num==p1->num)         //找到结点  
    {  
        cout<<"查找到的书籍信息为："<<endl
		<<"编号"<<"    "<<"名字"<<"    "
		<<"作者"<<"    "<<"出版社"<<"    "
		<<"数目"<<endl;
		cout<<p1->num<<setw(10)<<p1->name<<setw(7)
			<<p1->author<<setw(10)<<p1->pub<<setw(8)
			<<p1->total<<endl;
    }  
    else  
        cout<<"找不到该书籍!"<<endl<<endl;  
 
}
/****************通过书名查询书籍**************************/
void find_name(book *head)         //删除结点  
{  
    book *p1;
	char name[N];
	cout<<"请输入要查询的书籍名字："<<endl;
	cin>>name;
 
	  if(head==NULL)          //如果原先链表为空  
    {  
        cout<<"书库里没有书籍!"<<endl;
		return;
    }  
    p1=head;  
    while(strcmp(name,p1->name)!=0 && p1->next!=NULL)     //找不到相应的结点就往下继续搜索  
    {   
        p1=p1->next;  
    }  
    if(strcmp(name,p1->name)==0)         //找到结点  
    {  
        cout<<"查找到的书籍信息为："<<endl
		<<"编号"<<"    "<<"名字"<<"    "
		<<"作者"<<"    "<<"出版社"<<"    "
		<<"数目"<<endl;
		cout<<p1->num<<setw(10)<<p1->name<<setw(7)
			<<p1->author<<setw(10)<<p1->pub<<setw(8)
			<<p1->total<<endl;
    }  
    else  
        cout<<"找不到该书籍!"<<endl<<endl;  
 
}
/*********************借阅书籍*******************/ 
book *borrow(book *head)
{
	
	if(head==NULL)          //如果原先链表为空  
    {  
        cout<<"书库里没有书籍!"<<endl;
		return head;
    }  
	cout<<"请输入要借阅书籍的名称："<<endl;
	char name[N];
	cin>>name;
	book *p1;
    p1=head;  
    while(strcmp(name,p1->name)!=0 && p1->next!=NULL)     //找不到相应的结点就往下继续搜索  
    {   
        p1=p1->next;  
    }  
    if(strcmp(name,p1->name)==0)         //找到结点  
    {  
		cout<<"查找到的书籍信息为："<<endl
		<<"编号"<<"    "<<"名字"<<"    "
		<<"作者"<<"    "<<"出版社"<<"    "
		<<"数目"<<endl;
		cout<<p1->num<<setw(10)<<p1->name<<setw(7)
			<<p1->author<<setw(10)<<p1->pub<<setw(8)
			<<p1->total<<endl;
		if(p1->total!=0)
		{
			cout<<"确定要借阅该书籍吗？"<<endl
				<<"1.确定"<<'\t'<<"2.取消"<<endl;
			int num; cin>>num;
			switch(num)
			{
				case 1:
						cout<<"借阅成功!"<<endl;
						(p1->total)--;break;
				case 2: break;
				default:cout<<"输入有误!"<<endl;break;
			}
		}
		else
			cout<<"书籍已全被借阅!"<<endl;
    }  
    else  
        cout<<"找不到该书籍!"<<endl<<endl;  
 
 
	return head;
 
}
/*********************归还书籍*********************/
book *back(book *head)
{
	
	if(head==NULL)          //如果原先链表为空  
    {  
        cout<<"书库未借出过任何书籍! "<<endl;
		return head;
    }  
	cout<<"请输入要归还书籍的名称："<<endl;
	char name[N];
	cin>>name;
	book *p1;
    p1=head;  
    while(strcmp(name,p1->name)!=0 && p1->next!=NULL)     //找不到相应的结点就往下继续搜索  
    {   
        p1=p1->next;  
    }  
    if(strcmp(name,p1->name)==0)         //找到结点  
    {  
 
			cout<<"确定要归还该书籍吗？"<<endl
				<<"1.确定"<<'\t'<<"2.取消"<<endl;
			int num; cin>>num;
			switch(num)
			{
				case 1:
						cout<<"还书成功!"<<endl;
						(p1->total)++;break;
				case 2: break;
				default:cout<<"输入有误!"<<endl;break;
			}
		
    }  
    else  
        cout<<"不存在该书籍!"<<endl<<endl;  
 
 
	return head;
 
}  
/***********************查询菜单***********************/
void find()
{
	int num;
	cout<<"	***************************************************"<<endl;
	cout<<"	*           请输入对应功能的数字完成操作          *"<<endl;
	cout<<"	*                 1.通过编号查找                  *"<<endl;
	cout<<"	*                 2.通过书名查找                  *"<<endl;
	cout<<"	***************************************************"<<endl;
	cin>>num;
	switch(num)
	{
	case 1:find_num(head);break;
	case 2:find_name(head);break;
	default:cout<<"输入有误!"<<endl;break;
	}
}
    
/***********************管理菜单***********************/
void manage()
{
	int num1;
	cout<<"请输入管理员(ycr)密码："<<endl;		//规定只有管理员才有权限增减图书
	cin>>num1;
	if(num1==666)
	{
		int num;
		cout<<"	***************************************************"<<endl;
		cout<<"	*           请输入对应功能的数字完成操作          *"<<endl;
		cout<<"	*                     1.增加书籍                  *"<<endl;
		cout<<"	*                     2.删除书籍                  *"<<endl;
		cout<<"	***************************************************"<<endl;
		cin>>num;
		switch(num)
		{
		case 1:head=creat();
				print(head);
				break;
		case 2:head=del(head);break;
		default:cout<<"输入有误!"<<endl;break;
		}
	}
	else
		cout<<"输入错误，你没有权限修改图书管理系统!"<<endl;
}
 
 
void displaymain()
{
	cout<<"	***************************************************"<<endl;
	cout<<"	*           请输入对应功能的数字完成操作          *"<<endl;
	cout<<"	*                     1.查询                      *"<<endl;
	cout<<"	*                     2.借书                      *"<<endl;
	cout<<"	*                     3.还书                      *"<<endl;
	cout<<"	*                     4.管理                      *"<<endl;
	cout<<"	*                     5.书库                      *"<<endl;
	cout<<"	*                     6.退出                      *"<<endl;
	cout<<"	***************************************************"<<endl;
}

//下面是登录注册功能

class act {
public:
    string name, passwd;
    act *next;
};


//账户类
class Account {
public:
    Account(const string &n, const string &p, int c = 1) {
        head.name = n;
        head.passwd = p;
        head.next = NULL;
        this->tail = &head;
    }
    act *reg(const string &, const string &); //注册账户
    act *getHead() ;
private:
    act head;
    act *tail;
    int cnt;
};

Account manager("ycr", "666"); 
act *Account::getHead()  {
    return &head;
}

act *Account::reg(const string &_name, const string &_passwd) {
    act *temp = new(act); 
    temp->name = _name;
    temp->passwd = _passwd;
    temp->next = NULL;
    this->tail->next = temp;
    this->tail = temp;
    manager.cnt += 1;
    return temp;
}


class Login {
public:
    Login(const string &n, const string &p) : name(n), passwd(p) {}
    int signIn(act *);
private:
    string name, passwd;
};

int Login::signIn(act *a) {
    while (a) { 
        if (a->name == this->name && a->passwd == this->passwd) {
            cout << "登录成功!" << endl;
            return 1;
        } else {
            a = a->next;
        }
    }
    cout << "密码错误, 请重新输入密码!" << endl;
    return 0;
}


int main() {
    //管理员不可注册,提前写入程序de 
    //默认管理员为ycr,密码是666,可自行修改
    //请注意每次一定要按要求输入,避免死循环
    string n, p;
    int cnt = 100;  //可注册100个账户
    while (cnt--) {
        int ch;
        cout << "请选择: 1.登录       2.注册" << endl;
        cin >> ch;
        if (ch == 1) {
            cout << "请先输入账户:";
            cin >> n;
            cout << "请输入密码:";
            cin >> p;
            Login l(n, p); 
            act *a = manager.getHead();
            int flag = l.signIn(a);
            if (flag == 1) break;   //登录成功
        }
        if (ch == 2) {
            cout << "请先输入账户:";
            cin >> n;
            cout << "请输入密码:";
            cin >> p;
            manager.reg(n, p);  // 注册账户
            cout <<  "注册成功!" << endl;
        }
    } 
    
    //下面已登录
    cout<<endl<<"                        欢迎使用图书管理系统"<<endl<<endl;
	int choice=1;
	while(choice!=0)
	{
		displaymain();
		cin>>choice;
		switch(choice)
		{
			case 1:	find();break;
			case 2: head=borrow(head);break;
			case 3: head=back(head);break;
			case 4:	manage();break;
			case 5:	print(head);break;
			case 6:	choice=0;break;
			default:cout<<"输入有误，请重新输入!"<<endl;break;	
 
		}
	}
	cout<<"	***************************************************"<<endl;
	cout<<"	*                                                 *"<<endl;
	cout<<"	*                  感谢您的使用!                  *"<<endl;
	cout<<"	*                                                 *"<<endl;
	cout<<"	*                                                 *"<<endl;
	cout<<"	***************************************************"<<endl;
    return 0;
}

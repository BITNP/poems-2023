#include<stdio.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 100
typedef struct//定义栈的结构 
{
	char* base;
	char* top;//字符指针（在操作符栈中使用） 
	int* ba;
	int* to;//整型指针（在操作数栈中使用）
	int Stacksize;
}SpStack;
void InitStack(SpStack &S)//初始化栈 
{
    S.base=(char *)malloc(STACK_INIT_SIZE*sizeof(char));
    S.ba=(int *)malloc(STACK_INIT_SIZE*sizeof(int));
    if(!S.base||!S.ba) return;
    S.top=S.base;
    S.to=S.ba;
    S.Stacksize=STACK_INIT_SIZE;
    return;
}
void Push_1(SpStack &S,int e)//在操作数栈栈顶加入操作数 
{
	if(S.top-S.base>=S.Stacksize)
	{
	    S.to=(int*)realloc(S.base,(S.Stacksize+10)*sizeof(int));
	    if(!S.to) return;
	    S.to=S.ba+S.Stacksize;
	    S.Stacksize+=10;
    }
    *S.to=e;
	S.to++;
}
void Push(SpStack &S,char e)//在操作符栈栈顶加入操作符 
{
	if(S.top-S.base>=S.Stacksize)
	{
	    S.top=(char*)realloc(S.base,(S.Stacksize+10)*sizeof(char));
	    if(!S.top) return;
	    S.top=S.base+S.Stacksize;
	    S.Stacksize+=10;
    }
    *S.top=e;
	S.top++;
}
char Pop(SpStack &S)//在操作数栈栈顶取出操作数
{
	char e;
	if(S.top==S.base)return'w';
	else
	{
		e=*(S.top-1);
		S.top--;
	}
	return e;
}
int Pop_1(SpStack &S)//在操作符栈栈顶取出操作符 
{
	int e;
	if(S.to==S.ba)return'w';
	else
	{
		e=*(S.to-1);
		S.to--;
	}
	return e;
} 
char GetTop(SpStack S)//返回操作符栈栈顶的符号 
{
	
	if(S.base==S.top){}
	else
	{
	char e=*(S.top-1);
	return e;}
}
int GetTop_1(SpStack S)//返回操作数栈栈顶的数值 
{
	
	if(S.ba==S.to){}
	else
	{
	int e=*(S.to-1);
	return e;}
}
char Precede(char a,char b)//判断操作符之间的优先级关系 
{
	char ar[10]={'+','-','*','/','(',')','#','%','^','!'},br[10]={'+','-','*','/','%','^','!','(',')','='};
	int i,j;
	for(i=0;i<=9;i++)
	{if(a==ar[i])//得到字符a的编号 
    { 
	    break;
	}
    }
	for(j=0;j<=9;j++)
	{if(b==br[j])//获取字符b的编号 
    { 
	    break;
	}
    }
    char ch[10][10]=
	{//表示运算符优先关系的字符数组 
		{'>','>','<','<','<','<','<','<','>','>'}, 
		{'>','>','<','<','<','<','<','<','>','>'},
		{'>','>','>','>','>','<','<','<','>','>'},
		{'>','>','>','>','>','<','<','<','>','>'},
		{'<','<','<','<','<','<','<','<','=','>'},
		{'>','>','>','>','>','>','>','>','>','>'},
		{'<','<','<','<','<','<','<','<','<','<'},
		{'>','>','>','>','>','<','<','<','>','>'},
		{'>','>','>','>','>','>','>','<','>','>'},
		{'>','>','>','>','>','>','>','<','>','>'},
	};
	return ch[i][j];//返回值为对应的优先关系 
}
int Operate(int a,char x,int b)//进行运算 
{
	int c;
	switch(x)
	{
		case'+':
			c=a+b;
			break;
		case'-':
			c=a-b;
			break;
		case'*':
			c=a*b;
			break;
		case'/':
			c=a/b;
			break;
		case'%':
			c=a%b;
			break;
		case'^':
			int i;c=1;
			for(i=1;i<=b;i++)
			{
				c*=a;
			}
			break;
	} 
	return c;
}
int Operate_1(int a)//进行阶乘运算 
{
	int x=1,i;
	for(i=a;i>1;i--)
	{
		x*=i;
	}
	return x;
}
int main()
{
	printf("这是一个用C语言编写的运算表达式计算器，可实现四则运算、乘方、取余、阶乘运算，支持加入括号以区分运算优先级\n"); 
	printf("请输入运算表达式，以等号结束，例如：(12-98)*37-23*(34^2-(6!%11+95))=\n");
	char c,x;
	int a,b;
	SpStack NUM,CH;
	InitStack(NUM);
	InitStack(CH);
	Push(CH,'#');
	c=getchar();
	int i=0;
	while(i==0||NUM.to!=NUM.ba+1)
	{
		if(c!='+'&&c!='-'&&c!='*'&&c!='/'&&c!='('&&c!=')'&&c!='='&&c!='%'&&c!='^'&&c!='!')//若c不是操作符 
		{
			int j=1;
			int y=c-48;
			while(b=getchar())//本循环可以将计算器支持的位数扩展为任意位 
			{
			if(b!='+'&&b!='-'&&b!='*'&&b!='/'&&b!='('&&b!=')'&&b!='='&&b!='%'&&b!='^'&&b!='!')
			{
		        y=y*10+(b-48);
		    }
		    else 
			{c=b;break;}
		    }
		    Push_1(NUM,y);
		}
		else
		{
			switch(Precede(GetTop(CH),c))//判断c与操作符栈栈顶的优先级关系 
			{
				case'<':
					Push(CH,c);
					c=getchar();
					break;
				case'=':
					Pop(CH);
					c=getchar();
					break;
				case'>':
					x=Pop(CH);
					if(x=='!')
					{
						a=Pop_1(NUM);
						Push_1(NUM,Operate_1(a));
						if(c=='=')i++;//表达式结束了，跳出循环
					    break;
					}
					else
					{
					a=Pop_1(NUM);b=Pop_1(NUM);
					if(x=='/'||x=='-'||x=='%'||x=='^')
					{
						Push_1(NUM,Operate(b,x,a));
					}
					else Push_1(NUM,Operate(a,x,b));
					if(c=='=')i++;//表达式结束了，跳出循环 
					break;
				    }
			}
		}
	}
	printf("%d\n",GetTop_1(NUM));//在操作数栈取得最终结果 
}

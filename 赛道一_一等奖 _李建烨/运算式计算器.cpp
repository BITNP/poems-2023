#include<stdio.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 100
typedef struct//����ջ�Ľṹ 
{
	char* base;
	char* top;//�ַ�ָ�루�ڲ�����ջ��ʹ�ã� 
	int* ba;
	int* to;//����ָ�루�ڲ�����ջ��ʹ�ã�
	int Stacksize;
}SpStack;
void InitStack(SpStack &S)//��ʼ��ջ 
{
    S.base=(char *)malloc(STACK_INIT_SIZE*sizeof(char));
    S.ba=(int *)malloc(STACK_INIT_SIZE*sizeof(int));
    if(!S.base||!S.ba) return;
    S.top=S.base;
    S.to=S.ba;
    S.Stacksize=STACK_INIT_SIZE;
    return;
}
void Push_1(SpStack &S,int e)//�ڲ�����ջջ����������� 
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
void Push(SpStack &S,char e)//�ڲ�����ջջ����������� 
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
char Pop(SpStack &S)//�ڲ�����ջջ��ȡ��������
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
int Pop_1(SpStack &S)//�ڲ�����ջջ��ȡ�������� 
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
char GetTop(SpStack S)//���ز�����ջջ���ķ��� 
{
	
	if(S.base==S.top){}
	else
	{
	char e=*(S.top-1);
	return e;}
}
int GetTop_1(SpStack S)//���ز�����ջջ������ֵ 
{
	
	if(S.ba==S.to){}
	else
	{
	int e=*(S.to-1);
	return e;}
}
char Precede(char a,char b)//�жϲ�����֮������ȼ���ϵ 
{
	char ar[10]={'+','-','*','/','(',')','#','%','^','!'},br[10]={'+','-','*','/','%','^','!','(',')','='};
	int i,j;
	for(i=0;i<=9;i++)
	{if(a==ar[i])//�õ��ַ�a�ı�� 
    { 
	    break;
	}
    }
	for(j=0;j<=9;j++)
	{if(b==br[j])//��ȡ�ַ�b�ı�� 
    { 
	    break;
	}
    }
    char ch[10][10]=
	{//��ʾ��������ȹ�ϵ���ַ����� 
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
	return ch[i][j];//����ֵΪ��Ӧ�����ȹ�ϵ 
}
int Operate(int a,char x,int b)//�������� 
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
int Operate_1(int a)//���н׳����� 
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
	printf("����һ����C���Ա�д��������ʽ����������ʵ���������㡢�˷���ȡ�ࡢ�׳����㣬֧�ּ��������������������ȼ�\n"); 
	printf("������������ʽ���ԵȺŽ��������磺(12-98)*37-23*(34^2-(6!%11+95))=\n");
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
		if(c!='+'&&c!='-'&&c!='*'&&c!='/'&&c!='('&&c!=')'&&c!='='&&c!='%'&&c!='^'&&c!='!')//��c���ǲ����� 
		{
			int j=1;
			int y=c-48;
			while(b=getchar())//��ѭ�����Խ�������֧�ֵ�λ����չΪ����λ 
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
			switch(Precede(GetTop(CH),c))//�ж�c�������ջջ�������ȼ���ϵ 
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
						if(c=='=')i++;//���ʽ�����ˣ�����ѭ��
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
					if(c=='=')i++;//���ʽ�����ˣ�����ѭ�� 
					break;
				    }
			}
		}
	}
	printf("%d\n",GetTop_1(NUM));//�ڲ�����ջȡ�����ս�� 
}

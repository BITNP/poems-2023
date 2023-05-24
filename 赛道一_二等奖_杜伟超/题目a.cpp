#include<stdio.h>
#include<stdlib.h>
#include<math.h>
char OP[8]={'+','-','*','/','^','(',')','='};
int COMOP[8][8]={ 1, 1,-1,-1,-1,-1, 1, 1,
				  1, 1,-1,-1,-1,-1, 1, 1,
				  1, 1, 1, 1,-1,-1, 1, 1,
				  1, 1, 1, 1,-1,-1, 1, 1,
				  1, 1, 1, 1, 1,-1, 1, 1,
				 -1,-1,-1,-1,-1,-1, 0, 2,
				  1, 1, 1, 1, 1, 2, 1, 1,
				 -1,-1,-1,-1,-1,-1, 2, 0 };

typedef struct node{
	float data;
	char elem;
	struct node *next;
}Stack,*pStack;

void InitStack(pStack &S){
	S=(pStack)malloc(sizeof(Stack));
	S->next=NULL;
}

void Push1(pStack &S,char ch){
	pStack p;
	p=(pStack)malloc(sizeof(Stack));
	p->elem=ch;
	p->next=S->next;
	S->next=p;
}

void Push2(pStack &S,float n){
	pStack p;
	p=(pStack)malloc(sizeof(Stack));
	p->data=n;
	p->next=S->next;
	S->next=p;
}

int In(char ch,char OP[8]){
	int i;
	for(i=0;i<8;i++)
		if(ch==OP[i]) return(1);
	return(0);
}

int Precede(char c1,char c2){
	int i,j;
	for(i=0;i<8;i++)
		if(c1==OP[i]) break;
	for(j=0;j<8;j++)
		if(c2==OP[j]) break;
	return(COMOP[i][j]);
}

void Pop1(pStack &S,char &ch){
	pStack p=S->next;
	ch=p->elem;
	S->next=p->next;
	free(p);
}

void Pop2(pStack &S,float &n){
	pStack p=S->next;
	n=p->data;
	S->next=p->next;
	free(p);
}

float Operate(float a,char theta,float b){
	if(theta=='+') return(a+b);
	if(theta=='-') return(a-b);
	if(theta=='*') return(a*b);
	if(theta=='/') return(a/b);
	if(theta=='^') return(pow(a,b));
} 

int main(){
	printf("本计算器支持负数,小数运算;支持加减乘除,乘方开方(^)运算;计算结果均保留6位小数.\n"); 
	printf("请输入一个算式,如果算式中含有括号,请使用()(支持多个括号使用),并以等号结尾:\n"); 
	pStack OPTR,OPND;
	InitStack(OPTR);	Push1(OPTR,'=');
	InitStack(OPND);
	char c0,c,x,theta; float n,a,b; int flag=1;
	c0=c='-';c=getchar();
	while(c!='=' || OPTR->next->elem!='='){
		if(c=='-'&&In(c0,OP)&&c0!=')'){
			flag=-1;
			c0=c;c=getchar();
		}
		if(!In(c,OP)){
			n=c-'0'; c0=c;c=getchar();
			while(!In(c,OP)&&c!='.'){
				n=n*10+c-'0';
				c0=c;c=getchar();
			}
			if(c=='.'){
				int count=1;c0=c;c=getchar();
				while(!In(c,OP)){
					n=n+(c-'0')/(pow(10,count));
					count++;c0=c;c=getchar();
				}
			}
			Push2(OPND,n*flag);
			flag=1;
		}
		else{
			switch(Precede(OPTR->next->elem,c)){
				case -1:
					Push1(OPTR,c);	c0=c;c=getchar();
					break;
				case 0:
					Pop1(OPTR,x);	c0=c;c=getchar();
					break;
				case 1:
					Pop1(OPTR,theta);
					Pop2(OPND,b); Pop2(OPND,a);
					if(theta=='/'&&b==0){
						printf("输入有误\n");
						return(0);
					} 
					Push2(OPND,Operate(a,theta,b));
					break;
				default:
					printf("输入有误\n");return(0);
			}
		}	
	}
	printf("%f\n",OPND->next->data);
	return(0);
}

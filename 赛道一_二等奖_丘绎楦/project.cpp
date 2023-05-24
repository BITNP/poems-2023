#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <easyx.h>
#include <math.h>

double A_und(int n, double* a, double ave);
double B_und(double und);
double S_und(double a, double b);
void cul();
void phy();
void button(int x, int y, int w, int h, TCHAR* text);
char anniu();

int main() {
	char a = 0;
	while (1)
	{
		a=anniu();
		closegraph();
		switch (a) {
		case '1':cul(); break;
		case '2':phy(); break;
		case '3':break;
		default:;
		}
		if (a == '3')
		{
			break;
		}
	}
	return 0;
}

double A_und(int n, double* a, double ave)
{
	double ua = 0.0;
	double record = 0.0;
	for (int i = 0; i < n; i++)
	{
		record += pow((a[i] - ave), 2);
	}
	ua = sqrt(record / (n * (n - 1)));
	return ua;
}

double B_und(double und)
{
	double ub = 0.0;
	ub = und / sqrt(3);
	return ub;
}

double S_und(double a, double b)
{
	double u = 0.0;
	u = sqrt(a * a + b * b);
	return u;
}

void cul()
{
	char n=0;
	double ans = 0;
	double a = 0, b = 0;
	int yyt = 0;
	while (1)
	{
		system("cls");
		printf("|-------计算机-------|\n");
		printf("|       0 退出       |\n");
		printf("|       1 加法 +     |\n");
		printf("|       2 减法 -     |\n");
		printf("|       3 乘法 *     |\n");
		printf("|       4 除法 /     |\n");
		printf("|       5 乘方 ^n    |\n");
		printf("|       6 开方 √     |\n");
		printf("|--------------------|\n");
		printf("请输入菜单编号:");
		n=_getche();
		system("cls");
		switch (n)
		{
		case '1':
			
			printf("---加法运算---\n");
			if (yyt == 1)
			{
				printf("上一次运算结果: 【%g】\n", ans);
			}
			printf("输入两个数:");
			scanf_s("%lf%lf", &a, &b);
			ans = a + b;
			printf("%g+%g=%g",a,b,ans);
			printf("\n\n任意键继续使用计算机（输入‘0’退出）");
			n = _getche();
			break;
		case '2':
			printf("---减法运算---\n");
			if (yyt == 1)
			{
				printf("上一次运算结果: 【%g】\n", ans);
			}
			printf("输入两个数:");
			scanf_s("%lf%lf", &a, &b);
			ans = a - b;
			printf("%g-%g=%g", a, b, ans);
			printf("\n\n任意键继续使用计算机（输入‘0’退出）");
			n = _getche();
			break;
		case '3':
			printf("---乘法运算---\n");
			if (yyt == 1)
			{
				printf("上一次运算结果: 【%g】\n", ans);
			}
			printf("输入两个数:");

			scanf_s("%lf%lf", &a, &b);
			ans = a * b;
			printf("%g*%g=%g", a, b, ans);
			printf("\n\n任意键继续使用计算机（输入‘0’退出）");
			n = _getche();
			break;
		case '4':
			printf("---除法运算---\n");
			if (yyt == 1)
			{
				printf("上一次运算结果: 【%g】\n", ans);
			}
			printf("输入两个数:");
			scanf_s("%lf%lf", &a, &b);
			ans = a / b;
			printf("%g/%g=%g", a, b, ans);
			printf("\n\n任意键继续使用计算机（输入‘0’退出）");
			n = _getche();
			break;
		case '5':
			printf("---乘方运算---\n");
			if (yyt == 1)
			{
				printf("上一次运算结果: 【%g】\n", ans);
			}
			printf("输入要乘方的数:");
			scanf_s("%lf", &a);
			printf("几次方：");
			scanf_s("%lf", &b);
			ans = pow(a,b);
			printf("%g^%g=%g", a, b, ans);
			printf("\n\n任意键继续使用计算机（输入‘0’退出）");
			n = _getche();
			break;
		case '6':
			printf("---开方运算---\n");
			if (yyt == 1)
			{
				printf("上一次运算结果: 【%g】\n", ans);
			}
			printf("输入要开方的数:");
			scanf_s("%lf", &a);
			ans = sqrt(a);
			printf("√%g=%g", a, ans);
			printf("\n\n任意键继续使用计算机（输入‘0’退出）");
			n = _getche();
			break;
		case '0':
			break;
		default:break;
		}
		if (n == '0')
		{
			system("cls");
			break;
		}
		yyt = 1;
	}
}

void phy()
{
	while (1)
	{
		char j = 1;
		int n = 0;
		double* p = 0, ans = 0.0;
		double a[50] = { 0 };
		double sum = 0.0, srms = 0.0, sums = 0.0, und = 0.0;
		system("cls");
		printf("-----物理实验数据处理器-----\n");
		printf("输入数据个数：");
		scanf_s("%d", &n);
		printf("请输入%d个数据:", n);
		for (int i = 0; i < n; ++i)
		{
			scanf_s("%lf", &a[i]);
			sum += a[i];
			srms += pow(a[i], 2);
		}
		printf("请输入仪器不确定度（若无输入‘0’）：");
		scanf_s("%lf", &und);
		ans = sum / n;
		for (int i = 0; i < n; ++i)
		{
			sums += pow(a[i] - ans, 2);
		}
		printf("\n");
		printf("|--------------------\n");
		printf("|平均数          :%10.6lf\n", ans);
		printf("|--------------------\n");
		printf("|方均根数        :%10.6lf\n", sqrt(srms / n));
		printf("|--------------------\n");
		printf("|平均值标准偏差  :%10.6lf\n", sqrt(sums / n / (n + 1)));
		printf("|--------------------\n");
		printf("|A类不确定度     :%10.6lf\n", A_und(n, a, sum / n));
		printf("|--------------------\n");
		printf("|B类不确定度     :%10.6lf\n", B_und(und));
		printf("|--------------------\n");
		printf("|标准不确定度    :%10.6lf\n", S_und(A_und(n, a, sum / n), B_und(und)));
		printf("|--------------------\n欢迎再次使用！！！\n\n");

		printf("\n\n任意键继续使用物理实验数据处理器（输入‘0’退出）");
		j = _getche();
		if (j == '0')
		{
			system("cls");
			break;
		}
	}
}

void button(int x, int y, int w, int h, TCHAR* text)
{
	setbkmode(TRANSPARENT);
	setfillcolor(RED);
	fillroundrect(x, y, x + w, y + h, 10, 10);
	int textx = x + (w - textwidth(text)) / 2;
	int texty = y + (h - textheight(text)) / 2;
	outtextxy(textx, texty, text);
}
char anniu()
{
	int yyt = 0;
	TCHAR s1[50] = L"计算机";
	TCHAR s2[50] = L"物理实验数据处理器";
	TCHAR s3[50] = L"退出";
	initgraph(520, 360);
	setbkcolor(YELLOW);
	cleardevice();
	button(110, 50, 290, 50, s1);
	button(110, 150, 290, 50, s2);
	button(110, 250, 290, 50, s3);
	ExMessage msg;
	while (1)
	{
		if (peekmessage(&msg, EM_MOUSE)) 
		{

			switch (msg.message)
			{
				case WM_LBUTTONDOWN:
					if (msg.x >= 110 && msg.x <= 110 + 290 && msg.y >= 50 && msg.y <= 50 + 50)
					{
						yyt = 1;
						break;
					}
					if (msg.x >= 110 && msg.x <= 110 + 290 && msg.y >= 150 && msg.y <= 150 + 50)
					{
						yyt = 2;
						break;
					}
					if (msg.x >= 110 && msg.x <= 110 + 290 && msg.y >= 250 && msg.y <= 250 + 50)
					{
						yyt = 3;
						break;
					}
					break;
				default:
					break;
			}
			if (yyt == 1 || yyt == 2 || yyt == 3)
			{
				break;
			}
		}
	}
	if (yyt == 1)
	{
		return '1';
	}
	else if (yyt == 2)
	{
		return '2';
	}
	else if (yyt == 3)
	{
		return '3';
	}
}
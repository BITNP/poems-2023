#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 清屏函数
void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    printf("\033[H\033[J");
#endif
}

// 等待用户输入任意键继续 
void any_key_continue() {
    printf("\033[1;36m按任意键继续...\033[0m");
    getchar();
    getchar();
}

// 封装四则运算函数 
void calculate() {
    clear_screen();
    printf("\033[1;33m====== 计算 ======\033[0m\n\n");

    double num1, num2, result;
    char symbol;

    printf("请输入表达式 格式：正负号数1 运算符 正负号数2(正号可以省略,不要加括号):\n");
    scanf("%lf %c %lf", &num1, &symbol, &num2);

    switch (symbol) {
        case '+': 
            result = num1 + num2; 
            break;
        case '-': 
            result = num1 - num2; 
            break;
        case '*': 
            result = num1 * num2; 
            break;
        case '/': 
            result = num1 / num2; 
            break;
        case '^': 
            result = pow(num1, num2); 
            break;
        default: {
            printf("\033[1;31m输入错误，请重新输入\033[0m\n");
            any_key_continue();
            return;
        }
    }

    printf("\033[1;32m结果为：%lf\033[0m\n", result);

    any_key_continue();
}

// 封装解一元二次方程函数 
void quadratic_equation() {
    clear_screen();
    printf("\033[1;33m====== 解一元二次方程 ======\033[0m\n\n");

    double a, b, c;
    printf("请输入一元二次方程的三个系数，格式为：ax2 + bx + c = 0\n");
    printf("a = ");
    scanf("%lf", &a);
    printf("b = ");
    scanf("%lf", &b);
    printf("c = ");
    scanf("%lf", &c);

    if (a == 0) {
        printf("\033[1;31m你这不是一元二次方程！\033[0m\n");
        any_key_continue();
        return;
    }

    double delta = b * b - 4 * a * c;

    if (delta < 0) {
        printf("\033[1;31m此方程无实数解！\033[0m\n");
        any_key_continue();
        return;
    }

    double x1 = (-b + sqrt(delta)) / (2 * a);
    double x2 = (-b - sqrt(delta)) / (2 * a);

    if (delta == 0) {
        printf("\033[1;32m此方程有两个相同的实数解\nx1 = x2 = %lf\033[0m\n", x1);
    } else {
        printf("\033[1;32m此方程有两个不同的实数解\nx1 = %lf, x2 = %lf\033[0m\n", x1, x2);
    }

    any_key_continue();
}

// 计算一组数字的平均值和方差
void calculate_average_variance() {
    clear_screen();
    printf("\033[1;33m====== 计算平均值和方差 ======\033[0m\n\n");

    int n;
    printf("请输入数字的个数：");
    scanf("%d", &n);

    if (n <= 0) {
        printf("\033[1;31m数字的个数必须是正整数！\033[0m\n");
        any_key_continue();
        return;
    }

    double sum = 0, sum2 = 0;
    double num;

    for (int i = 0; i < n; i++) {
        printf("请输入第%d个数字：", i + 1);
        scanf("%lf", &num);
        sum += num;
        sum2 += num * num;
    }

    double mean = sum / n;
    double variance = sum2 / n - mean * mean;

    printf("\033[1;32m数字的平均值为：%lf, 方差为：%lf\033[0m\n", mean, variance);

    any_key_continue();
}

int main() {
    while (1) {
        clear_screen();
        printf("\033[1;36m========== 小计算器 ==========\033[0m\n\n");
        printf("支持的运算符有：+ - * / ^\n");
        printf("1. 计算\n");
        printf("2. 解一元二次方程\n");
        printf("3. 计算平均值和方差\n");
        printf("4. 退出\n\n");

        int choice;
        printf("请选择：");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                calculate(); 
                break;
            case 2: 
                quadratic_equation(); 
                break;
            case 3: 
                calculate_average_variance(); 
                break;
            case 4: 
                clear_screen();
                printf("\033[1;36m再见!\033[0m\n");
                return 0;
            default: {
                printf("\033[1;31m输入有误，请重新输入\033[0m\n");
                any_key_continue();
                break;
            }
        }
    }
}






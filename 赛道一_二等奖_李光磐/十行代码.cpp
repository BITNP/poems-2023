#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ��������
void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    printf("\033[H\033[J");
#endif
}

// �ȴ��û�������������� 
void any_key_continue() {
    printf("\033[1;36m�����������...\033[0m");
    getchar();
    getchar();
}

// ��װ�������㺯�� 
void calculate() {
    clear_screen();
    printf("\033[1;33m====== ���� ======\033[0m\n\n");

    double num1, num2, result;
    char symbol;

    printf("��������ʽ ��ʽ����������1 ����� ��������2(���ſ���ʡ��,��Ҫ������):\n");
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
            printf("\033[1;31m�����������������\033[0m\n");
            any_key_continue();
            return;
        }
    }

    printf("\033[1;32m���Ϊ��%lf\033[0m\n", result);

    any_key_continue();
}

// ��װ��һԪ���η��̺��� 
void quadratic_equation() {
    clear_screen();
    printf("\033[1;33m====== ��һԪ���η��� ======\033[0m\n\n");

    double a, b, c;
    printf("������һԪ���η��̵�����ϵ������ʽΪ��ax2 + bx + c = 0\n");
    printf("a = ");
    scanf("%lf", &a);
    printf("b = ");
    scanf("%lf", &b);
    printf("c = ");
    scanf("%lf", &c);

    if (a == 0) {
        printf("\033[1;31m���ⲻ��һԪ���η��̣�\033[0m\n");
        any_key_continue();
        return;
    }

    double delta = b * b - 4 * a * c;

    if (delta < 0) {
        printf("\033[1;31m�˷�����ʵ���⣡\033[0m\n");
        any_key_continue();
        return;
    }

    double x1 = (-b + sqrt(delta)) / (2 * a);
    double x2 = (-b - sqrt(delta)) / (2 * a);

    if (delta == 0) {
        printf("\033[1;32m�˷�����������ͬ��ʵ����\nx1 = x2 = %lf\033[0m\n", x1);
    } else {
        printf("\033[1;32m�˷�����������ͬ��ʵ����\nx1 = %lf, x2 = %lf\033[0m\n", x1, x2);
    }

    any_key_continue();
}

// ����һ�����ֵ�ƽ��ֵ�ͷ���
void calculate_average_variance() {
    clear_screen();
    printf("\033[1;33m====== ����ƽ��ֵ�ͷ��� ======\033[0m\n\n");

    int n;
    printf("���������ֵĸ�����");
    scanf("%d", &n);

    if (n <= 0) {
        printf("\033[1;31m���ֵĸ�����������������\033[0m\n");
        any_key_continue();
        return;
    }

    double sum = 0, sum2 = 0;
    double num;

    for (int i = 0; i < n; i++) {
        printf("�������%d�����֣�", i + 1);
        scanf("%lf", &num);
        sum += num;
        sum2 += num * num;
    }

    double mean = sum / n;
    double variance = sum2 / n - mean * mean;

    printf("\033[1;32m���ֵ�ƽ��ֵΪ��%lf, ����Ϊ��%lf\033[0m\n", mean, variance);

    any_key_continue();
}

int main() {
    while (1) {
        clear_screen();
        printf("\033[1;36m========== С������ ==========\033[0m\n\n");
        printf("֧�ֵ�������У�+ - * / ^\n");
        printf("1. ����\n");
        printf("2. ��һԪ���η���\n");
        printf("3. ����ƽ��ֵ�ͷ���\n");
        printf("4. �˳�\n\n");

        int choice;
        printf("��ѡ��");
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
                printf("\033[1;36m�ټ�!\033[0m\n");
                return 0;
            default: {
                printf("\033[1;31m������������������\033[0m\n");
                any_key_continue();
                break;
            }
        }
    }
}






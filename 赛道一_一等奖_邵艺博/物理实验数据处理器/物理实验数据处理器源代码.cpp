#include <iostream>
#include <regex>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>

using namespace std;

/*�û�������*/
class gui{
	public:
		void append(string);		/*�������*/
		void print();				/*ˢ�»���*/
		void erase();				/*�������һ��*/
		void append_head();			/*��ӱ���1*/
	private:
		vector<string> canvas; 		/*���廭��*/
};

/*ˢ�»���*/
void gui::print() {
	system("cls");
	for(auto it = canvas.begin(); it != canvas.end(); it++) {
		cout << *it << endl;
	}
	return;
}

void gui::erase() {
	canvas.erase(canvas.end());
	return;
}

/*�������*/
void gui::append(string line) {
	canvas.push_back(line);
	return;
}


/*��ӱ���*/
void gui::append_head(){	
	append("                                                        ");
	append(" =====================================================  ");
	append(" �U             ʮ�д�����ս��������Ʒ                �U");
	append(" =====================================================  ");
	append("������Ҫ���е����ݴ���                                ");	
	append("   1.���㲻ȷ���ȣ�ʵ���׼�ƽ��ֵ                   ");
	append("   2.ͨ����С���˷����Իع�                             ");
	append("                                                        ");		
	append("   �Ŵ�����: ctrl + '='       ��С����: ctrl + '-'      ");
	append("                                                        ");
	append("                                                        ");
	return;
}


/* ƽ��ֵ */
double mean(vector<double> arr) {
    double result = 0;
    for(auto it = arr.begin(); it != arr.end(); it++) result += *it;
    return result / arr.size();
}

/*������� */
double variance(vector<double> arr) {
    double result = 0, m = mean(arr);
    for(auto it = arr.begin(); it != arr.end(); it++) *it = pow(*it - m,2);
    for(auto it = arr.begin(); it != arr.end(); it++) result += *it;
    return result / arr.size();
}

/* A���׼��ȷ���� */
double uncertainty_a(vector<double> arr) {
	return sqrt(variance(arr) / (arr.size() - 1) );
}

/* ʵ���׼�� */
double std_error(vector<double> arr) {
	return uncertainty_a(arr) * sqrt(arr.size());
}

/* B���׼��ȷ���� */
double uncertainty_b(double ins,double k) {
	return ins / k;
}

/* �ϳɱ�׼��ȷ���� */
double uncertainty_c(double ua,double ub) {
	return sqrt(ua*ua+ub*ub);
}

/* ��С���˷����Իع�-б�� */
double least_squares_w(vector<double> arr_x, vector<double> arr_y) {
	double xm = mean(arr_x), up = 0, down = 0;
	for(auto it_x = arr_x.begin(), it_y = arr_y.begin(); it_x != arr_x.end(); it_x++, it_y++) {
		up += *it_y * (*it_x - xm);
	}
	for(auto it_x = arr_x.begin(); it_x != arr_x.end(); it_x++) {
		down += pow(*it_x, 2) - pow(xm, 2);
	}
	return up / down;
}

/* ��С���˷����Իع�-�ؾ� */
double least_squares_b(vector<double> arr_x, vector<double> arr_y) {
	return mean(arr_y) - least_squares_w(arr_x, arr_y) * mean(arr_x);
}

/* ���㲻ȷ���Ƚ��� */
void uncertainty() {
	gui gui_1;
	double k,ins;
	vector<double> arr;
	string input;
	for(int i = 1; ; i++){
		gui_1.append("�������" + to_string(i) + "��ֵ, ����������ַ��˳�");
		gui_1.print();
		getline(cin, input);
		gui_1.erase();
		if( regex_match(input,regex("(-?\\d+)(\\.\\d+)?")) ) {
			gui_1.append(to_string(i) + ":  " + input);
			arr.push_back(stod(input));
		}
		else break;
	}
	for(; !regex_match(input,regex("(-?\\d+)(\\.\\d+)?"));){
		gui_1.append("������ins");
		gui_1.print();
		getline(cin,input);
		gui_1.erase();
	}
	ins = stod(input);
	gui_1.append("ins = " + to_string(ins));
	gui_1.append("k = " + to_string(sqrt(3)));
	gui_1.append("ƽ��ֵ:" + to_string(mean(arr)) );
	gui_1.append("ʵ���׼��Sx:" + to_string(std_error(arr)) );
	gui_1.append("A���׼��ȷ����ua:" + to_string(uncertainty_a(arr)) );
	gui_1.append("B���׼��ȷ����ub:" + to_string(uncertainty_b(ins, sqrt(3))) );
	gui_1.append("�ϳɱ�׼��ȷ����uc:" + to_string(uncertainty_c(uncertainty_a(arr), uncertainty_b(ins, sqrt(3)))) );
	gui_1.append("����b�˳�");
	gui_1.print();
	for(string i = "0";i[0] != 'b';){
		getline(cin,i);
	}
	return ;
}


void least_squares(){
	gui gui_1;
	vector<double> arr_x, arr_y;
	string input;
	char c[] = {'x', 'y'};
	for(int j = 0; j<2; j++){
		for(int i = 1; ; i++){
			gui_1.append("�������" + to_string(i) + "��" + c[j] + "ֵ, ����������ַ��˳�");
			gui_1.print();
			getline(cin, input);
			gui_1.erase();
			if( regex_match(input,regex("(-?\\d+)(\\.\\d+)?")) ) {
				gui_1.append(c[j] + to_string(i) + " :  " + input);
				j == 0 ? arr_x.push_back(stod(input)) : arr_y.push_back(stod(input));
			}
			else break;
		}
	}
	if (arr_x.size() != arr_y.size() ){
		gui_1.append("x,y���������");
	}
	else {
		double k,b;
		k = least_squares_w(arr_x, arr_y);
		b = least_squares_b(arr_x, arr_y);
		gui_1.append("б��Ϊ��" + to_string(k) );
		gui_1.append("y��ؾ�Ϊ��" + to_string(b) );
	}
	gui_1.append("����b�˳�");
	gui_1.print();
	for(string i = "0";i[0] != 'b';){
		getline(cin,i);
	}
	return;
}

main() {
	gui gui_main;
	gui_main.append_head();
	string conl;
	while(1){
		gui_main.print();
		getline(cin, conl);
		switch(conl[0]){
			case '1' : uncertainty() ; break;
			case '2' : least_squares() ; break;
		}
	}
}

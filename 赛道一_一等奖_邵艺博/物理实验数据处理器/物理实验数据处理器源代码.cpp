#include <iostream>
#include <regex>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>

using namespace std;

/*用户界面类*/
class gui{
	public:
		void append(string);		/*添加内容*/
		void print();				/*刷新画面*/
		void erase();				/*擦除最后一行*/
		void append_head();			/*添加标题1*/
	private:
		vector<string> canvas; 		/*定义画布*/
};

/*刷新画面*/
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

/*添加内容*/
void gui::append(string line) {
	canvas.push_back(line);
	return;
}


/*添加标题*/
void gui::append_head(){	
	append("                                                        ");
	append(" =====================================================  ");
	append(" ║             十行代码挑战赛参赛作品                ║");
	append(" =====================================================  ");
	append("输入你要进行的数据处理：                                ");	
	append("   1.计算不确定度，实验标准差，平均值                   ");
	append("   2.通过最小二乘法线性回归                             ");
	append("                                                        ");		
	append("   放大字体: ctrl + '='       缩小字体: ctrl + '-'      ");
	append("                                                        ");
	append("                                                        ");
	return;
}


/* 平均值 */
double mean(vector<double> arr) {
    double result = 0;
    for(auto it = arr.begin(); it != arr.end(); it++) result += *it;
    return result / arr.size();
}

/*方差计算 */
double variance(vector<double> arr) {
    double result = 0, m = mean(arr);
    for(auto it = arr.begin(); it != arr.end(); it++) *it = pow(*it - m,2);
    for(auto it = arr.begin(); it != arr.end(); it++) result += *it;
    return result / arr.size();
}

/* A类标准不确定度 */
double uncertainty_a(vector<double> arr) {
	return sqrt(variance(arr) / (arr.size() - 1) );
}

/* 实验标准差 */
double std_error(vector<double> arr) {
	return uncertainty_a(arr) * sqrt(arr.size());
}

/* B类标准不确定度 */
double uncertainty_b(double ins,double k) {
	return ins / k;
}

/* 合成标准不确定度 */
double uncertainty_c(double ua,double ub) {
	return sqrt(ua*ua+ub*ub);
}

/* 最小二乘法线性回归-斜率 */
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

/* 最小二乘法线性回归-截距 */
double least_squares_b(vector<double> arr_x, vector<double> arr_y) {
	return mean(arr_y) - least_squares_w(arr_x, arr_y) * mean(arr_x);
}

/* 计算不确定度界面 */
void uncertainty() {
	gui gui_1;
	double k,ins;
	vector<double> arr;
	string input;
	for(int i = 1; ; i++){
		gui_1.append("请输入第" + to_string(i) + "个值, 输入任意非字符退出");
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
		gui_1.append("请输入ins");
		gui_1.print();
		getline(cin,input);
		gui_1.erase();
	}
	ins = stod(input);
	gui_1.append("ins = " + to_string(ins));
	gui_1.append("k = " + to_string(sqrt(3)));
	gui_1.append("平均值:" + to_string(mean(arr)) );
	gui_1.append("实验标准差Sx:" + to_string(std_error(arr)) );
	gui_1.append("A类标准不确定度ua:" + to_string(uncertainty_a(arr)) );
	gui_1.append("B类标准不确定度ub:" + to_string(uncertainty_b(ins, sqrt(3))) );
	gui_1.append("合成标准不确定度uc:" + to_string(uncertainty_c(uncertainty_a(arr), uncertainty_b(ins, sqrt(3)))) );
	gui_1.append("输入b退出");
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
			gui_1.append("请输入第" + to_string(i) + "个" + c[j] + "值, 输入任意非字符退出");
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
		gui_1.append("x,y数量不相等");
	}
	else {
		double k,b;
		k = least_squares_w(arr_x, arr_y);
		b = least_squares_b(arr_x, arr_y);
		gui_1.append("斜率为：" + to_string(k) );
		gui_1.append("y轴截距为：" + to_string(b) );
	}
	gui_1.append("输入b退出");
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

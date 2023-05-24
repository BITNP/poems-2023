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
		void append(string);	/*添加内容*/
		void print();			/*刷新画面*/
		void append_head();		/*添加标题*/
	private:
		vector<string> canvas; 	/*定义画布*/
};

/*刷新画面*/
void gui::print() {
	system("cls");
	for(auto it = canvas.begin(); it != canvas.end(); it++) {
		cout << *it << endl;
	}
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
	append(" 支持以下运算:                                          ");	
	append("   加 +     减 -    乘 *     除 /     乘方 ^    括号()  ");
	append("   正弦 sin     余弦 cos    正切 tan     自然对数 ln    ");
	append("                                                        ");
	append(" 支持输入pi或e以代替3.14159265和2.71828183              ");
	append("   放大字体: ctrl + '='       缩小字体: ctrl + '-'      ");
	append("                                                        ");
	append("                                                        ");
	return;
}


/*用于计算的函数*/
double cacu(string lin) { 
	smatch matches;
	lin = regex_replace(lin, regex("pi"), "3.14159265");
	lin = regex_replace(lin, regex("e"), "2.71828183");
	
	double r2;			
	for (string lin2; regex_search(lin, matches, regex("\\([lncosita0-9\\^+\\-\\*/\\.]*\\)")); ){
			lin2 = matches[0];			/*提取括号内的数字*/
			lin2.erase(lin2.begin());
			lin2.erase(lin2.end() - 1);
			r2 = cacu(lin2);
			if (isinf(r2) || isnan(r2)) 
				return nan("0");
			lin = regex_replace(lin, regex("\\([lncosita0-9\\^+\\-\\*/\\.]*\\)"), to_string(r2), regex_constants::format_first_only);
		}
		
	double arg;
	for(double arg, a, b;
		regex_search(lin, matches, regex("(sin|cos|tan|ln)(-?\\d+)(\\.\\d+)?")); ) {
		a = stod(matches[2]), b = ( matches[3]=="" ? 0 : stod(matches[3]) );
		arg = a < 0 ? a - b : a + b ;
		switch(matches[1].str()[0]){
			case 's' : arg = sin(arg); break;	/*计算sin*/
			case 'c' : arg = cos(arg); break;	/*计算cos*/
			case 't' : arg = tan(arg); break;	/*计算tan*/
			case 'l' : if(arg <= 0) return nan("0");
						arg = log(arg);  /*计算ln*/
		}									
		lin = regex_replace(lin, regex("(sin|cos|tan|ln)(-?\\d+)(\\.\\d+)?"), to_string(arg), regex_constants::format_first_only);
	}
	
	string ops[] = {"(\\^)", "(\\*|/)", "(\\+|\\-)"};
	for (int i = 0; i < 3; i++ ) {
		for ( double result, a, b, c, d;
			regex_search(lin, matches, regex("(\\d+)(\\.\\d+)?"+ ops[i] + "(\\d+)(\\.\\d+)?")) ;
			lin = regex_replace(lin, regex("(\\d+)(\\.\\d+)?"+ ops[i] + "(\\d+)(\\.\\d+)?"), to_string(result), regex_constants::format_first_only)) {
			c = stod(matches[1]), d = ( matches[2]=="" ? 0 : stod(matches[2]) );
			a = ( c < 0 ? c - d : c + d );
			c = stod(matches[4]), d = ( matches[5]=="" ? 0 : stod(matches[5]) );
			b = ( c < 0 ? c - d : c + d );
			switch(matches[3].str()[0]){
				case '+' : result = a + b; break;
				case '-' : result = a - b; break;
				case '*' : result = a * b; break;
				case '/' : if (b==0) return nan("0");
							result = a / b; break;
				case '^' : if (a==0 && b==0) return nan("0");
							result = pow(a,b);
			}
		}
	}
	cout << lin;
	return stod(lin);
}


/*判断算式是否正确*/
bool check(string lin) {
	regex reg("[\\(\\)]*(-?\\d+)(\\.\\d+)?[\\(\\)]*([\\^+\\-\\*/][\\(\\)]*(-?\\d+)(\\.\\d+)?[\\(\\)]*)*[\\(\\)]*");
	lin = regex_replace(lin, regex("(pi)|(e)"), "1");
	lin = regex_replace(lin, regex("(sin)|(cos)|(ln)|(tan)"), "");
	if (!regex_match(lin, reg)) return false; 		/*判断除括号外的算式是否正确*/
	if (regex_search(lin, regex("(\\(\\))"))) return false;
	while (regex_search(lin, regex("[\\(\\)]"))) {	/*判断括号是否正确*/
		if (regex_search(lin, regex("\\([0-9\\^+\\-\\*/\\.]*\\)"))) {
			lin = regex_replace(lin, regex("\\([0-9\\^+\\-\\*/\\.]*\\)"), "1");
		}
		else{
			return false;
		}
	}
	return true;
}


main() {
	string lin,result_string;
	gui gui1;
	gui1.append_head();
	gui1.print();
	double result;
	while (1){
		getline(cin, lin);								/*输入算式*/
		cout << "计算中……";
		lin = regex_replace(lin, regex("\\s+"), "");	/*删除空格格*/
		if (*(lin.end()-1) == '=')
					lin.erase(lin.end()-1);				/*删除等号*/
		if (check(lin)){								/*检查算式是否正确*/
			result = cacu(lin);	
			if (isinf(result) || isnan(result)){		/*检查算式是否无意义*/
				gui1.append(lin);
				gui1.append("算式无意义");
			}
			else {
				result_string = to_string(result);
				for (auto it = result_string.end()-1; *it == '0'; it--){
					result_string.erase(it);
				}
				if (*(result_string.end()-1) == '.')	/*删除小数点后多余的零*/
					result_string.erase(result_string.end()-1);
				gui1.append(lin + " = " + result_string);
			}
		}
		else {
			gui1.append(lin);
			gui1.append("请输入正确的算式");
		}
		gui1.print();									/*刷新用户界面*/
	}
}

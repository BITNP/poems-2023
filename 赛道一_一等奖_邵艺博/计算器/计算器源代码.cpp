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
		void append(string);	/*�������*/
		void print();			/*ˢ�»���*/
		void append_head();		/*��ӱ���*/
	private:
		vector<string> canvas; 	/*���廭��*/
};

/*ˢ�»���*/
void gui::print() {
	system("cls");
	for(auto it = canvas.begin(); it != canvas.end(); it++) {
		cout << *it << endl;
	}
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
	append(" ֧����������:                                          ");	
	append("   �� +     �� -    �� *     �� /     �˷� ^    ����()  ");
	append("   ���� sin     ���� cos    ���� tan     ��Ȼ���� ln    ");
	append("                                                        ");
	append(" ֧������pi��e�Դ���3.14159265��2.71828183              ");
	append("   �Ŵ�����: ctrl + '='       ��С����: ctrl + '-'      ");
	append("                                                        ");
	append("                                                        ");
	return;
}


/*���ڼ���ĺ���*/
double cacu(string lin) { 
	smatch matches;
	lin = regex_replace(lin, regex("pi"), "3.14159265");
	lin = regex_replace(lin, regex("e"), "2.71828183");
	
	double r2;			
	for (string lin2; regex_search(lin, matches, regex("\\([lncosita0-9\\^+\\-\\*/\\.]*\\)")); ){
			lin2 = matches[0];			/*��ȡ�����ڵ�����*/
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
			case 's' : arg = sin(arg); break;	/*����sin*/
			case 'c' : arg = cos(arg); break;	/*����cos*/
			case 't' : arg = tan(arg); break;	/*����tan*/
			case 'l' : if(arg <= 0) return nan("0");
						arg = log(arg);  /*����ln*/
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


/*�ж���ʽ�Ƿ���ȷ*/
bool check(string lin) {
	regex reg("[\\(\\)]*(-?\\d+)(\\.\\d+)?[\\(\\)]*([\\^+\\-\\*/][\\(\\)]*(-?\\d+)(\\.\\d+)?[\\(\\)]*)*[\\(\\)]*");
	lin = regex_replace(lin, regex("(pi)|(e)"), "1");
	lin = regex_replace(lin, regex("(sin)|(cos)|(ln)|(tan)"), "");
	if (!regex_match(lin, reg)) return false; 		/*�жϳ����������ʽ�Ƿ���ȷ*/
	if (regex_search(lin, regex("(\\(\\))"))) return false;
	while (regex_search(lin, regex("[\\(\\)]"))) {	/*�ж������Ƿ���ȷ*/
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
		getline(cin, lin);								/*������ʽ*/
		cout << "�����С���";
		lin = regex_replace(lin, regex("\\s+"), "");	/*ɾ���ո��*/
		if (*(lin.end()-1) == '=')
					lin.erase(lin.end()-1);				/*ɾ���Ⱥ�*/
		if (check(lin)){								/*�����ʽ�Ƿ���ȷ*/
			result = cacu(lin);	
			if (isinf(result) || isnan(result)){		/*�����ʽ�Ƿ�������*/
				gui1.append(lin);
				gui1.append("��ʽ������");
			}
			else {
				result_string = to_string(result);
				for (auto it = result_string.end()-1; *it == '0'; it--){
					result_string.erase(it);
				}
				if (*(result_string.end()-1) == '.')	/*ɾ��С�����������*/
					result_string.erase(result_string.end()-1);
				gui1.append(lin + " = " + result_string);
			}
		}
		else {
			gui1.append(lin);
			gui1.append("��������ȷ����ʽ");
		}
		gui1.print();									/*ˢ���û�����*/
	}
}

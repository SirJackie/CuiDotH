#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
#include <stack>
using namespace std;

int main(){
	cout << "输入你的代码（输入*****来结束）" << endl; 
	
	int count = 0;
	string value;
	
	vector<string> lines;
	while(getline(cin, value)){
		if(value == "*****"){
			break;
		}
		count += 1;
		lines.push_back(value);
	}	
	
	string quote = "\"";
	string escapedQuote = "\\\"";
	int pos;
	stack<int> s;
	
	for(int i = 0; i < count; i++){
		cout<<i<<endl;
		
		while(1){
			pos = lines[i].find(quote);
			if(pos == -1){
				break;
			}
			s.push(pos);
			lines[i].replace(pos, 1, "QUOTE_NEED_TO_ESCAPE");
		}
		
		cout<<lines[i]<<endl;
		
		
//		lines[i].replace(lines[i].find(quote),1,escapedQuote);
//		lines[i].replace(lines[i].find(quote),1,escapedQuote);
//		lines[i].replace(lines[i].find(quote),1,escapedQuote);
//		lines[i].replace(lines[i].find(quote),1,escapedQuote);
//		lines[i].replace(lines[i].find(quote),1,escapedQuote);
//		cout<<"foundquotestate"<<;
	}
	
	
//	string tab = "    ";
//	
//	for(int i = 0; i < count; i++){
//		while(1){
//			if((pos=lines[i].find(tab)) != string::npos){
//				lines[i].replace(pos,4,""); 
//			}
//			else{
//				break;
//			}
//		}
//	}
	
	
	cout<<"完成！代码："<<endl;
	
	for(int i = 0; i < count; i++){
		cout << lines.at(i) << endl;
	}
	
	
//	ofstream out(".\\Output.txt", ios::in|ios::out);
//	out << "\"";
//	for(int i = 0; i < n; i++){
//		out << lines[n];
//	}
//	out << "\"";
//	
//	out << "Second Line" << endl;
//	out << "Third  Line" << endl;
//	out.close();
}

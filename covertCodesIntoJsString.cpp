#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
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
	
	cout<<"完成！代码："<<endl;
	
	for(int i = 0; i < count; i++){
		cout << lines.at(i) << endl;
	} 
	
//	string quote = "\"";
//	string escapedQuote = "\\\"";
//	int pos;
//	
//	for(int i = 0; i < n; i++){
//		while(1){
//			if((pos=lines[i].find(quote)) != string::npos){
//				lines[i].replace(pos,1,escapedQuote); 
//			}
//			else{
//				break;
//			}
//		}
//	}
//	
//	
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

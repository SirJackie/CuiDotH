#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
using namespace std;

int main(){
	cout << "������Ĵ��루����*****��������" << endl; 
	
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
//	string escapedQuote = "\\\"";
	int pos;
	
	for(int i = 0; i < count; i++){
		cout<<i;
//		while(1){
//			pos = lines[i].find("\"");
//			cout << pos << endl;
//			lines[i].replace(pos,1,"\\\"");
//			
//			pos != -1;
			
//			if(pos == -1){
//				cout<<"-1!!!!!!!!!!!"<<endl;
//				break;
////				lines[i].replace(pos,1,"\\\"");
//			}
//			else{
//				cout<<"0!!!!!!!!!!!!"<<endl;
//				break;
//			}
		}
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
	
	
	cout<<"��ɣ����룺"<<endl;
	
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

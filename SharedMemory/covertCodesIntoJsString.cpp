#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
using namespace std;

int main(){
	
	/*
	** Input 
	*/
	
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
	
	int pos;
	
	/*
	** Escape Quote
	*/ 
	
	for(int i = 0; i < count; i++){
		
		while(1){
			pos = lines[i].find("\"");
			if(pos == -1){
				break;
			}
			lines[i].replace(pos, 1, "QUOTE_NEED_TO_ESCAPE");
		}

		while(1){
			pos = lines[i].find("QUOTE_NEED_TO_ESCAPE");
			if(pos == -1){
				break;
			}
			lines[i].replace(pos, 20, "\\\"");
		}
	}
	
	/*
	** Escape Tab
	*/ 
	
	for(int i = 0; i < count; i++){
		
		while(1){
			pos = lines[i].find("    ");
			if(pos == -1){
				break;
			}
			lines[i].replace(pos, 4, "TAB_NEED_TO_ESCAPE");
		}

		while(1){
			pos = lines[i].find("TAB_NEED_TO_ESCAPE");
			if(pos == -1){
				break;
			}
			lines[i].replace(pos, 18, "");
		}
	}
	
	/*
	** Create \n
	*/
	
	string finalString = "var code = \"";
	
	for(int i = 0; i < lines.size(); i++){
		finalString += lines.at(i);
		finalString += "\\n";
	}
	
	finalString += "\"";
	
	/*
	** Output and Save into File
	*/
	
	cout << "完成！代码：" << endl << finalString << endl;
	
	ofstream out("ConvertedCode.js");
	out << finalString <<endl;
	out.close();
	
	cout << "成功保存到ConvertedCode.js" <<endl;
	
	getchar();
}

#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

inline void SSystem(string str){
	system(str.c_str());
}

void CheckIfPipeExist(){
	;
}

int main(){
	SSystem("mshta javascript:alert(\"test\");window.close();");
}

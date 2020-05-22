#include <cstdio>
#include <iostream>
#include <string>
#include <Windows.h>
#include "Pipe.h"
using namespace std;

#define PIPENAME "CuiPipe1"

inline void SSystem(string str){
	system(str.c_str());
}

int main(){
	if(CheckIfPipeExist(PIPENAME) == true){
		cout << PIPENAME << " already exists!" << endl;
	}
	else{
		CreatePipe(PIPENAME, 100 * sizeof(int));
		cout << "Created " << PIPENAME << endl;
	}
	getchar();
}

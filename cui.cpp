#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>
#include "Pipe.h"
using namespace std;

#define PIPENAME "CuiPipe1"

inline void SSystem(string str){
	system(str.c_str());
}

void CuiInit(int argc, char** argv){
//	cout << strcmp(argv[1], "ReadPipe");
	//argv[0] = exe address;
	//argv[1] = command;
	//argv[2] = command argument 1;
	//argv[3] = command argument 2;
	
	if(argc == 1){   //have no arguments
		return;      //back to main()
	}
	
	if(strcmp(argv[1], "ReadPipe") == 0){
		cout<<"READPIPE!"<<endl;
		char buf[100];
		ReadPipe(argv[2], buf);         //read the pipe that named "command argument 1"
		
		int position;
		stringstream ss;
		ss.clear();
		ss << argv[3];
		ss >> position;
		
		PostQuitMessage((int)buf[position]);  //read the position that is "command argument 2"
	}
	
	if(strcmp(argv[1], "WritePipe") == 0){
		cout<<"WRITEPIPE!"<<endl;
		WritePipe(argv[2], argv[3]); //write "command argument 3" into "command argument 2" pipe
		PostQuitMessage(0);
	}
}

int main(int argc, char** argv){
	CuiInit(argc, argv);
	
//	if(CheckIfPipeExist(PIPENAME) == true){
//		cout << PIPENAME << " already exists!" << endl;
//	}
//	else{
//		CreatePipe(PIPENAME, 100 * sizeof(int));
//		cout << "Created " << PIPENAME << endl;
//	}
	getchar();
}

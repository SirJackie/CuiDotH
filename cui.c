#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include "SharedMemory.h"

#define SMNAME  "CuiSM1"
#define SMLEN   100

void CuiInit(int argc, char** argv){
	//argv[0] = exe address;
	//argv[1] = command;
	//argv[2] = command argument 1;
	//argv[3] = command argument 2;
	//argv[3] = command argument 3;
	
	if(argc == 1){
		//have no arguments
		return;  //back to main()
	}
	
	if(strcmp(argv[1], "READSM") == 0){
		exit(ReadSM(argv[2], atoi(argv[3])));
	}
	
	if(strcmp(argv[1], "WRITESM") == 0){
		WriteSM(argv[2], atoi(argv[3]), atoi(argv[4]));
		exit(0);
	}
}

void CuiExit(){
	WriteSM(SMNAME, 0,  -1);
}

void CuiDrawLine(int x1, int y1, int x2, int y2){
	WriteSM(SMNAME, 1, x1);
	WriteSM(SMNAME, 2, y1);
	WriteSM(SMNAME, 3, x2);
	WriteSM(SMNAME, 4, y2);
	WriteSM(SMNAME, 0,  1); //activate DrawLine() inside Client.hta
	while(ReadSM(SMNAME, 0) != 0){
		;
	}
}
BOOL CuiCheckHeartBeat(){
	int count = 0;
	WriteSM(SMNAME, 0,  -2); //activate heartbeat reporter inside Client.hta
	while(ReadSM(SMNAME, 0) != 0){
		Sleep(1);
		count += 1;
		if(count > 500){
			return FALSE;
		}
	}
	return TRUE;
}

int main(int argc, char** argv){
	CuiInit(argc, argv);    //For Cmd Call
	
	CreateSM(SMNAME, 65535);
	WriteSM(SMNAME, 0, 0);       //initialize

	system("start .\\Client.hta");
	
	CuiDrawLine(0, 0, 400, 400);
	printf("Drew!"); 
	
	while(CuiCheckHeartBeat()){
		;
	}

	CuiExit();
}

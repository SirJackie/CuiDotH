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
		if(!CheckIfSharedMemoryExist(argv[2])){
			printf("Error! Shared Memory Doesn't Even Exist!!!");
			PostQuitMessage(0);
		}
		exit(ReadPieceOfSharedMemory(argv[2], atoi(argv[3])));
	}
	
	if(strcmp(argv[1], "WRITESM") == 0){
		if(!CheckIfSharedMemoryExist(argv[2])){
			printf("Error! Shared Memory Doesn't Even Exist!!!");
			exit(0);
		}
		WritePieceOfSharedMemory(argv[2], atoi(argv[3]), atoi(argv[4]));
		exit(0);
	}
}

void DrawLine(int x1, int y1, int x2, int y2){
	WritePieceOfSharedMemory(SMNAME, 1, x1);
	WritePieceOfSharedMemory(SMNAME, 2, y1);
	WritePieceOfSharedMemory(SMNAME, 3, x2);
	WritePieceOfSharedMemory(SMNAME, 4, y2);
	WritePieceOfSharedMemory(SMNAME, 0,  1); //activate DrawLine() inside Client.hta
	while(ReadPieceOfSharedMemory(SMNAME, 0) != 0){
		Sleep(1000); 
	}
}

int main(int argc, char** argv){
	CuiInit(argc, argv);    //For Cmd Call
//	if(CheckIfSharedMemoryExist(SMNAME) == FALSE){
		CreateSharedMemory(SMNAME, 100 * sizeof(int));
		WritePieceOfSharedMemory(SMNAME, 0, 0);       //initialize
//		printf("Created Shared Memory"); 
//	}
	system("start .\\Client.hta");
	
	
	
	DrawLine(0, 0, 400, 400);
	printf("Drew!"); 
	
	getchar();
}

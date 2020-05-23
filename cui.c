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
	
	int returnValue;
	
	if(argc == 1){
		//have no arguments
		return;  //back to main()
	}
	
	if(strcmp(argv[1], "READSM") == 0){
		printf("Mode: READSM\n");
		if(!CheckIfSharedMemoryExist(argv[2])){
			printf("Error! Shared Memory Doesn't Even Exist!!!");
			PostQuitMessage(0);
		}
		ReadPieceOfSharedMemory(argv[2], atoi(argv[3]), &returnValue);
		PostQuitMessage(returnValue);
	}
	
	if(strcmp(argv[1], "WRITESM") == 0){
		printf("Mode: READSM\n");
		if(!CheckIfSharedMemoryExist(argv[2])){
			printf("Error! Shared Memory Doesn't Even Exist!!!");
			PostQuitMessage(0);
		}
		WritePieceOfSharedMemory(argv[2], atoi(argv[3]), atoi(argv[4]));
	}
}

int main(int argc, char** argv){
	CuiInit(argc, argv);    //For Cmd Call
	
	int i;
	int data[SMLEN];
	
	if(CheckIfSharedMemoryExist(SMNAME)){
		printf("%s already exists! Values:\n", SMNAME);
		ReadSharedMemory(SMNAME, data, SMLEN);
		for(i = 0; i < SMLEN; i++){
			printf("%d ", data[i]);
		}
	}
	else{
		CreateSharedMemory(SMNAME, 100 * sizeof(int));
		for(i = 0; i < SMLEN; i++){
			data[i] = i;
		}
		WriteSharedMemory(SMNAME, data, 100); 
		printf("Created %s and wrote init values\n", SMNAME);
	}
	getchar();
}

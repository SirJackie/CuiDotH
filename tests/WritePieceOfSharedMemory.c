#include <stdio.h>
#include "SharedMemory.h"

int main(){
	int i;
	
	//Check Existing State
	i = CheckIfSharedMemoryExist("CuiSM1");
	if(i == TRUE){
		printf("Existing State: True\n");
	}
	else{
		printf("Existing State: False\n");
	}
	 
	WritePieceOfSharedMemory("CuiSM1", 1, 0);
} 

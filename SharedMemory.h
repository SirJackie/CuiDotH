#ifndef PIPE_H_
#define PIPE_H_

#include <Windows.h>
#include <string.h>

HANDLE CreateSM(char* name,int len){
    return CreateFileMapping(INVALID_HANDLE_VALUE,
                             NULL,
                             PAGE_READWRITE,
                             0,
                             len,
                             name);
}

void CloseSM(char* name){
    CloseHandle(OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, name));
}

BOOL CheckSM(char* name){
	HANDLE pipe = OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, name);
	
    if(NULL == pipe){
        return FALSE;
    }
    else{
        return TRUE;
    }
}

int ReadSM(char* name, int position){
//	HANDLE pipe = OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, name);

	HANDLE pipe = CreateSM(name, 65535);
	
    LPVOID pBuffer = MapViewOfFile(pipe, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    
    int returnValue = ((int*)pBuffer)[position];
    
    UnmapViewOfFile(pBuffer);
    
    return returnValue;
}

void WriteSM(char* name, int position, int value){
//	HANDLE pipe = OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, name);

	HANDLE pipe = CreateSM(name, 65535);
	
    LPVOID pBuffer = MapViewOfFile(pipe, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    
    ((int*)pBuffer)[position] = value;
    
    UnmapViewOfFile(pBuffer);
}

void ReadStringFromSharedMemory(char* name, int* buffer, int len){
	int i;
	
//	HANDLE pipe = OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, name);

	HANDLE pipe = CreateSM(name, 65535);
	
    LPVOID pBuffer = MapViewOfFile(pipe, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    
    for(i = 0; i < len; i++){
    	buffer[i] = ((int*)pBuffer)[i];
	}
    
    UnmapViewOfFile(pBuffer);
}

void WriteStringToSharedMemory(char* name, int* data, int len){
	int i;
	
//	HANDLE pipe = OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, name);

	HANDLE pipe = CreateSM(name, 65535);
	
    LPVOID pBuffer = MapViewOfFile(pipe, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    
    for(i = 0; i < len; i++){
    	((int*)pBuffer)[i] = data[i];
	}
    
    UnmapViewOfFile(pBuffer);
}

#endif

#ifndef PIPE_H_
#define PIPE_H_

#include <Windows.h>
#include <string.h>

HANDLE CreateSharedMemory(char* name,int len){
    return CreateFileMapping(INVALID_HANDLE_VALUE,
                             NULL,
                             PAGE_READWRITE,
                             0,
                             len,
                             name);
}

void DestroySharedMemory(char* name){	
    CloseHandle(OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, name));
}

BOOL CheckIfSharedMemoryExist(char* name){
	HANDLE pipe = OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, name);
	
    if(NULL == pipe){
        return FALSE;
    }
    else{
        return TRUE;
    }
}

void WriteSharedMemory(char* name, int* data, int len){
	int i;
	
	HANDLE pipe = OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, name);
	
    LPVOID pBuffer = MapViewOfFile(pipe, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    
    for(i = 0; i < len; i++){
    	((int*)pBuffer)[i] = data[i];
	}
    
    UnmapViewOfFile(pBuffer);
}

void ReadSharedMemory(char* name, int* buffer, int len){
	int i;
	
	HANDLE pipe = OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, name);
	
    LPVOID pBuffer = MapViewOfFile(pipe, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    
    for(i = 0; i < len; i++){
    	buffer[i] = ((int*)pBuffer)[i];
	}
    
    UnmapViewOfFile(pBuffer);
}

void ReadPieceOfSharedMemory(char* name, int position, int* returnValue){
	HANDLE pipe = OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, name);
	
    LPVOID pBuffer = MapViewOfFile(pipe, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    
    *returnValue = ((int*)pBuffer)[position];
    
    UnmapViewOfFile(pBuffer);
}

void WritePieceOfSharedMemory(char* name, int position, int value){
	HANDLE pipe = OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, name);
	
    LPVOID pBuffer = MapViewOfFile(pipe, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    
    ((int*)pBuffer)[position] = value;
    
    UnmapViewOfFile(pBuffer);
}

#endif

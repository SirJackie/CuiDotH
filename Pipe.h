#ifndef PIPE_H_
#define PIPE_H_

#include <windows.h>
#include <string>

HANDLE CreatePipe(char* name,int len){
    return CreateFileMapping(INVALID_HANDLE_VALUE,
                             NULL,
                             PAGE_READWRITE,
                             0,
                             len,
                             name);
}

void DestroyPipe(char* name){
	HANDLE pipe = OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, name);
	
    CloseHandle(pipe);
}

bool CheckIfPipeExist(char* name){
	HANDLE pipe = OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, name);
	
    if(NULL == pipe){
        return false;
    }
    else{
        return true;
    }
}

void WritePipe(char* name, char* data){
	HANDLE pipe = OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, name);
	
    LPVOID pBuffer = MapViewOfFile(pipe, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    
    strcpy((char*)pBuffer, data);
    
    UnmapViewOfFile(pBuffer);
}

void ReadPipe(char* name, char* buffer){
	HANDLE pipe = OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, name);
	
    LPVOID pBuffer = MapViewOfFile(pipe, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    
    strcpy(buffer, (char*)pBuffer);
    
    UnmapViewOfFile(pBuffer);
}

#endif

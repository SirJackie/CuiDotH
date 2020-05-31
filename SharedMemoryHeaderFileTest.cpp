#include <stdio.h>
#include "SharedMemory.h"

int main(){
	printf("%d\n", ReadSM("CuiSM1", 0));
	WriteSM("CuiSM1", 0, 123);
	printf("%d\n", ReadSM("CuiSM1", 0));
}

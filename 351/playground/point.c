//Stefan Dierauf Oct 2013 (omg im almost 20)
//playground for pointers.c of lab 1
//
#include <stdio.h>

int intSize() {
	int intArray[10];
	int * intPtr1;
	int * intPtr2;
	intPtr1 = &intArray[0];
	intPtr2 = &intArray[1];
	int a = &(&intPtr1);
	int b = &(&intPtr2);
	return b - a;
}

int main(int arg, char* argv[]) {
	int size = intSize();
	printf("intptr should be 4 bytes: %d, 0x%x\n", size, size);
}

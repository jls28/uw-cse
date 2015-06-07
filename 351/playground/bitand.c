#include <stdio.h>

typedef char byte;

void showBytes(byte * start, int len) {
	int i;
	for (i = 0; i < len; i++) {
		printf("%p\t0x%.2x\n", start + i, *(start + i));
	}
	printf("\n");
}

void showInt(int x) {
	showBytes( (byte *) &x, 2*sizeof(int));
}

int bitAnd(int x, int y) {
	int result = 0;
	result = ~(~x | ~y);
	return result;
}

void printBits(unsigned int num) {
	for (int bit = 0; bit < (sizeof(unsigned int) * 8); bit++) {
		printf("%i", num & 0x01);
		num == num >> 1;
	}
	printf("\n");
}

int bitXor(int x, int y) {
	int result = 0;
	result = ~(~(x&~y) & ~(~x&y)) ;
	return result;
}

int thirdBits(void) {
	//return an int with every third bit set to 1
	//should look like 0100 1001 0010 0100 1001 0010 0100 1001 in binary
	//or          0x    4    9    2    4    9    2    4    9
	//or 1227133513 in decimal
	int result = 0x49;
	result <<= 8;
	result |= 0x24;
	result <<= 8;
	result |= 0x92;
	result <<= 8;
	result |= 0x49; 
	return result;
}

//returns 1 if x can be represented as an n-bit 2's compliment integer
int fitsBits(int x, int n) {
	//x must fit in n bits
	//smash it as large as possible
	//unsmash it
	//return equivalency
	int result = x;
	printf("0x%x\n", result);
	result <<= (32 + ~n + 1);
	printf("0x%x\n", result);
	result >>= (32 + ~n + 1);
	printf("0x%x\n", result);
	return (! (result ^ x));
}

int sign(int x) {
	int result = x;
	//shift left for a whole
	int neg = x >> 31;
	int zeroOrNot = !!x; //if x == 0; itll be zero
	return neg | zeroOrNot;
}

int getByte(int x, int n) {
	int result = x;
	result >>= (n << 3);
	return result & 0xff;
}

int logShift(int x, int n) {
	unsigned int poo = x;
	return x >> n;
}

int logicalShift(int x, int n) {
	int mask = 0x1 << 31;
	printf("0x%x\n", mask);
	mask = mask >> n - 1;
	printf("0x%x\n", mask);
	mask = ~mask;
	printf("0x%x\n", mask);
	int shift = x >> n;
	printf("0x%x\n", shift);
	return ((x >> n) & mask);
}

int addOk(int x, int y) {
	int sum = (x + y) >> 31;
	int minx = x >> 31;
	int miny = y >> 31;
	return !( ~(minx ^ miny) & (minx ^ sum));
}

int invert(int x, int p, int n) {
	//build mask for that chunk
	//not the number 
	//return the (~mask & x) | (mask & ~x)
	int mask = 0x1;
	mask <<= 31;
	mask >>= n - 1;
	mask = logicalShift(mask, 32- p - n); 
	return (~mask & x) | (mask & ~x);
}

int binvert(int x, int p, int n) {
	int mask = 1;
	int logicalMask = 1 << 31;
	logicalMask >>= 33 + ~p + ~n;
	mask <<= 31;
	mask >>= 32 + ~p;
	mask = mask & ~logicalMask; 
	printf("0x%x\n", mask);
	return (~mask & x) | (mask & ~x);
}

int bang(int x) {
	int zeroCheck = ~x;
	int zeroAssure = ~(zeroCheck + 1);
	return (1 & ((zeroAssure & zeroCheck) >> 31));
}

int conditional(int x, int y, int z) {
  int ifZero = !!x;
  return (((ifZero << 31) >> 31) & y) | ((((!ifZero) << 31) >> 31) & z);
}

int isPower2(int x) {
	return (~0 & 1) & 1 | 0 //1 or 0
}

int main(int arg, char* argv[]) {
	printf("%d \n", bitAnd(6, 5));
	printf("%d \n", 6 & 5);
	printf("%d \n", bitXor(3, 10));
	printf("%d \n", 3 ^ 10);
	int thirdbits = thirdBits();
	printf("int thirdbits = 1227133513\n");
	showInt(thirdbits);
	printf("\n");
	printf("%d\t%d\n\n", 3, ~3);
	printf("thirdbits = 0x%x\n or 0d%d\n", thirdBits(), thirdBits());
	printf("getByte(0x12345678, 1): 0x%x\n", getByte(0x12345678, 1));
	//printBits(1);	
	printf("5, 3: %d\n", fitsBits(5, 3));
	printf("-4, 3: %d\n", fitsBits(-4, 3));
	printf("sign(131): %d\n", sign(131));
	printf("sign(-23) %d\n", sign(-23));
	printf("logicalShift(0x87654321, 4): 0x%x\n", logShift(0x87654321, 4));
	printf("huge number %d\n", 34123412341234 + 43123423141234);
	printf("addOk1 0x%x\n", addOk(0x80000000, 0x80000000));
	printf("addOk2 0x%x\n", addOk(0x80000000, 0x7000000));
	printf("invert1: 0x%x\n", binvert(0x80000000, 0, 1));
	printf("invert2: 0x%x\n", binvert(0x0000008e, 3, 3));
	printf("bang 123123: %d\n", bang(123123));
	printf("bang -10: %d\n", bang(-10));
	printf("bang 0: %d\n", bang(0));
	printf("logshift: 0x%x\n", logShift(0x80000000, 1));
	printf("conditional 2, 4, 5: %d\n", conditional(2, 4, 5));
	return 0;
}

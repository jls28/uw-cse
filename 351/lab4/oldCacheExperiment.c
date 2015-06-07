#include <stdio.h>

int src[4096][4096];
int dst[4096][4096];

/* Copies the contents of one 4096-by-4096 array (src) into another (dst). */
int main(int argc, char* argv[])
{
	// declare all variables before the code (conform to an older C standard...)
	int rep;
	int i, j;

	for ( rep = 0; rep < 10; rep++ )
	{
		for ( i = 0; i < 4096; i++ )
		{
			for ( j = 0; j < 4096; j++ )
			{
				src[i][j] = i * rep;
				dst[i][j] = src[i][j];
			}
		}
	}

	return 0;
}

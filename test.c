
#include <stdio.h>

int main()
{
	unsigned char a = 0xff; // 1111 1111
				
	char b = a & 1;
	printf("b = %d\n", b);
	return 0;
}

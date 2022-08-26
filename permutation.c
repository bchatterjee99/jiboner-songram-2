#include <stdio.h>

int perm[8] = {6, 4, 2, 5, 7, 0, 1, 3};

int get_bit(char a, int i)
{
	return (a >> i) & 1;
}

char set_bit(char a, int i, int b)
{
	a = a & (0xff ^ (1 << i));
	a = a | (b << i);
	return a;
}

void show(unsigned char a)
{
	int x = 128;
	while(x > 0)
	{
		printf("%d", !!(a & x));
		x = x >> 1;
	}
}

int main()
{
	char a = 0xb1; // 1011 0001
	char b;

	for(int i=0; i<8; i++)
		b = set_bit(b, perm[i], get_bit(a, i));

	show(a);
	printf("\n");
	show(b);
	printf("\n");
	return 0;
}

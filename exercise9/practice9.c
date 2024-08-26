#include<stdio.h>

void swap_int(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int main(void)
{
	int u, v;
	u = 2;
	v = 3;

	printf("u=%d v=%d\n", u, v);
	swap_int(&u, &v);
	printf("u=%d v=%d\n", u, v);

	return 0;
}

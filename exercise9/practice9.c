#include<stdio.h>

void swap_int(int *a, int *b);

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

/**
 * @brief 変数の値を入れ替える関数
 *
 * @details int型の2つの変数の値を入れ替える関数
 *
 * @return int *a と int *b の値を入れ替えた値を返す
 */
void swap_int(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

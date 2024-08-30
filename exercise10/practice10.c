#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct DAT_t{
	int n;
	const char* s;
}DAT;

/**
 * @brief ソート関数
 *
 * @details int型のnを比較してからchar型のsを比較する関数
 *
 * @return n1がn2より小さい場合は-1を、大きい場合は1を、同じ場合はs1とs2を比較する
 */
int compare(const void *a, const void *b){
	DAT *dat1 = (DAT *)a;
	DAT *dat2 = (DAT *)b;

	if (dat1->n < dat2->n) return -1;
	if (dat1->n > dat2->n) return 1;

	return strcmp(dat1->s, dat2->s);
}

int main(void)
{
	DAT dat[]={
		{9,"A"},
		{2,"A"},
		{5,"AB"},
		{5,"AA"},
	};
	
	size_t numDat = sizeof(dat) / sizeof(dat[0]);
	qsort(dat, numDat, sizeof(DAT), compare);

	for (size_t i = 0; i < numDat; i++) {
		printf("n: %d, s: %s\n", dat[i].n, dat[i].s);
	}

	return 0;
}

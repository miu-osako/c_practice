#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct DAT_t{
	int n;
	const char* s;
}DAT;

int compare_DAT_t(const void *a, const void *b);

/**
 * @brief ソート関数
 *
 * @details struct DAT_tのint nを比較してからchar* sを比較する関数
 *
 * @param[out] a DATのメンバにアクセスするポインタ1
 *
 * @param[out] b DATのメンバにアクセスするポインタ2
 *
 * @return dat1のnがdat2のnより小さい場合は-1を、大きい場合は1を、同じ場合はsを比較する
 */
int compare_DAT_t(const void *a, const void *b){
	const DAT *dat1 = (const DAT *)a;
	const DAT *dat2 = (const DAT *)b;

	if (dat1->n < dat2->n) {
		return -1;
	}
	if (dat1->n > dat2->n) {
		return 1;
	}

	return strcmp(dat1->s, dat2->s);
}

int main(void)
{
	DAT dat[] = {
		{9,"A"},
		{2,"A"},
		{5,"AB"},
		{5,"AA"},
	};
	
	size_t num_dat = sizeof(dat) / sizeof(dat[0]);
	qsort(dat, num_dat, sizeof(DAT), compare_DAT_t);

	for (size_t i = 0; i < num_dat; i++) {
		printf("n: %d, s: %s\n", dat[i].n, dat[i].s);
	}

	return 0;
}

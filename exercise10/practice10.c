#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct DAT_t {
	int n;
	const char* s;
} DAT;

int compare_DAT_t(const void *a, const void *b);

int main(void)
{
	DAT dat[] = {
		{9,"A"},
		{2,"A"},
		{5,"AB"},
		{5,"AA"},
	};
	size_t i;
	
	size_t num_dat = sizeof(dat) / sizeof(dat[0]);
	qsort(dat, num_dat, sizeof(DAT), compare_DAT_t);

	for (i = 0; i < num_dat; i++) {
		printf("n: %d, s: %s\n", dat[i].n, dat[i].s);
	}

	return 0;
}

/**
 * @brief 比較関数
 *
 * @details struct DAT_tのint nを比較して、同値の場合char* sも比較する関数
 *
 * @param[in] a 大小比較の対象1
 *
 * @param[in] b 大小比較の対象2
 *
 * @return aが大きい場合正の値、bが大きい場合負の値、同じ場合0を返す
 */
int compare_DAT_t(const void *a, const void *b)
{
	const DAT *dat1 = (const DAT *)a;
	const DAT *dat2 = (const DAT *)b;
	
	if (dat1->n < dat2->n) {
		return -1;
	}else if (dat1->n > dat2->n) {
		return 1;
	}
		return strcmp(dat1->s, dat2->s);
}

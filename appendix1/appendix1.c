#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int allocate_memory(size_t size);

int main(int argc, char *argv[])
{
	size_t size = 0;
	char *end = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "usage: program name size[M/K]\n"
				"options: size[M/K] サイズ(M=メガ,K=キロ)\n");
		return 1;
	}
	
	if (argv[1][strlen(argv[1]) - 1] == 'M' || argv[1][strlen(argv[1]) - 1] == 'm') {
		size = strtol(argv[1], &end, 10) * 1024 * 1024;
	} else if (argv[1][strlen(argv[1]) - 1] == 'K' || argv[1][strlen(argv[1]) - 1] == 'k') {
		size = strtol(argv[1], &end, 10) * 1024;
	} else {
	size = strtol(argv[1], &end, 10);
	}
	
	allocate_memory((size_t)size);

	return 0;
}

/**
* @brief メモリを確保する関数
*
* @details パラメータで渡されたサイズ分メモリを確保する関数
*
* @return 確保したメモリの内容を表示
 */
int allocate_memory(size_t size)
{
	size_t i = 0;
	char *array = NULL;

	array = (char *)calloc(1, size);

	if (array == NULL) {
		fprintf(stderr, "Error allocating memory.\n");
		return 1;
	} else {
		printf("size = %zu\naddress = %p\n", size, (void*)array);
	}

	free(array);

	return 0;
}

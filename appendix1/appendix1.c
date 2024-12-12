#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	size_t size = 0;
	char *end = NULL;
	char *array = NULL;

	if (argc != 2) {
		fprintf(stderr, "usage: program name size[M/K]\n"
				"options: size[M/K] サイズ(M=メガ,K=キロ)\n");
		return 1;
	}
	
	size = strtol(argv[1], &end, 10);
	switch (*end) {
		case 'M':
		size = size * 1024 * 1024;
		break;
		case 'K':
		size = size * 1024;
		break;
		default:
		break;
	}
	
	array = (char *)malloc(size);
	if (array == NULL) {
		fprintf(stderr, "Error allocating memory.\n");
		return 1;
	}
	printf("1 = size = %zu\naddress = %p\n", size, (void*)array);

	free(array);

	return 0;
}

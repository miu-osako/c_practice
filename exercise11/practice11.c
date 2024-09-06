#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	char str[100];

	FILE *file = NULL;
	if (argc != 2) {
		printf("usage: display_file filename\n");
		return 1;
	}

	file = fopen(argv[1], "r");
	if (file == NULL) {
		printf("error opening file\n");
		return -1;
	}

	while (!feof(file)) {
		fgets(str, 100, file) == NULL;
		printf("%s", str);
	}
	
	if (ferror(file)) {
		printf("error closing file\n");
	}
	
	fclose(file);
	return 0;
}

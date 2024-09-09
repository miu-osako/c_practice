#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	int max_length;
	char str[max_length];
	
	max_length= 256;
	FILE *fp = NULL;
	
	if (argc != 2) {
		printf("usage: display_file filename\n");
		return 1;
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("error opening file\n");
		return -1;
	}

	while (!feof(fp)) {
		fgets(str, max_length, fp);
		printf("%s",str);
	}
	
	fclose(fp);
	if (ferror(fp)) {
                printf("error closing file\n");
        }

	return 0;
}

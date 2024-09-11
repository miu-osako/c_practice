#include<stdio.h>
#include<stdlib.h>

#define READ_FILE_MAX 256 /*ファイル読み込み最大バイト数を定義*/

int main(int argc, char *argv[])
{
	char str[READ_FILE_MAX + 1];
	const char *infile;
	FILE *fp = NULL;
	int rc = 0;

	if (argc != 2) {
		printf("usage: display_file filename\n");
		return 1;
	}

	infile = argv[1];
	fp = fopen(infile, "r");
	if (fp == NULL) {
		perror("error opening file\n");
		return 1;
	}

	while (fgets(str, READ_FILE_MAX + 1, fp) != NULL) {
		printf("%s", str);
	}
	if (!feof(fp)) {
		perror("error reading file\n");
		rc = 1;
	}
	
	if (fclose(fp) != 0) {
		perror("error closing file\n");
		return 1;
	}

	return rc;
}

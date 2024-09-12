#include<stdio.h>
#include<stdlib.h>

#define READ_FILE_MAX 256 /*ファイル読み込み最大バイト数を定義*/
#define SUCCESS 0 /*正常終了*/
#define FAILURE 1 /*異常終了*/

int main(int argc, char *argv[])
{
	char str[READ_FILE_MAX];
	const char *infile;
	FILE *fp = NULL;
	int chk;
	int rc = 0;

	if (argc != 2) {
		fprintf(stderr, "usage: display_file filename\n");
		return FAILURE;
	}

	infile = argv[1];
	fp = fopen(infile, "r");
	if (fp == NULL) {
		perror("error opening file\n");
		return FAILURE;
	}

	while (fgets(str, sizeof(str), fp) != NULL) {
		printf("%s", str);
	}
	if (ferror(fp)) {
		perror("error reading file\n");
		rc = FAILURE;
	}
	
	chk = fclose(fp);
	if (chk != 0) {
		perror("error closing file\n");
		return FAILURE;
	}

	return rc;
}

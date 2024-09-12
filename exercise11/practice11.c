#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#define READ_FILE_MAX 256 /*ファイル読み込み最大バイト数を定義*/
#define SUCCESS 0 /*正常終了*/
#define FAILURE 1 /*異常終了*/

int main(int argc, char *argv[])
{
	char str[READ_FILE_MAX];
	const char *infile;
	FILE *fp = NULL;
	int file_close_status;
	int rc = 0;

	if (argc != 2) {
		fprintf(stderr, "usage: display_file filename\n");
		return FAILURE;
	}

	infile = argv[1];
	fp = fopen(infile, "r");
	if (fp == NULL) {
		fprintf(stderr, "error opening '%s': %s\n", infile, strerror(errno));
		return FAILURE;
	}

	while (fgets(str, sizeof(str), fp) != NULL) {
		printf("%s", str);
	}
	if (ferror(fp)) {
		perror("error reading file\n");
		rc = FAILURE;
	}
	
	file_close_status = fclose(fp);
	if (file_close_status != 0) {
		perror("error closing file\n");
		return FAILURE;
	}

	return rc;
}

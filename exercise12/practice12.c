#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_BYTE 16 /* 1行あたりのバイト */
#define SUCCESS 0 /* 正常終了 */
#define FAILURE 1 /* 異常終了 */

int main(int argc, char* argv[])
{
	unsigned char input_byte[MAX_BYTE];
	/* 入力文字1文字につき、HEX表記の下2桁(0xXXのXX)を使用するため2 バイト、半角スペースの1バイトの合計3バイトを使う。最後にNULL文字が入るため、+1している。 */
	char out[MAX_BYTE * 3 + 1];
	size_t i, read_size;
	const char *infile;
	FILE *fp;
	unsigned long index = 0;
	int file_close_status;
	int rc = SUCCESS;

	if (argc != 2) {
		fprintf(stderr, "usage: hexdump filename\n"
			"options: filename ファイル名\n");
		return FAILURE;
	}

	infile = argv[1];
	fp = fopen(infile, "rb");
	if (fp == NULL) {
		fprintf(stderr, "error opening '%s': %s\n", infile, strerror(errno));
		return FAILURE;
	}

	printf("ADDRESS  00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
	while (!feof(fp)) {
		read_size = fread(input_byte, sizeof(unsigned char), MAX_BYTE, fp);
		if (ferror(fp)) {
			perror("fread error");
			rc = FAILURE;
			break;
		}
		for (i = 0; i < read_size; i++) {
		/* 入力文字1文字につき、HEX表記の下2桁(0xXXのXX)を使用するため2バイト、半角スペースの1バイトの合計3バイトを使う。そのため入力文字の1文字目はout[0]から始まり2文字目以降の添え字は3の倍数となる。 */
			sprintf(out + i * 3, " %02X", input_byte[i]);
		}
		printf("%07lX0%s\n", index, out);
		index++;
	}

	file_close_status = fclose(fp);
	if (file_close_status != 0) {
		perror("error closing file\n");
		return FAILURE;
	}

	return rc;
}

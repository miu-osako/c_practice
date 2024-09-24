#include <stdio.h>
#include <stdlib.h>

#define BYTES_HEX 16 /*16進数表記*/
#define SUCCESS 0 /*正常終了*/
#define FAILURE 1 /*異常終了*/

int main(int argc, char* argv[])
{
	unsigned char bytes[BYTES_HEX];
	size_t i;
	FILE *fp;
	size_t read_size;
	unsigned long ADDRESS = 0;

	if (argc != 2) {
		fprintf(stderr, "usage: %s filename\n"
			"options: filename ファイル名\n",
			argv[0]);
		return FAILURE;
	}

	fp = fopen(argv[1], "rb");
	if (fp == NULL) {
		perror("error opening file\n");
		return FAILURE;
	}

	while ((read_size = fread(bytes, sizeof(unsigned char), 
		BYTES_HEX, fp)) > 0) {
		printf("%08lx", ADDRESS);
		for (i = 0; i < read_size; i++) {
			printf("%02X ", bytes[i]);
		}
		for (i = 0; i < BYTES_HEX; i++) {
			printf(" ");
		}
		printf("\n");
		ADDRESS += BYTES_HEX;
	}

	if (ferror(fp)) {
		perror("error reading file");
		return FAILURE;
	}

	fclose(fp);
	return SUCCESS;
}

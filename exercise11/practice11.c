#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	int ch; 

	FILE *file = fopen("test.txt", "r");
	if (file == NULL) {
		printf("ファイルが開けませんでした。\n");
		return 1;
	}

	while ((ch = fgetc(file)) != EOF)
	{
		putchar(ch);
	}

	fclose(file);
	return 0;
}

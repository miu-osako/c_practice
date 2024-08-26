#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	int i;
	
	for (i = 1; i < argc; i++){
		n=atoi(argv[i]);
		printf("%d:%s\n", i, argv[i]);
	}
	return 0;
}

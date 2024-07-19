#include <stdio.h>

int main(void) {  
    printf("char=%05zu short=%05zu int=%05zu long=%05zu float=%05zu double=%05zu \n", 
            sizeof(char), sizeof(short), sizeof(int), sizeof(long), sizeof(float), sizeof(double));
    return 0;
}

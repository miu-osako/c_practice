#include<stdio.h>

static int static_counter();

int main(void)
{

    for(int i = 0; i < 10; i++) {
        printf("%d\n", static_counter());
    }
    
    return 0; 
}

    static int static_counter()
    {
        static int counter = 0;
        return counter++;
    }

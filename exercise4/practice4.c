#include <stdio.h>

int main(void)
{
    int i = 20;
    int *p;

    p = &i;

    printf("i: アドレス=%#llx 値=%d\n", (unsigned long)&i, i);
    printf("p: アドレス=%#llx 値=%#llx 指す先の値=%d\n", (unsigned long)&p, (unsigned long)p, *p);

    return 0;
}

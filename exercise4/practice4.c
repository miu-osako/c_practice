#include <stdio.h>

int main(void)
{
    int i = 20;
    int *p;

    p = &i;

    printf("i: アドレス=%#llx 値=%d\n", &i, i);
    printf("p: アドレス=%#llx 値=%#llx 指す先の値=%d\n", &p, p, *p);

    return 0;
}

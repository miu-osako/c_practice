#include <stdio.h>

int main(void) {
    int i = 20;
    int *p;
    p = &i;

    printf("i: アドレス=%p 値=%d\n", (void *)&i, i);
    printf("p: アドレス=%p 値=%p 指す先の値=%d\n", (void *)&p, (void *)p, *p);

    return 0;
}
#include <stdio.h>

int main(void) {
    int i = 20;
    int *p;
    p = &i;

    printf("i: アドレス=0x%lx 値=%d\n", (unsigned long)&i, i);
    printf("p: アドレス=0x%lx 値=0x%lx 指す先の値=%d\n", (unsigned long)&p, (unsigned long)p, *p);

    return 0;
}

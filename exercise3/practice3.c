#include <stdio.h>
#include <string.h>

int main(void)
{
    char str[] = "abcdefghijklmnopqrstu";

    printf("配列サイズ=%ld 文字列長=%ld\n", sizeof(str), strlen(str));
    printf("1文字目は%c、最後の文字は%cです。\n", str[0], str[20]);
    return 0;
}

#include <stdio.h>
#include <string.h>

int main(void)
{
    char str[] = "abcdefghijklmnopqrstu";

    printf("配列サイズ=%ld 文字列長=%ld\n1文字目は%c、最後の文字は%cです。\n",
            sizeof(str), strlen(str), str[0], str[strlen(str) - 1]);
    return 0;
}

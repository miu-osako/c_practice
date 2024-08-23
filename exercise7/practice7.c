#include<stdio.h>

static int static_counter();

int main(void)
{
    for (int i = 0; i < 10; i++) {
        int counter = static_counter();
        printf("%d\n", counter);
    }

    return 0; 
}

/**
 * @brief カウンタを返す関数
 * 
 * @details プログラムを起動してから呼び出すたびに1インクリメントした値を返す関数
 * 
 * @return 1インクリメントした値を返す
 */
static int static_counter()
{
    static int counter = 0;
    return ++counter;
}

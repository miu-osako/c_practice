#include<stdio.h>

int main(void)
{
    char charArray[2] = {};
    short shortArray[2] = {};
    int intArray[2] = {};
    long longArray[2] = {};

    char *charPointer = charArray;
    short *shortPointer = shortArray;
    int *intPointer = intArray;
    long *longPointer = longArray;

    printf("char配列=%lld short配列=%lld int配列=%lld long配列=%lld\n"
           "charポインタ=%lld shortポインタ=%lld intポインタ=%lld longポインタ=%lld\n",
            (long long)(&charArray[1])-(long long)(&charArray[0]),
            (long long)(&shortArray[1])-(long long)(&shortArray[0]),
            (long long)(&intArray[1])-(long long)(&intArray[0]),
            (long long)(&longArray[1])-(long long)(&longArray[0]),
            (long long)(charArray+1)-(long long)(charArray),
            (long long)(shortArray+1)-(long long)(shortArray),
            (long long)(intArray+1)-(long long)(intArray),
            (long long)(longArray+1)-(long long)(longArray));

    return 0;
}

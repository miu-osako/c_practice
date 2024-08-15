#include<stdio.h>

int main(void)
{
    char char_array[2] = {};
    short short_array[2] = {};
    int int_array[2] = {};
    long long_array[2] = {};

    char *char_pointer = char_array;
    short *short_pointer = short_array;
    int *int_pointer = int_array;
    long *long_pointer = long_array;

    printf("char配列=%lld short配列=%lld int配列=%lld long配列=%lld\n"
           "charポインタ=%lld shortポインタ=%lld intポインタ=%lld longポインタ=%lld\n",
            (long long)(&char_array[1]) - (long long)(&char_array[0]),
            (long long)(&short_array[1]) - (long long)(&short_array[0]),
            (long long)(&int_array[1]) - (long long)(&int_array[0]),
            (long long)(&long_array[1]) - (long long)(&long_array[0]),
            (long long)(char_pointer + 1) - (long long)(char_pointer),
            (long long)(short_pointer + 1) - (long long)(short_pointer),
            (long long)(int_pointer + 1) - (long long)(int_pointer),
            (long long)(long_pointer + 1) - (long long)(long_pointer));

    return 0;
}

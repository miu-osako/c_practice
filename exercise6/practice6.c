#include<stdio.h>
#include<stddef.h>

struct SAMPLE_t
{
    char m1;
    short m2;
    char m3;
    long m4;
    char m5;
    void* m6;
};

int main(void)
{
    struct SAMPLE_t sample;
    
    printf("構造体のサイズ=%zu メンバの合計サイズ=%zu\n"
           "char m1オフセット=%zu サイズ=%zu\n"
           "short m2オフセット=%zu サイズ=%zu\n"
           "char m3オフセット=%zu サイズ=%zu\n"
           "long m4オフセット=%zu サイズ=%zu\n"
           "char m5オフセット=%zu サイズ=%zu\n"
           "void* m6オフセット=%zu サイズ=%zu\n",
           sizeof(sample),
           sizeof(sample.m1)+sizeof(sample.m2)+sizeof(sample.m3)+sizeof(sample.m4)+sizeof(sample.m5)+sizeof(sample.m6),
           offsetof(struct SAMPLE_t, m1), sizeof(sample.m1),
           offsetof(struct SAMPLE_t, m2), sizeof(sample.m2),
           offsetof(struct SAMPLE_t, m3), sizeof(sample.m3),
           offsetof(struct SAMPLE_t, m4), sizeof(sample.m4),
           offsetof(struct SAMPLE_t, m5), sizeof(sample.m5),
           offsetof(struct SAMPLE_t, m6), sizeof(sample.m6));
    return 0;
}

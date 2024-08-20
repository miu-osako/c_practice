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
    struct SAMPLE_t a;
    
    printf("構造体のサイズ=%zu メンバの合計サイズ=%zu\n"
           "char m1オフセット=%zu サイズ=%zu\n"
           "short m2オフセット=%zu サイズ=%zu\n"
           "char m3オフセット=%zu サイズ=%zu\n"
           "long m4オフセット=%zu サイズ=%zu\n"
           "char m5オフセット=%zu サイズ=%zu\n"
           "void* m6オフセット=%zu サイズ=%zu\n",
           sizeof(a),
           sizeof(a.m1)+sizeof(a.m2)+sizeof(a.m3)+sizeof(a.m4)+sizeof(a.m5)+sizeof(a.m6),
           offsetof(struct SAMPLE_t, m1), sizeof(a.m1),
           offsetof(struct SAMPLE_t, m2), sizeof(a.m2),
           offsetof(struct SAMPLE_t, m3), sizeof(a.m3),
           offsetof(struct SAMPLE_t, m4), sizeof(a.m4),
           offsetof(struct SAMPLE_t, m5), sizeof(a.m5),
           offsetof(struct SAMPLE_t, m6), sizeof(a.m6));
    return 0;
}

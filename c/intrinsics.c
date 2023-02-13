#include <stdio.h>
#include <immintrin.h>

void print_vec16(const char* name, __m512 vec16)
{
    printf("%s = [", name);
    for(int i=0; i<15; i++)
    {
        printf("%.2f, ", vec16[i]);
    }
    printf("%.2f]\n", vec16[15]);
}

int main()
{
    __m512 a = _mm512_set_ps(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
    __m512 b = _mm512_mul_ps(a, _mm512_set1_ps(100));

    __m512 c = _mm512_shuffle_f32x4(a,b,0x88);
    __m512 d = _mm512_shuffle_f32x4(a,b,0x18);

    __m512 e = _mm512_unpackhi_ps(a,b);
    __m512 f = _mm512_unpacklo_ps(a,b);

    __m512 g = _mm512_mask_blend_ps(0x03,a,b);
    __m512 h = _mm512_mask_blend_ps(0x07,a,b);

    __m128 i = _mm512_extractf32x4_ps(a,0);
    __m128 j = _mm512_extractf32x4_ps(a,1);
    __m128 k = _mm512_extractf32x4_ps(a,2);
    __m128 l = _mm512_extractf32x4_ps(a,3);

    __m128 m = _mm_setr_ps(0,1,2,3);
    __m128 n = _mm_mul_ps(m, _mm_set1_ps(100));

    __m128 o = _mm_shuffle_ps(m,n,0x11);

    return 0;
}

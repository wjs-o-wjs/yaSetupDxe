#include <blend.h>
#include <stdio.h>
#include <stdlib.h>
#include <emmintrin.h> //SSE2
#include <tmmintrin.h> //SSSE3
#include <time.h>
#define RED(x) ((x&0xFF0000)>>16)
#define GREEN(x) ((x&0xFF00)>>8)
#define BLUE(x) ((x&0xFF))
#define ALPHA(x) ((x&0xFF000000)>>24)
const __m128i all_zero = {0x0,0x0};
const __m128i __attribute__((aligned(16))) alpha_shuffle_mask = {
    0xffff06ff06ff06ff,
    0xffff0eff0eff0eff
};
const __m128i __attribute__((aligned(16))) alpha_reverse_mask = {
    0xffffffffffffffff,
    0xffffffffffffffff
};
const __m128i __attribute__((aligned(16))) alpha_bit_mask = {
    0x0000ff00ff00ff00,
    0x0000ff00ff00ff00
};
void alpha_blending(__m128i* front, __m128i* back, __m128i* result)
{
    //unpack.
    __m128i temp_a  = _mm_loadu_si128(front);
    __m128i temp_b  = _mm_unpacklo_epi8(temp_a,all_zero);
    temp_a = _mm_unpackhi_epi8(temp_a,all_zero);
    __m128i alpha_a = _mm_shuffle_epi8(temp_a,alpha_shuffle_mask);
    __m128i alpha_b = _mm_shuffle_epi8(temp_b,alpha_shuffle_mask);
    temp_a = _mm_mulhi_epu16(temp_a,alpha_a);
    temp_b = _mm_mulhi_epu16(temp_b,alpha_b);
    __m128i result_1 = _mm_packus_epi16(temp_b,temp_a);
    //Then background.
    temp_a  = _mm_loadu_si128(back);
    temp_b  = _mm_unpacklo_epi8(temp_a,all_zero);
    temp_a = _mm_unpackhi_epi8(temp_a,all_zero);
    alpha_a = _mm_subs_epu8(alpha_reverse_mask,alpha_a);
    alpha_b = _mm_subs_epu8(alpha_reverse_mask,alpha_b);
    alpha_a = _mm_and_si128(alpha_a,alpha_bit_mask);
    alpha_b = _mm_and_si128(alpha_b,alpha_bit_mask);
    temp_a = _mm_mulhi_epu16(temp_a,alpha_a);
    temp_b = _mm_mulhi_epu16(temp_b,alpha_b);
    //Add.
    temp_a = _mm_packus_epi16(temp_b,temp_a);
    temp_a = _mm_add_epi8(temp_a,result_1);
    _mm_store_si128(result,temp_a);
}
void alpha_blending_naive(unsigned* a, unsigned* b, unsigned* res)
{
    for(int i=0;i<3;i++) {
        float transparency=ALPHA(a[i])/256.0;
        res[i] = (int)(BLUE(a[i])*transparency+BLUE(b[i])*(1-transparency))
                |(int)(GREEN(a[i])*transparency+GREEN(b[i])*(1-transparency))<<8
                |(int)(RED(a[i])*transparency+RED(b[i])*(1-transparency))<<16;
    }
}
uint32_t alpha_blending_pixel(uint32_t a, uint32_t b)
{

}
pixel* alpha_blending_bitmap(pixel* front,uint32_t front_width, uint32_t front_height, pixel* back, uint32_t back_width, uint32_t back_height, uint32_t offset_x, uint32_t offset_y)
{

}

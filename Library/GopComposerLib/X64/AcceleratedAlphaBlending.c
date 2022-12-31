/** @file
  The accelerated alpha blending function especially for X64 based systems using SSE.
**/
#include <Library/ComposerLib.h>
#include <emmintrin.h> //SSE2
#include <tmmintrin.h> //SSSE3
#include <stdalign.h>

#define RED(x) ((x&0xFF0000)>>16)
#define GREEN(x) ((x&0xFF00)>>8)
#define BLUE(x) ((x&0xFF))
#define ALPHA(x) ((x&0xFF000000)>>24)
#define SSE_GROUP_SIZE (sizeof(__m128i)/sizeof(UINT32))

const __m128i alignas(16) AllZero = {0x0,0x0};
const __m128i alignas(16) AlphaShuffleMask = {
    0xffff06ff06ff06ff,
    0xffff0eff0eff0eff
};

const __m128i alignas(16) AlphaReverseMask = {
    0xffffffffffffffff,
    0xffffffffffffffff
};
const __m128i alignas(16) AlphaBitMask = {
    0x0000ff00ff00ff00,
    0x0000ff00ff00ff00
};

UINT32
EFIAPI
AlphaBlendingPixel
(
  UINT32 a,
  UINT32 b
)
{
  float transparency=ALPHA(a)/256.0;
  return (int)(BLUE(a)*transparency+BLUE(b)*(1-transparency))
        |(int)(GREEN(a)*transparency+GREEN(b)*(1-transparency))<<8
        |(int)(RED(a)*transparency+RED(b)*(1-transparency))<<16;
}
STATIC
VOID
AlphaBlendingSse(__m128i* Front, __m128i* Back, __m128i* Result)
{
    //unpack.
    __m128i TempA  = _mm_loadu_si128(Front);
    __m128i TempB  = _mm_unpacklo_epi8(TempA,AllZero);
    TempA = _mm_unpackhi_epi8(TempA,AllZero);
    __m128i AlphaA = _mm_shuffle_epi8(TempA,AlphaShuffleMask);
    __m128i AlphaB = _mm_shuffle_epi8(TempB,AlphaShuffleMask);
    TempA = _mm_mulhi_epu16(TempA,AlphaA);
    TempB = _mm_mulhi_epu16(TempB,AlphaB);
    __m128i Result1 = _mm_packus_epi16(TempB,TempA);
    //Then background.
    TempA  = _mm_loadu_si128(Back);
    TempB  = _mm_unpacklo_epi8(TempA,AllZero);
    TempA = _mm_unpackhi_epi8(TempA,AllZero);
    AlphaA = _mm_subs_epu8(AlphaReverseMask,AlphaA);
    AlphaB = _mm_subs_epu8(AlphaReverseMask,AlphaB);
    AlphaA = _mm_and_si128(AlphaA,AlphaBitMask);
    AlphaB = _mm_and_si128(AlphaB,AlphaBitMask);
    TempA = _mm_mulhi_epu16(TempA,AlphaA);
    TempB = _mm_mulhi_epu16(TempB,AlphaB);
    //Add.
    TempA = _mm_packus_epi16(TempB,TempA);
    TempA = _mm_add_epi8(TempA,Result1);
    _mm_store_si128(Result,TempA);
}
EFI_STATUS
EFIAPI
AlphaBlendingArea
(
  UINT32   *Front,
  UINT32    FrontWidth,
  UINT32    FrontHeight,
  UINT32   *Back,
  UINT32    BackWidth,
  UINT32    BackHeight,
  UINT32    OffsetX,
  UINT32    OffsetY
)
{
  UINT32 ActualWidth,ActualHeight;
  UINT32 SseGroupCount=0,RemainingPixelOffset=0;
  //Make sure that we have at least 1 pixel.
  if(OffsetX>=BackWidth||OffsetY>=BackHeight) {
    return EFI_SUCCESS;
  }
  ActualWidth  = (FrontWidth+OffsetX>BackWidth?BackWidth-OffsetX:FrontWidth);
  ActualHeight = (FrontHeight+OffsetY>BackHeight?BackHeight-OffsetY:FrontHeight);
  SseGroupCount = ActualWidth / SSE_GROUP_SIZE;
  RemainingPixelOffset = (SseGroupCount*SSE_GROUP_SIZE);
  for(UINT32 i=0;i<ActualHeight;i++) {
    //Use as much SSE as we can.
    for(UINT32 j=0;j<RemainingPixelOffset;j+=SSE_GROUP_SIZE) {
      AlphaBlendingSse((__m128i*)&Front[i*FrontWidth+j],
                       (__m128i*)&Back[(OffsetY+i)*BackWidth+(OffsetX+j)],
                       (__m128i*)&Back[(OffsetY+i)*BackWidth+(OffsetX+j)]);
    }
    for(UINT32 j=RemainingPixelOffset;j<ActualWidth;j++) {
      Back[(OffsetY+i)*BackWidth+j] = AlphaBlendingPixel( Back[(OffsetY+i)*BackWidth+(OffsetX+j)],
                                                         Front[i*FrontWidth+j]);
    }
  }
  return EFI_SUCCESS;
}

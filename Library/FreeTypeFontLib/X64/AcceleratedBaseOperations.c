/** @file
  Base operations related to FreeType operations, which may increase overall performance via assembly.
  This file contains SSE accelerated operations.
  SPDX-License-Identifier: WTFPL
**/
#include <Uefi.h>
#include <emmintrin.h> //SSE2
#include <tmmintrin.h> //SSSE3
#include <stdalign.h>
#include <Library/DebugLib.h>

#define COLOR_BIT_MASK      0x00FFFFFF
#define ALPHA_BIT_SHIFT     24

const __m128i alignas(16) ColorBitMask = {
  0x00ffffff00ffffff,
  0x00ffffff00ffffff
};
const __m128i alignas(16) ShuffleMask = {
  0x0180808000808080,
  0x0380808002808080
};

VOID
SetMemInt32
(
  UINT32       *Buffer,
  CONST UINTN   BufferSize,
  CONST UINT32  Value
)
{
  // Make the memory address align.
  UINT32 *PtrBegin = Buffer;
  UINT32 *PtrEnd   = (UINT32*)((UINTN)Buffer+BufferSize);
  __m128i alignas(16) tmp = {
    (UINT64)Value<<32|Value,
    (UINT64)Value<<32|Value
  };
  while((((UINTN)PtrBegin)&0xF)&&PtrBegin<PtrEnd) {
    *PtrBegin = Value;
    PtrBegin++;
  }
  if(PtrBegin==PtrEnd) {
    return;
  }
  PtrEnd   = (UINT32*)(((UINTN)Buffer+BufferSize-(sizeof(__m128i)/sizeof(UINT32)))&~0xF);
  while(PtrBegin!=PtrEnd) {
    _mm_store_si128((__m128i*)PtrBegin,tmp);
    PtrBegin += (sizeof(__m128i)/sizeof(UINT32));
  }
  for(UINT32 * i=PtrEnd;i<(UINT32*)((UINTN)Buffer+BufferSize);i++) {
    *i = Value;
  }
}

#if 0
VOID
SetTransparency
(
  UINT32       *Buffer,
  UINTN         BufferSize,
  CONST UINT8  *Value
)
{
  __m128i alignas(16) tmp;
  int i=0;
  // Make the memory address align.
  UINT32 *PtrBegin = Buffer;
  UINT32 *PtrEnd   = (UINT32*)((UINTN)Buffer+BufferSize);
  while((((UINTN)PtrBegin)&0xF)&&PtrBegin<PtrEnd) {
    *PtrBegin &= COLOR_BIT_MASK;
    *PtrBegin |= (UINT32)Value[i]<<(ALPHA_BIT_SHIFT);
    PtrBegin++;
    i++;
  }
  if(PtrBegin==PtrEnd) {
    return;
  }
  PtrEnd   = (UINT32*)(((UINTN)Buffer+BufferSize-(sizeof(__m128i)/sizeof(UINT32)))&~0xF);
  while(PtrBegin<=PtrEnd) {
    tmp = _mm_loadu_si128((__m128i*)&Value[i]);
    tmp = _mm_shuffle_epi8(tmp,ShuffleMask);
    __m128i a = _mm_load_si128((__m128i*)PtrBegin);
    a = _mm_and_si128(a,ColorBitMask);
    a = _mm_or_si128 (a,tmp);
    _mm_store_si128((__m128i*)PtrBegin,a);
    PtrBegin += (sizeof(__m128i)/sizeof(UINT32));
    i += (sizeof(__m128i)/sizeof(UINT32));
  }
  for(UINT32 *Ptr=PtrEnd;Ptr<(UINT32*)((UINTN)Buffer+BufferSize);Ptr++) {
    *PtrBegin &= COLOR_BIT_MASK;
    *PtrBegin |= (UINT32)Value[i]<<(ALPHA_BIT_SHIFT);
    PtrBegin++;
    i++;
  }
}
#else
VOID
SetTransparency
(
  UINT32       *Buffer,
  UINTN         BufferSize,
  CONST UINT8  *Value
)
{
  for (UINTN i=0;i<BufferSize;i++) {
    UINT32 Transparency = Value[i] << ALPHA_BIT_SHIFT;
    Buffer[i] &= COLOR_BIT_MASK;
    Buffer[i] |= Transparency;
  }
  return;
}
#endif

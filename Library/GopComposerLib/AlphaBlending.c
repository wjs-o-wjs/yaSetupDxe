/**
  Alpha blending for naive CPUs that don't support accelerated alpha blending.
  Currently, we only support X64 CPUs.
**/
#if (!defined MDE_CPU_X64)
#include <Library/ComposerLib.h>
UINT32
EFIAPI
AlphaBlendingPixel
(
  UINT32 a,
  UINT32 b
)
{
  UINT32 Ret = 0xFF000000;
  double Alpha = ((a&0xFF000000)>>24);
  Alpha /= 0xFF;
  Ret |= (((UINT32)((Alpha*((a&0x00FF0000)>>16))+((1-Alpha)*((b&0x00FF0000)>>16))))<<16);
  Ret |= (((UINT32)((Alpha*((a&0x0000FF00)>>8 ))+((1-Alpha)*((b&0x0000FF00)>>8 ))))<<8);
  Ret |= (((UINT32)((Alpha*((a&0x000000FF)    ))+((1-Alpha)*((b&0x000000FF)    )))));
  return Ret;
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
  //Make sure that we have at least 1 pixel.
  if(OffsetX>=BackWidth||OffsetY>=BackHeight) {
    return EFI_SUCCESS;
  }
  ActualWidth  = (FrontWidth+OffsetX>BackWidth?BackWidth-OffsetX:FrontWidth);
  ActualHeight = (FrontHeight+OffsetY>BackHeight?BackHeight-OffsetY:FrontHeight);
  for(UINT32 i=0;i<ActualHeight;i++) {
    for(UINT32 j=0;j<ActualWidth;j++) {
      Back[(OffsetY+i)*BackWidth+j] = AlphaBlendingPixel( Back[(OffsetY+i)*BackWidth+(OffsetX+j)],
                                                         Front[i*FrontWidth+j]);
    }
  }
  return EFI_SUCCESS;
}
#endif

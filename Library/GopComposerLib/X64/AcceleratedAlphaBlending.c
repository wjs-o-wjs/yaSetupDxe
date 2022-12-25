/** @file
  The accelerated alpha blending function especially for X64 based systems using SSE.
**/
#include <Library/ComposerLib.h>
UINT32
EFIAPI
AlphaBlendingPixel
(
  UINT32 a,
  UINT32 b
)
{
  return EFI_SUCCESS;
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
  return EFI_SUCCESS;
}

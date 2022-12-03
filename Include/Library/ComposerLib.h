#ifndef COMPOSER_LIB
#define COMPOSER_LIB
#include <Uefi.h>
/*
 Interface to initialize the Composer.
 If you specify the display parameter, we will try to match your input.
 If you pass O as input, we will use the default GOP resolution amd try to scale it "seeming like" 1920*1080.
 */
EFI_STATUS
EFIAPI
InitComposer (
  IN OPTIONAL UINT32 DesiredScreenWidth,
  IN OPTIONAL UINT32 DesiredScreenHeight,
  IN OPTIONAL double DesiredScaleFactor
);

/*
 Interface to clear screen.
 The color is specified as XRGB8888.
 */
EFI_STATUS
EFIAPI
ClearScreen (
  UINT32 Color
);
/*
 Interface to fill a rectangle area.
 The color is specified as XRGB8888.
 Overflow areas are guranteed to handle properly.
 */
EFI_STATUS
EFIAPI
FillRectangle
(
  UINT32 StartX,
  UINT32 StartY,
  UINT32 Width,
  UINT32 Height,
  UINT32 Color
);
/*
 Interface to update the "Window Caption".
 */
EFI_STATUS
EFIAPI
DrawCaption
(
  IN UINT32 Height,
  IN UINT32 BackgroundColor,
  IN CONST CHAR16 *Title
);
#endif

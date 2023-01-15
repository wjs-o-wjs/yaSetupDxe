#ifndef COMPOSER_LIB
#define COMPOSER_LIB
/** @file
  Headers to define the composer interface.
  SPDX-License-Identifier: WTFPL
**/

#include <Uefi.h>

/**
  Since EFI EmulatorPkg's GOP Driver cannot write to framebuffer directly, we will need to double buffer it.
 **/
extern UINT32 *FrameBuffer;

/**
  Interface to initialize the Composer.
  If you specify the display parameter, we will try to match your input.
  If you pass O as input, we will use the default GOP resolution amd try to scale it "seeming like" 1920*1080.
 **/
EFI_STATUS
EFIAPI
InitComposer (
  IN OPTIONAL UINT32 DesiredScreenWidth,
  IN OPTIONAL UINT32 DesiredScreenHeight,
  IN OPTIONAL double DesiredScaleFactor
);

/**
  Interface to clear screen.
  The color is specified as XRGB8888.
 **/
EFI_STATUS
EFIAPI
ClearScreen (
  UINT32 Color
);
/**
  Interface to fill a rectangle area.
  The color is specified as XRGB8888.
  Overflow areas are guranteed to handle properly.
 **/
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
/**
  Interface to update the "Window Caption".
 **/
EFI_STATUS
EFIAPI
DrawCaption
(
  IN UINT32        Height,
  IN UINT32        BackgroundColor,
  IN CONST CHAR16 *Title
);
/**
  This function returns current scale factor.
 **/
double
EFIAPI
GetScaleFactor (
  VOID
);
/**
  This function sets scale factor.
**/
EFI_STATUS
EFIAPI
SetScaleFactor (
  double NewScaleFactor
);
/**
  This function returns current screen width.
 **/
UINT32
EFIAPI
GetScreenWidth
(
  VOID
);
/**
  This function returns current screen height.
 **/
UINT32
EFIAPI
GetScreenHeight
(
  VOID
);

/**
  This function does alpha blending on a single pixel.
  The detailed implementation varies among different architectures.
  @param  a   The first pixel.
  @param  b   The second pixel.
  @returns    The blended pixel.
**/
UINT32
EFIAPI
AlphaBlendingPixel
(
  UINT32 a,
  UINT32 b
);


/**
  This function does blending on an area of pixels.
  The detailed implementation varies among different architectures.
  If the blended data reaches the maximum bound of the buffer, the overflow area is dropped.
  @param    Front       The pixel buffer of the front pixel.
  @param    FrontWidth  The width of front buffer.
  @param    FrontHeight The height of the front buffer that is going to be blended.
  @param    Back        The pixel buffer of the back pixel.
  @param    BackWidth   The width of back buffer.
  @param    BackHeight  The height of the back buffer that is going to be blended.
  @param    OffsetX     The relative offset of Front. It is obvious that this vaule should not less than 0.
  @param    OffsetY     The relative offset of Front. It is obvious that this vaule should not less than 0.
  @returns  EFI_SUCCESS The blending process ends successfully.
  @returns  Other       When the process fails.
**/
EFI_STATUS
EFIAPI
AlphaBlendingArea
(
  UINT32          *Front,
  UINT32           FrontWidth,
  UINT32           FrontHeight,
  UINT32          *Back,
  UINT32           BackWidth,
  UINT32           BackHeight,
  UINT32           OffsetX,
  UINT32           OffsetY,
  UINT32 OPTIONAL *Destination,
  UINT32 OPTIONAL  DestinationWidth
);

EFI_STATUS
EFIAPI
RefreshPartialScreen
(
  UINT32 XOffset,
  UINT32 YOffset,
  UINT32 Width,
  UINT32 Height
);

EFI_STATUS
EFIAPI
RefreshScreen
(
  VOID
);
#endif

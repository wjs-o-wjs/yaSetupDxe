#ifndef FONT_LIB
#define FONT_LIB
/** @file
  Headers to define the Font library interface.
  SPDX-License-Identifier: WTFPL
**/
#include <Uefi.h>

// This function initializes font.
EFI_STATUS
EFIAPI
PrepareFont
(
  VOID
);


// This function destroys font.
EFI_STATUS
EFIAPI
DestroyFont
(
  VOID
);

// This function renders text.
EFI_STATUS
EFIAPI
RenderText
(
  IN CONST CHAR16   *Text,
  IN UINT32          FontSize,
  IN UINT32          Color,
  OUT UINT32       **Buffer,
  OUT UINT32        *BufferWidth,
  OUT UINT32        *BufferHeight
  //TODO: Auto-wrap policy
);

#endif

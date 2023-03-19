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
  UINT32         *Buffer,
  CONST CHAR16   *Text,
  UINT32          FontSize,
  UINT32          XOffset,
  UINT32          YOffset,
  UINT32          PixelsPerLine
  //TODO: Auto-wrap policy
);

#endif

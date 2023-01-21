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

#endif

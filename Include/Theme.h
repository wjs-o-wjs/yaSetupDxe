#ifndef THEME_H
#define THEME_H
/** @file
  Headers to define binary files provided by theme.
  SPDX-License-Identifier: WTFPL
**/
#include <Uefi.h>

// The font file in Theme.
extern const unsigned char FontFile[];
extern const UINTN FontSize;
// The cursor image in Theme.
extern const unsigned char CursorImage[];
extern const UINT32 CursorImageWidth;
extern const UINT32 CursorImageHeight;

#endif

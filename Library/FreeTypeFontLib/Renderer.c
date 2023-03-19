/** @file
  The text renderer using FreeType2.
  SPDX-License-Identifier: WTFPL
**/
#include <Library/FontLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <freetype/freetype.h>


extern FT_Face    Face;

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
)
{
  DEBUG ((DEBUG_ERROR,"Rendering Text \"%s\" @(%d,%d), %d pts.\n",Text,XOffset,YOffset,FontSize));
  (VOID)Buffer;
  (VOID)PixelsPerLine;
  return EFI_SUCCESS;
}

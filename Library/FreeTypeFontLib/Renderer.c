/** @file
  The text renderer using FreeType2.
  SPDX-License-Identifier: WTFPL
**/
#include <Library/FontLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/MemoryAllocationLib.h>
#include <freetype/freetype.h>



extern FT_Face    Face;
extern double     ScaleFactor;//In GopComposerLib

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
)
{
  FT_Error Error;
  UINT32   GlyphNumber;
  UINT32   Width=0, Height=0;
  INT32    HeightAboveBaseline=0, HeightBelowBaseline=0;
  CONST CHAR16 *Ptr=Text;
  Error = FT_Set_Char_Size(
          Face,             /* handle to face object         */
          0,                /* char_width in 1/64 of points  */
          FontSize*64,      /* char_height in 1/64 of points */
          96*ScaleFactor,   /* horizontal device resolution  */
          96*ScaleFactor);  /* vertical device resolution    */
  if(Error) {
    DEBUG ((DEBUG_ERROR,"Cannot set font size!\n"));
    return EFI_UNSUPPORTED;
  }
  while (*Ptr) {
    GlyphNumber = FT_Get_Char_Index(Face,*Ptr);
    if(GlyphNumber) { // GlyphNumber==0 means there is no such glyph.
      Error = FT_Load_Glyph(Face,GlyphNumber,FT_LOAD_RENDER);
      if(Error) {
        DEBUG ((DEBUG_ERROR,"Cannot load character %c(%d)!\n",*Ptr,GlyphNumber));
        return EFI_UNSUPPORTED;
      }
      if(Face->glyph->metrics.horiBearingY>HeightAboveBaseline) {
        HeightAboveBaseline = Face->glyph->metrics.horiBearingY;
      }
      if(Face->glyph->metrics.height-Face->glyph->metrics.horiBearingY>HeightBelowBaseline) {
        HeightBelowBaseline = Face->glyph->metrics.height-Face->glyph->metrics.horiBearingY;
      }
      if(*(Ptr+1)!='\0' && *(Ptr+1)!='\n') {
        Width += Face->glyph->metrics.horiAdvance/64;
      }
      else {
        Width += Face->glyph->metrics.width/64;
      }
    }
    Ptr++;
  }
  Height = (HeightAboveBaseline+HeightBelowBaseline)/64;
  DEBUG ((DEBUG_ERROR,"String:%s, size %d*%d(%d+%d)\n",Text,Width,Height,HeightAboveBaseline/64,HeightBelowBaseline/64));
  *Buffer = AllocatePool(Width*Height*sizeof(UINT32));
  Ptr = Text;
  //TODO: Render!
  return EFI_SUCCESS;
}

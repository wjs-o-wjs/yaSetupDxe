// The Wrapper file that calls FreeType2.
#include <Library/FontLib.h>
#include <freetype/freetype.h>

extern EFI_BOOT_SERVICES *gBS;
extern EFI_SYSTEM_TABLE  *gST;
FT_Library Library;
EFI_STATUS
EFIAPI
PrepareFont
(
  VOID
)
{
  FT_Error Status;
  Status = FT_Init_FreeType(&Library);
  if(Status) {
    gST->StdErr->OutputString(gST->StdErr,L"Cannot init FreeType Library!\n");
    return EFI_UNSUPPORTED;
  }
  return EFI_SUCCESS;
}

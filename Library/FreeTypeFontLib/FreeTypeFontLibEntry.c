// The Wrapper file that calls FreeType2.
#include <Library/FontLib.h>
#include <freetype/freetype.h>
#include <Library/DebugLib.h>

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
    DEBUG ((DEBUG_INFO,"Cannot init FreeType Library!\n"));
    gST->StdErr->OutputString(gST->StdErr,L"Cannot init FreeType Library!\n");
    return EFI_UNSUPPORTED;
  }
  else {
    DEBUG ((DEBUG_INFO,"FreeType Library init done!\n"));
  }
  return EFI_SUCCESS;
}

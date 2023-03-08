// The Wrapper file that calls FreeType2.
#include <Library/FontLib.h>
#include <freetype/freetype.h>
#include <Library/DebugLib.h>

extern EFI_BOOT_SERVICES *gBS;
extern EFI_SYSTEM_TABLE  *gST;

// Imported from external font that converted by LD.
// FIXME: Use more generic way!
extern UINT8  _binary_DroidSans_EfiCompressed_start[];
extern UINT8  *_binary_DroidSans_EfiCompressed_size;

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
    DEBUG ((DEBUG_INFO,"Font is at %p, size is %lx\n",_binary_DroidSans_EfiCompressed_start));
    DEBUG ((DEBUG_INFO,"FreeType Library init done!\n"));
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
DestroyFont
(
  VOID
)
{
  FT_Error Status;
  Status = FT_Done_FreeType(Library);
  if(Status) {
    DEBUG ((DEBUG_INFO,"Cannot destroy FreeType Library!\n"));
    gST->StdErr->OutputString(gST->StdErr,L"Cannot destroy FreeType Library!\n");
    return EFI_UNSUPPORTED;
  }
  return EFI_SUCCESS;
}

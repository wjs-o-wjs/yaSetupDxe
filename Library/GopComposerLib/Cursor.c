#include <Library/ComposerLib.h>
#include <Library/PcdLib.h>

extern EFI_BOOT_SERVICES *gBS;
extern EFI_SYSTEM_TABLE  *gST;

STATIC UINT8* CursorBuffer;
STATIC UINT8* BackBuffer;
STATIC UINT32 CursorImageWidth,CursorImageHeight;
STATIC UINT8* CursorImage;
/**
  This function updates the cursor buffer when image beneath cursor has changed its content.
**/
EFI_STATUS
EFIAPI
UpdateCursorBuffer
(
  VOID
)
{
  //TODO: Finish it.
  return EFI_SUCCESS;
}

/**
  This function initializes the cursor.
**/
EFI_STATUS
EFIAPI
InitCursor
(
  VOID
)
{
  EFI_STATUS Status = EFI_SUCCESS;
  CursorImageWidth  = PcdGet32(CursorImageWidth);
  CursorImageHeight = PcdGet32(CursorImageHeight);
  CursorImage       = PcdGetPtr(CursorImage);
  if((CursorImageWidth!=0)&&(CursorImageHeight!=0)) {
    Status = gBS->AllocatePool(EfiLoaderData,CursorImageWidth*CursorImageHeight*sizeof(UINT32),(VOID**)&CursorBuffer);
    Status |= gBS->AllocatePool(EfiLoaderData,CursorImageWidth*CursorImageHeight*sizeof(UINT32),(VOID**)&BackBuffer);
  }
  if(EFI_ERROR(EFI_SUCCESS)) {
    gST->StdErr->OutputString(gST->StdErr,L"Cannot allocate buffer for cursor buffer.\r\n");
    return Status;
  }
  return EFI_SUCCESS;
}

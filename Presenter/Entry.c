#include <Uefi.h>
#include <Library/ComposerLib.h>
EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE    *SystemTable
)
{
  EFI_STATUS                       Status;
  SystemTable->ConOut->OutputString(SystemTable->ConOut,L"Hello EFI!\r\n");
  Status = InitComposer(1024,768,0);
  if(EFI_ERROR(Status)) {
      return Status;
  }
  (VOID) ImageHandle;
  return EFI_SUCCESS;
}

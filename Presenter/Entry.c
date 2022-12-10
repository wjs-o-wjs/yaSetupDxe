#include <Uefi.h>
#include <Library/ComposerLib.h>
#include <Library/MainMessageLooperLib.h>
EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE    *SystemTable
)
{
  EFI_STATUS                       Status;
  SystemTable->StdErr->OutputString(SystemTable->StdErr,L"Hello EFI!\r\n");
  Status = InitComposer(1024,768,0);
  if(EFI_ERROR(Status)) {
      return Status;
  }
  //Add initialization here.
  return EnterMainMessageLoop();
  (VOID) ImageHandle;
}

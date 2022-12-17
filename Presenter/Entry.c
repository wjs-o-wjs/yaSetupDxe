#include <Uefi.h>
#include <Library/ComposerLib.h>
#include <Library/MainMessageLooperLib.h>
#include <Library/MouseLib.h>
#include <Library/KeyboardLib.h>
extern EFI_BOOT_SERVICES *gBS;
EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE    *SystemTable
)
{
  EFI_STATUS                       Status;
  SystemTable->StdErr = SystemTable->ConOut;
  Status = InitKeyboard();
  if(EFI_ERROR(Status)) {
    SystemTable->StdErr->OutputString(SystemTable->StdErr,L"Cannot init keyboard!\r\n");
    return Status;
  }
  Status = InitMouse();
  if(EFI_ERROR(Status)) {
    SystemTable->StdErr->OutputString(SystemTable->StdErr,L"Cannot init mouse!\r\n");
    return Status;
  }
  Status = InitComposer(1024,768,0);
  if(EFI_ERROR(Status)) {
    return Status;
  }
  //Add initialization here.
  return EnterMainMessageLoop();
  (VOID) ImageHandle;
}

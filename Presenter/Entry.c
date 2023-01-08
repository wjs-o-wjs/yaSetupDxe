#include <Uefi.h>
#include <Library/ComposerLib.h>
#include <Library/MainMessageLooperLib.h>
#include <Library/MouseLib.h>
#include <Library/KeyboardLib.h>
#include <Library/DebugLib.h>
extern EFI_BOOT_SERVICES *gBS;
extern
EFI_STATUS
EFIAPI
DxeEmuLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );
EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE    *SystemTable
)
{
  EFI_STATUS                       Status;
#ifdef BUILD_FOR_EMULATOR_PKG
  DxeEmuLibConstructor(ImageHandle,SystemTable);
#endif
  Status = InitComposer(1024,768,0);
  if(EFI_ERROR(Status)) {
    return Status;
  }
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
  //Add initialization here.
  return EnterMainMessageLoop();
  (VOID) ImageHandle;
}

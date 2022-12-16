/** @file
  Emulated mouse lib for platforms that doesn't have a mouse.
  SPDX-License-Identifier: WTFPL
**/
#include <Library/MouseLib.h>
#include <Protocol/SimpleTextIn.h>
#include <Library/UefiLib.h>
extern EFI_BOOT_SERVICES *gBS;
extern EFI_SYSTEM_TABLE  *gST;

/**
  Register our mouse event handler now.
  Currently, we use keyboard to emulate a mouse.
  Operations:
  W     -- Move Up
  A     -- Move Left
  S     -- Move Down
  D     -- Move Right
  Space -- Left Click
  Alt   -- Right Click
**/
EFI_STATUS
EFIAPI
InitMouse
(
  VOID
)
{
  return EFI_SUCCESS;
}

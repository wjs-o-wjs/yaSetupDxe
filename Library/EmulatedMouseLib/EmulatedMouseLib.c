/** @file
  Emulated mouse lib for platforms that doesn't have a mouse.
  SPDX-License-Identifier: WTFPL
**/
#include <Library/MouseLib.h>
#include <Protocol/SimpleTextIn.h>
#include <Library/UefiLib.h>
extern EFI_BOOT_SERVICES *gBS;
extern EFI_SYSTEM_TABLE  *gST;
static MOUSE_LIB_CLICK_HANDLER RegisteredClickHandler;
static MOUSE_LIB_MOVE_HANDLER  RegisteredMoveHandler;

VOID
EFIAPI
EmulatedMouseKeyboardEventHandler
(
  IN EFI_EVENT Event,
  IN VOID*     Context
)
{
  EFI_SIMPLE_TEXT_INPUT_PROTOCOL *Protocol;
  EFI_STATUS Status;
  Protocol = Context;
  EFI_INPUT_KEY Key;
  Status = Protocol->ReadKeyStroke(Protocol,&Key);
  if(EFI_ERROR(Status)) {
    gST->StdErr->OutputString(gST->StdErr,L"Failed to retrieve key.\r\n");
  }
  Print(L"Pressed Key %d\r\n",Key.ScanCode);
  gBS->SignalEvent(Event);
}


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
RegisterMouseEventHandler
(
  IN MOUSE_LIB_CLICK_HANDLER ClickHandler,
  IN MOUSE_LIB_MOVE_HANDLER  MoveHandler
)
{
  EFI_STATUS Status;
  EFI_SIMPLE_TEXT_INPUT_PROTOCOL  *Protocol;
  RegisteredClickHandler = ClickHandler;
  RegisteredMoveHandler  = MoveHandler;
  Protocol =gST->ConIn;
  // We use the keyboard to control mouse.
  Status = gBS->CreateEvent (
    EVT_NOTIFY_WAIT,
    TPL_APPLICATION,
    EmulatedMouseKeyboardEventHandler,
    Protocol,
    &(Protocol->WaitForKey)
  );
  return Status;
}

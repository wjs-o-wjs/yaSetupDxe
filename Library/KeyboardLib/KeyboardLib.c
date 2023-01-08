#include <Library/KeyboardLib.h>
#include <Protocol/SimpleTextIn.h>
#include <Library/MainMessageLooperLib.h>

extern EFI_BOOT_SERVICES  *gBS;
extern EFI_SYSTEM_TABLE   *gST;

static KEYBOARD_INPUT_KEY KeyboardInputRingBuffer[0x20];
static UINTN KeyboardInputRingBufferPosition;

STATIC
VOID
EFIAPI
KeyboardLooperEvent
(
  IN  EFI_EVENT  Event,
  IN  VOID      *Context
)
{
  EFI_INPUT_KEY Key;
  EFI_STATUS    Status = EFI_SUCCESS;
  while(TRUE) {
    Status = gST->ConIn->ReadKeyStroke(gST->ConIn,&Key);
    if(Status!=EFI_SUCCESS) {
      break;
    }
    else {
      KeyboardInputRingBuffer[KeyboardInputRingBufferPosition].ScanCode = Key.ScanCode;
      KeyboardInputRingBuffer[KeyboardInputRingBufferPosition].UnicodeChar = Key.UnicodeChar;
      SendMessage(MessageLooperMessageKeyboard,NULL,&KeyboardInputRingBuffer[KeyboardInputRingBufferPosition]);
      KeyboardInputRingBufferPosition = (KeyboardInputRingBufferPosition+1)%0x20;
    }
  }
  (VOID)Event;
  (VOID)Context;
}

STATIC EFI_EVENT KeyboardEvent;

EFI_STATUS
EFIAPI
InitKeyboard
(
  VOID
)
{
  EFI_STATUS Status;
      // Create timer Event.
  Status = gBS->CreateEvent(EVT_TIMER | EVT_NOTIFY_SIGNAL,
                            TPL_CALLBACK,
                            KeyboardLooperEvent,
                            NULL,
                            &KeyboardEvent);
  if(EFI_ERROR(Status)) {
    gST->StdErr->OutputString(gST->StdErr,L"Cannot create Keyboard timer Event.\r\n");
    return Status;
  }
  Status = gBS->SetTimer(KeyboardEvent,TimerPeriodic,100000); //10ms
  if(EFI_ERROR(Status)) {
    gST->StdErr->OutputString(gST->StdErr,L"Cannot start keyboard timer Event.\r\n");
    return Status;
  }
  return EFI_SUCCESS;
}

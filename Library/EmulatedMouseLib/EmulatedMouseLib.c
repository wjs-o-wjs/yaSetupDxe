/** @file
  Emulated mouse lib for platforms that doesn't have a mouse.
  SPDX-License-Identifier: WTFPL
**/
#include <Library/MouseLib.h>
#include <Library/KeyboardLib.h>
#include <Library/MainMessageLooperLib.h>
#include <Library/ComposerLib.h>
#include <Library/UefiLib.h>
extern EFI_BOOT_SERVICES *gBS;
extern EFI_SYSTEM_TABLE  *gST;

STATIC MOUSE_STATUS MouseStatusRingBuffer[0x20];
STATIC UINTN        MouseStatusRingBufferCurrentPosition;
STATIC INT32        CurrentMousePositionX, CurrentMousePositionY;
STATIC UINT32       MaxMousePositionX, MaxMousePositionY;
/**
  Here we handles the message from the keyboard.
  When we retrieve the information from keyboard, we read the key stroke, and then send mouse event.
 **/
EFI_STATUS
EFIAPI
EmulatedMouseMessageHandler
(
  IN MESSAGE_LOOPER_MESSAGE_TYPE                 MessageType,
  IN OUT VOID                                   *ExtraContent,
  OUT MESSAGE_LOOPER_MESSAGE_FORWARDING_METHOD  *ForwardingMethod
)
{
  KEYBOARD_INPUT_KEY *Key = (KEYBOARD_INPUT_KEY*) ExtraContent;
  switch(Key->UnicodeChar) {
    case 'W': case 'w':{
      CurrentMousePositionY -= 10;
      if(CurrentMousePositionY<0) {
        CurrentMousePositionY = 0;
      }
      break;
    }
    case 'S': case 's':{
      CurrentMousePositionY += 10;
      if(CurrentMousePositionY>MaxMousePositionY) {
        CurrentMousePositionY = MaxMousePositionY;
      }
      break;
    }
    case 'A': case 'a':{
      CurrentMousePositionX -= 10;
      if(CurrentMousePositionX<0) {
        CurrentMousePositionX = 0;
      }
      break;
    }
    case 'D': case 'd':{
      CurrentMousePositionX += 10;
      if(CurrentMousePositionX>MaxMousePositionX) {
        CurrentMousePositionX = MaxMousePositionX;
      }
      break;
    }
    default: {
      *ForwardingMethod = MessageLooperContinueForwardingMessages;
      return EFI_SUCCESS;
    }
  }
  MouseStatusRingBuffer[MouseStatusRingBufferCurrentPosition].CurrentX = CurrentMousePositionX;
  MouseStatusRingBuffer[MouseStatusRingBufferCurrentPosition].CurrentY = CurrentMousePositionY;
  //TODO: Mouse click status.
  SendMessage(MessageLooperMessageMouse,NULL,&MouseStatusRingBuffer[MouseStatusRingBufferCurrentPosition]);
  MouseStatusRingBufferCurrentPosition = (MouseStatusRingBufferCurrentPosition+1)%0x20;
  *ForwardingMethod = MessageLooperStopForwardingMessages;
  (VOID)MessageType;
  return EFI_SUCCESS;
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
InitMouse
(
  VOID
)
{
  //Register our keyboard message handler.
  MaxMousePositionX = GetScreenWidth();
  MaxMousePositionY = GetScreenHeight();
  if((MaxMousePositionX==0)||(MaxMousePositionY==0)) {
    gST->StdErr->OutputString(gST->StdErr,L"Screen is not found. Stop.\r\n");
    return EFI_UNSUPPORTED;
  }
  return RegisterMessageHandler(MessageLooperMessageKeyboard,EmulatedMouseMessageHandler);
}

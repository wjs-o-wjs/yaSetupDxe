/** @file
  Emulated mouse lib for platforms that doesn't have a mouse.
  SPDX-License-Identifier: WTFPL
**/
#include <Library/MouseLib.h>
#include <Library/KeyboardLib.h>
#include <Library/MainMessageLooperLib.h>
#include <Library/UefiLib.h>
extern EFI_BOOT_SERVICES *gBS;
extern EFI_SYSTEM_TABLE  *gST;

STATIC MOUSE_STATUS MouseStatusRingBuffer[0x20];
STATIC UINTN        MouseStatusRingBufferCurrentPosition;
STATIC UINT32       CurrentMousePositionX, CurrentMousePositionY;

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
      break;
    }
    case 'S': case 's':{
      CurrentMousePositionY += 10;
      break;
    }
    case 'A': case 'a':{
      CurrentMousePositionX -= 10;
      break;
    }
    case 'D': case 'd':{
      CurrentMousePositionX += 10;
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
  return RegisterMessageHandler(MessageLooperMessageKeyboard,EmulatedMouseMessageHandler);
}

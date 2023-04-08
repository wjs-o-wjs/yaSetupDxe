/** @file
  Cursor-related composer functions.
  SPDX-License-Identifier: WTFPL
**/

#include <Library/ComposerLib.h>
#include <Library/PcdLib.h>
#include <Library/MouseLib.h>
#include <Library/MainMessageLooperLib.h>
#include <Library/UefiLib.h>
#include <Protocol/GraphicsOutput.h>
#include <Theme.h>

extern EFI_BOOT_SERVICES *gBS;
extern EFI_SYSTEM_TABLE  *gST;

STATIC UINT32 *BackBuffer;
STATIC UINT32  CursorPositionX,CursorPositionY;
STATIC UINT32  FrameBufferWidth,FrameBufferHeight;

/**
  This function updates the cursor buffer when image beneath cursor has changed its content.
**/
VOID
EFIAPI
UpdateCursorBuffer
(
  UINT32 CopyWidth,
  UINT32 CopyHeight
)
{
  //First, Copy the screen buffer into BackBuffer.
  for(UINT32 i=0;i<CopyHeight;i++) {
    for(UINT32 j=0;j<CopyWidth;j++) {
      BackBuffer[i*CursorImageWidth+j] = FrameBuffer[(CursorPositionY+i)*FrameBufferWidth+(CursorPositionX+j)];
    }
  }
  //Then, we do alpha blending.
  AlphaBlendingArea(
    (UINT32*)CursorImage,
    CursorImageWidth,
    CursorImageHeight,
    FrameBuffer,
    FrameBufferWidth,
    FrameBufferHeight,
    CursorPositionX,
    CursorPositionY,
    NULL,
    0
  );
}

/**
  This function Sets the cursor position.
**/
EFI_STATUS
EFIAPI
SetCursorPosition
(
  UINT32 X,
  UINT32 Y
)
{
  if(X>FrameBufferWidth) {
    X = FrameBufferWidth;
  }
  if(Y>FrameBufferHeight) {
    Y = FrameBufferHeight;
  }
  UINT32 OriginalCopyWidth =((CursorPositionX+CursorImageWidth)>FrameBufferWidth?
                             FrameBufferWidth-CursorPositionX:
                             CursorImageWidth);
  UINT32 OriginalCopyHeight=((CursorPositionY+CursorImageHeight)>FrameBufferHeight?
                             FrameBufferHeight-CursorPositionY:
                             CursorImageHeight);
  UINT32 NewCopyWidth      =((X+CursorImageWidth)>FrameBufferWidth?
                             FrameBufferWidth-X:
                             CursorImageWidth);
  UINT32 NewCopyHeight     =((Y+CursorImageHeight)>FrameBufferHeight?
                             FrameBufferHeight-Y:
                             CursorImageHeight);
  // Copy the buffer back.
  for(UINT32 i=0;i<OriginalCopyHeight;i++) {
    for(UINT32 j=0;j<OriginalCopyWidth;j++) {
      FrameBuffer[(CursorPositionY+i)*FrameBufferWidth+(CursorPositionX+j)] = BackBuffer[i*CursorImageWidth+j];
    }
  }
  //Finally, update the screen.
  UINT32 RefreshBeginX,RefreshBeginY,RefreshEndX,RefreshEndY;
  (X>CursorPositionX)?(RefreshBeginX=CursorPositionX,RefreshEndX=X+NewCopyWidth):(RefreshBeginX=X,RefreshEndX=CursorPositionX+OriginalCopyWidth);
  (Y>CursorPositionY)?(RefreshBeginY=CursorPositionY,RefreshEndY=Y+NewCopyHeight):(RefreshBeginY=Y,RefreshEndY=CursorPositionY+OriginalCopyHeight);
  // Generate new cursor.
  CursorPositionX = X;
  CursorPositionY = Y;
  UpdateCursorBuffer(NewCopyWidth,NewCopyHeight);
  return RefreshPartialScreen(
    RefreshBeginX,
    RefreshBeginY,
    RefreshEndX-RefreshBeginX,
    RefreshEndY-RefreshBeginY
  );
}

EFI_STATUS
EFIAPI
CursorMessageHandler
(
  IN MESSAGE_LOOPER_MESSAGE_TYPE                 MessageType,
  IN OUT VOID                                   *ExtraContent,
  OUT MESSAGE_LOOPER_MESSAGE_FORWARDING_METHOD  *ForwardingMethod
)
{
  MOUSE_STATUS *MouseStatus = (MOUSE_STATUS*) ExtraContent;
  *ForwardingMethod = MessageLooperContinueForwardingMessages;
  return SetCursorPosition(MouseStatus->CurrentX,MouseStatus->CurrentY);
  (VOID)MessageType;
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
  if((CursorImageWidth!=0)&&(CursorImageHeight!=0)) {
    Status |= gBS->AllocatePool(EfiLoaderData,CursorImageWidth*CursorImageHeight*sizeof(UINT32),(VOID**)&BackBuffer);
  }
  if(EFI_ERROR(EFI_SUCCESS)) {
    gST->StdErr->OutputString(gST->StdErr,L"Cannot allocate buffer for cursor buffer.\r\n");
    return Status;
  }
  FrameBufferWidth = GetScreenWidth();
  FrameBufferHeight = GetScreenHeight();
  for(UINT32 i=0;i<CursorImageHeight;i++) {
    for(UINT32 j=0;j<CursorImageWidth;j++) {
      BackBuffer[i*CursorImageWidth+j] = FrameBuffer[(CursorPositionY+i)*FrameBufferWidth+(CursorPositionX+j)];
    }
  }
  return RegisterMessageHandler(MessageLooperMessageMouse,CursorMessageHandler);
}

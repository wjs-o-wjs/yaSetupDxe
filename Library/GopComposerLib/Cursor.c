#include <Library/ComposerLib.h>
#include <Library/PcdLib.h>
#include <Library/MouseLib.h>
#include <Library/MainMessageLooperLib.h>
#include <Protocol/GraphicsOutput.h>

extern EFI_BOOT_SERVICES *gBS;
extern EFI_SYSTEM_TABLE  *gST;
extern EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphicsProtocol;

STATIC UINT8  *BackBuffer;
STATIC UINT32  CursorImageWidth,CursorImageHeight;
STATIC UINT32 *CursorImage;
STATIC UINT32  CursorPositionX,CursorPositionY;
STATIC UINT32 *FrameBuffer;
STATIC UINT32  FrameBufferWidth,FrameBufferHeight;

/**
  This function updates the cursor buffer when image beneath cursor has changed its content.
**/
EFI_STATUS
EFIAPI
UpdateCursorBuffer
(
  VOID
)
{
  UINT32 ActualCopyWidth =((CursorPositionX+CursorImageWidth)>FrameBufferWidth?
                            FrameBufferWidth-CursorPositionX:
                            CursorImageWidth);
  UINT32 ActualCopyHeight=((CursorPositionY+CursorImageHeight)>FrameBufferHeight?
                            FrameBufferHeight-CursorPositionY:
                            CursorImageHeight);
  //First, Copy the screen buffer into BackBuffer.
  for(UINT32 i=0;i<ActualCopyWidth;i++) {
    for(UINT32 j=0;j<ActualCopyHeight;j++) {
      BackBuffer[i*CursorImageWidth+j] = FrameBuffer[(CursorPositionY+i)*FrameBufferWidth+(CursorPositionX+j)];
    }
  }
  //Then, we do alpha blending.
  return AlphaBlendingArea(
    CursorImage,
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
  // Copy the buffer back.
  for(UINT32 i=0;i<OriginalCopyWidth;i++) {
    for(UINT32 j=0;j<OriginalCopyHeight;j++) {
      FrameBuffer[(CursorPositionY+i)*FrameBufferWidth+(CursorPositionX+j)] = BackBuffer[i*CursorImageWidth+j];
    }
  }
  // Generate new cursor.
  CursorPositionX = X;
  CursorPositionY = Y;
  return UpdateCursorBuffer();
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
  CursorImageWidth  = PcdGet32(CursorImageWidth);
  CursorImageHeight = PcdGet32(CursorImageHeight);
  CursorImage       = PcdGetPtr(CursorImage);
  if((CursorImageWidth!=0)&&(CursorImageHeight!=0)) {
    Status |= gBS->AllocatePool(EfiLoaderData,CursorImageWidth*CursorImageHeight*sizeof(UINT32),(VOID**)&BackBuffer);
  }
  if(EFI_ERROR(EFI_SUCCESS)) {
    gST->StdErr->OutputString(gST->StdErr,L"Cannot allocate buffer for cursor buffer.\r\n");
    return Status;
  }
  FrameBuffer = (UINT32*)(UINTN)(GraphicsProtocol->Mode->FrameBufferBase);
  FrameBufferWidth = GetScreenWidth();
  FrameBufferHeight = GetScreenHeight();
  return RegisterMessageHandler(MessageLooperMessageMouse,CursorMessageHandler);
}

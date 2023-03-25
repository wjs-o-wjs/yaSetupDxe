#include <Library/ComposerLib.h>
#include <Protocol/GraphicsOutput.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/FontLib.h>
#include <Library/PcdLib.h>

extern EFI_SYSTEM_TABLE *gST;
extern EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphicsProtocol;

double ScaleFactor=1.0;
UINT32 *FrameBuffer;

double
EFIAPI
GetScaleFactor
(
  VOID
)
{
  return ScaleFactor;
}

EFI_STATUS
EFIAPI
SetScaleFactor
(
  double NewScaleFactor
)
{
  ScaleFactor = NewScaleFactor;
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
ClearScreen
(
  UINT32 Color
)
{
  return FillRectangle(0,0,
    GraphicsProtocol->Mode->Info->HorizontalResolution,
    GraphicsProtocol->Mode->Info->VerticalResolution,
    Color
  );
}

EFI_STATUS
EFIAPI
FillRectangle
(
  UINT32 StartX,
  UINT32 StartY,
  UINT32 Width,
  UINT32 Height,
  UINT32 Color
)
{
  UINT32 FrameBufferWidth = GraphicsProtocol->Mode->Info->HorizontalResolution;
  //We may use some accelerated method here.
  for(UINT32 i=0;i<Height;i++) {
    for(UINT32 j=0;j<Width;j++) {
      FrameBuffer[(StartY+i)*FrameBufferWidth+(StartX+j)] = Color;
    }
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
RefreshPartialScreen
(
  UINT32 XOffset,
  UINT32 YOffset,
  UINT32 Width,
  UINT32 Height
)
{
  return GraphicsProtocol->Blt(
    GraphicsProtocol,
    (EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)FrameBuffer,
    EfiBltBufferToVideo,
    XOffset,
    YOffset,
    XOffset,
    YOffset,
    Width,
    Height,
    GraphicsProtocol->Mode->Info->HorizontalResolution*sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
  );
}

EFI_STATUS
EFIAPI
RefreshScreen
(
  VOID
)
{
  return GraphicsProtocol->Blt(
    GraphicsProtocol,
    (EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)FrameBuffer,
    EfiBltBufferToVideo,
    0,
    0,
    0,
    0,
    GraphicsProtocol->Mode->Info->HorizontalResolution,
    GraphicsProtocol->Mode->Info->VerticalResolution,
    GraphicsProtocol->Mode->Info->HorizontalResolution*sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
  );
}

EFI_STATUS
EFIAPI
DrawCaption
(
  IN UINT32 Height,
  IN UINT32 BackgroundColor,
  IN CONST CHAR16 *Title
)
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT32 BufferWidth,BufferHeight;
  UINT32 FrameBufferWidth = GraphicsProtocol->Mode->Info->HorizontalResolution;
  Status = FillRectangle(0,0,FrameBufferWidth,(UINT32)(Height*ScaleFactor),BackgroundColor);
  if(EFI_ERROR(Status)) {
    return Status;
  }
  UINT32 *Buffer;
  Status = RenderText(Title,PcdGet32 (CaptionTextSize),PcdGet32(PrimaryTextColor),&Buffer,&BufferWidth,&BufferHeight);
  UINT32 MarginLeft = (FrameBufferWidth-BufferWidth)/2;
  AlphaBlendingArea(Buffer,BufferWidth,BufferHeight,FrameBuffer+MarginLeft+10*FrameBufferWidth,FrameBufferWidth,BufferHeight,0,0,FrameBuffer+MarginLeft+10*FrameBufferWidth,FrameBufferWidth);
  RefreshScreen();
  return Status;
}
/**
  This function returns current screen width.
 **/
UINT32
EFIAPI
GetScreenWidth
(
  VOID
)
{
  return GraphicsProtocol->Mode->Info->HorizontalResolution;
}
UINT32
EFIAPI
GetScreenHeight
(
  VOID
)
{
  return GraphicsProtocol->Mode->Info->VerticalResolution;
}

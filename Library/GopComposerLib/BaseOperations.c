#include <Library/ComposerLib.h>
#include <Protocol/GraphicsOutput.h>
#include <Library/UefiLib.h>

extern EFI_SYSTEM_TABLE *gST;
extern EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphicsProtocol;

static double ScaleFactor=1.0;
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
    0
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
  Status = FillRectangle(0,0,GraphicsProtocol->Mode->Info->HorizontalResolution,Height,BackgroundColor);
  // TODO:Draw caption.
  Print(L"Title:%s\r\n",Title);
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

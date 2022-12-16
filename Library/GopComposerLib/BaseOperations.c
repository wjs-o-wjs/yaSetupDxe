#include <Library/ComposerLib.h>
#include <Protocol/GraphicsOutput.h>
#include <Library/UefiLib.h>

extern EFI_SYSTEM_TABLE *gST;
extern EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphicsProtocol;

static double ScaleFactor=1.0;

double
EFIAPI
GetScaleFactor (
  VOID
)
{
  return ScaleFactor;
}

EFI_STATUS
EFIAPI
SetScaleFactor (
  double NewScaleFactor
)
{
  ScaleFactor = NewScaleFactor;
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
ClearScreen (
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
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL Pixel = {
    .Red   =  Color&0xFF,
    .Green = (Color&0xFF00) >> 8,
    .Blue  = (Color&0xFF0000) >> 16
  };
  return GraphicsProtocol->Blt(
    GraphicsProtocol,
    &Pixel,
    EfiBltVideoFill,
    0,
    0,
    StartX,
    StartY,
    Width,
    Height,
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

#include <Library/ComposerLib.h>
#include <Protocol/GraphicsOutput.h>
#include <Library/UefiLib.h>
#include <Library/PcdLib.h>
#include <Library/MouseLib.h>
#include <Library/DebugLib.h>
extern EFI_SYSTEM_TABLE  *gST;
extern EFI_BOOT_SERVICES *gBS;

EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphicsProtocol;

extern
EFI_STATUS
EFIAPI
InitCursor
(
  VOID
);


EFI_STATUS
EFIAPI
InitComposer (
  IN OPTIONAL UINT32 DesiredScreenWidth,
  IN OPTIONAL UINT32 DesiredScreenHeight,
  IN OPTIONAL double DesiredScaleFactor
)
{
  EFI_STATUS Status = EFI_SUCCESS;
  Status = gST->BootServices->LocateProtocol(&gEfiGraphicsOutputProtocolGuid,NULL,(VOID**) &GraphicsProtocol);
  if(EFI_ERROR(Status)) {
    gST->StdErr->OutputString(gST->StdErr,L"This system DOES NOT support GOP!\r\n");
    return Status;
  }
  if( DesiredScreenHeight==0 || DesiredScreenWidth==0 ) {
    //Get Desired Resolution.
    DesiredScreenWidth  = GraphicsProtocol->Mode->Info->HorizontalResolution;
    DesiredScreenHeight = GraphicsProtocol->Mode->Info->VerticalResolution;
  }
  else {
    //Try to set the resolution.
    UINT32 ModeCount = GraphicsProtocol->Mode->MaxMode;
    UINTN  ModeInfoSize;
    for(UINT32 n=0;n<ModeCount;n++) {
      EFI_GRAPHICS_OUTPUT_MODE_INFORMATION  *GraphicsInformation;
      Status = GraphicsProtocol->QueryMode(GraphicsProtocol,n,&ModeInfoSize,&GraphicsInformation);
      if(EFI_ERROR(Status)) {
        gST->StdErr->OutputString(gST->StdErr,L"Cannot retrive the display information!\r\n");
        return Status;
      }
      if(GraphicsInformation->HorizontalResolution == DesiredScreenWidth
       &&GraphicsInformation->VerticalResolution   == DesiredScreenHeight) {
          Status = GraphicsProtocol->SetMode(GraphicsProtocol,n);
          if(EFI_ERROR(Status)) {
            gST->StdErr->OutputString(gST->StdErr,L"Cannot set the desired mode!\r\n");
            return Status;
          }
          break;
      }
    }
    // Check whether the graphic mode is set.
    if(GraphicsProtocol->Mode->Info->HorizontalResolution != DesiredScreenWidth
     ||GraphicsProtocol->Mode->Info->VerticalResolution   != DesiredScreenHeight) {
      gST->StdErr->OutputString(gST->StdErr,L"Failed to find the corresponding mode for your selection!\r\n");
      return EFI_UNSUPPORTED;
    }
  }

  // Calculate desired scale factor.
  if(DesiredScaleFactor!=0.0) {
    SetScaleFactor(DesiredScaleFactor);
  }
  else {
    UINT32 ScaleTargetW = PcdGet32(DesiredScaleTargetW);
    UINT32 ScaleTargetH = PcdGet32(DesiredScaleTargetH);
    double ScaleFactorW = DesiredScreenWidth/ScaleTargetW;
    double ScaleFactorH = DesiredScreenHeight/ScaleTargetH;
    //We choose the smaller one.
    DesiredScaleFactor = (ScaleFactorH<ScaleFactorW)?ScaleFactorH:ScaleFactorW;
    //If the scale factor is lower than 1, it means the screen resolution is lower than we expected, and we shall not scale it.
    if(DesiredScaleFactor<1.0) {
      DesiredScaleFactor = 1.0;
    }
    SetScaleFactor(DesiredScaleFactor);
  }

  Print(L"Chosen resolution:%dx%d\r\n",DesiredScreenWidth,DesiredScreenHeight);
  Status = gBS->AllocatePool(EfiLoaderData,DesiredScreenWidth*DesiredScreenHeight*sizeof(UINT32),(VOID**)&FrameBuffer);
  if(EFI_ERROR(Status)) {
    gST->StdErr->OutputString(gST->StdErr,L"Cannot allocate Framebuffer.\n");
    return Status;
  }
  ClearScreen(PcdGet32(BackgroudColor));
  DrawCaption(PcdGet32(WindowCaptionHeight),PcdGet32(WindowCaptionColor),PcdGetPtr(SetupWindowTitle));
  RefreshScreen();
  return InitCursor();
}

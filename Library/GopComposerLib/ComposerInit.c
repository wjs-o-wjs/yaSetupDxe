#include <Library/ComposerLib.h>
#include <Protocol/GraphicsOutput.h>
#include <Library/UefiLib.h>
#include <Library/PcdLib.h>
extern EFI_SYSTEM_TABLE *gST;
EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphicsProtocol;

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
    gST->ConOut->OutputString(gST->ConOut,L"This system DOES NOT support GOP!\r\n");
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
        gST->ConOut->OutputString(gST->ConOut,L"Cannot retrive the display information!\r\n");
        return Status;
      }
      if(GraphicsInformation->HorizontalResolution == DesiredScreenWidth
       &&GraphicsInformation->VerticalResolution   == DesiredScreenHeight) {
          Status = GraphicsProtocol->SetMode(GraphicsProtocol,n);
          if(EFI_ERROR(Status)) {
            gST->ConOut->OutputString(gST->ConOut,L"Cannot set the desired mode!\r\n");
            return Status;
          }
          break;
      }
    }
    // Check whether the graphic mode is set.
    if(GraphicsProtocol->Mode->Info->HorizontalResolution != DesiredScreenWidth
     ||GraphicsProtocol->Mode->Info->VerticalResolution   != DesiredScreenHeight) {
      gST->ConOut->OutputString(gST->ConOut,L"Failed to find the corresponding mode for your selection!\r\n");
      return EFI_UNSUPPORTED;
    }
  }
  Print(L"Chosen resolution:%dx%d\r\n",DesiredScreenWidth,DesiredScreenHeight);
  ClearScreen(PcdGet32(BackgroudColor));
  DrawCaption(PcdGet16(WindowCaptionHeight),PcdGet32(WindowCaptionColor),PcdGetPtr(SetupWindowTitle));
  (void) DesiredScaleFactor;
  return Status;
}

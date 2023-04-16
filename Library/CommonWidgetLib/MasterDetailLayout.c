/** @file
  Functions that implements the Master-Detail layout.
  SPDX-License-Identifier: WTFPL
**/

#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>

#include <Library/CommonWidgets/MasterDetailLayout.h>
#include <Library/MemoryAllocationLib.h>

EFI_STATUS
EFIAPI
MasterDetailLayoutOnClick
(
  IN COMMON_WIDGET     *Instance,
  IN UINT32             RelativeX,
  IN UINT32             RelativeY,
  IN MOUSE_CLICK_STATUS Status
)
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
MasterDetailLayoutOnHover
(
  IN COMMON_WIDGET     *Instance,
  IN UINT32             RelativeX,
  IN UINT32             RelativeY
)
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
MasterDetailLayoutOnActivate
(
  IN COMMON_WIDGET     *Instance
)
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
MasterDetailLayoutOnDeactivate
(
  IN COMMON_WIDGET     *Instance
)
{
  return EFI_SUCCESS;
}

STATIC
VOID
FillInInvalidRange
(
  IN UINT32*  Region,
  IN UINT32   Width,
  IN UINT32   Height,
  IN UINT32   PixelsPerLine,
  IN UINT32   Color
)
{
  while(Height) {
    SetMem32(Region,Width*sizeof(UINT32),Color);
    Region+=PixelsPerLine;
    Height--;
  }
}
EFI_STATUS
EFIAPI
MasterDetailLayoutOnResize
(
  COMMON_WIDGET  *Instance,
  UINT32          NewWidth,
  UINT32          NewHeight
)
{
  if(Instance->Buffer) {
    FreePool(Instance->Buffer);
  }
  Instance->Height = NewHeight;
  Instance->Width  = NewWidth;
  if(!Instance->Height&&!Instance->Width) {
    return EFI_SUCCESS;
  }
  Instance->Buffer = AllocatePool(NewHeight*NewWidth*sizeof(UINT32));
  MASTER_DETAIL_LAYOUT * Layout = (MASTER_DETAIL_LAYOUT*)Instance;
  UINT32 MasterValue=0,DetailValue=0;
  if(Layout->MasterDetailRatio < 0) {
    Layout->MasterDetailRatio = 0;
  }
  if(Layout->MasterDetailRatio > 1) {
    Layout->MasterDetailRatio = 1;
  }
  if(Layout->Orientation == LayoutOrientationHorizontal) {
    MasterValue = NewWidth*Layout->MasterDetailRatio;
    DetailValue = NewWidth-MasterValue;
    if(Layout->MasterWidget) {
      Layout->MasterWidget->OnResize(Layout->MasterWidget,MasterValue,NewHeight);
      UINT32 i = NewHeight-1;
      while(i) {
        CopyMem(Instance->Buffer+i*NewWidth,
                Layout->MasterWidget->Buffer+MasterValue*i,MasterValue*sizeof(UINT32));
        i--;
      }
    }
    else {
      FillInInvalidRange(Instance->Buffer,MasterValue,NewHeight,NewWidth,Layout->DefaultColor);
    }
    if(Layout->DetailWidget) {
      Layout->DetailWidget->OnResize(Layout->DetailWidget,DetailValue,NewHeight);
      UINT32 i = NewHeight-1;
      while(i) {
        CopyMem(Instance->Buffer+i*NewWidth+MasterValue,
                Layout->MasterWidget->Buffer+DetailValue*i,DetailValue*sizeof(UINT32));
        i--;
      }
    }
    else {
      FillInInvalidRange(Instance->Buffer+MasterValue,
                         DetailValue,NewHeight,NewWidth,Layout->DefaultColor);
    }
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
MasterDetailLayoutOnRepaint
(
  COMMON_WIDGET  *Instance,
  UINT32          RepaintBeginX,
  UINT32          RepaintBeginY,
  UINT32          RepaintWidth,
  UINT32          RepaintHeight
)
{
  return EFI_SUCCESS;
}
EFI_STATUS
EFIAPI
InitializeMasterDetailLayout
(
  IN OUT MASTER_DETAIL_LAYOUT *Instance
)
{
  SetMem(Instance,sizeof(MASTER_DETAIL_LAYOUT),0x00);
  Instance->CommonLayout.CommonWidget.OnClick      = MasterDetailLayoutOnClick;
  Instance->CommonLayout.CommonWidget.OnHover      = MasterDetailLayoutOnHover;
  Instance->CommonLayout.CommonWidget.OnResize     = MasterDetailLayoutOnResize;
  Instance->CommonLayout.CommonWidget.OnRepaint    = MasterDetailLayoutOnRepaint;
  Instance->CommonLayout.CommonWidget.OnActivate   = MasterDetailLayoutOnActivate;
  Instance->CommonLayout.CommonWidget.OnDeactivate = MasterDetailLayoutOnDeactivate;
  Instance->CommonLayout.CommonWidget.Buffer       = NULL;
  return EFI_SUCCESS;
}

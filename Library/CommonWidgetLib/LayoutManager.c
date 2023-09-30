/** @file
  Layout manager for the Widget-layout system.
  SPDX-License-Identifier: WTFPL
**/

#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>

#include <Library/CommonWidgetLib.h>
#include <Library/CommonWidgets/NaiveWidget.h>
#include <Library/ComposerLib.h>
#include <Library/CommonWidgets/MasterDetailLayout.h>
#include <Library/CommonWidgets/TextLabel.h>

COMMON_WIDGET *RootWidget;

BOOLEAN
EFIAPI
CheckChildWidgetFitsInParent
(
  COMMON_WIDGET *Parent,
  COMMON_WIDGET *Child
)
{
  return ((Child->OffsetX>=Parent->Width)||(Child->OffsetY>=Parent->Height));
}

EFI_STATUS
EFIAPI
CheckChildWidgetInParentDrawingArea
(
  COMMON_WIDGET *Parent,
  COMMON_WIDGET *Child,
  UINT32         DrawingOffsetX,
  UINT32         DrawingOffsetY,
  UINT32         DrawingWidth,
  UINT32         DrawingHeight,
  UINT32        *ChildDrawingOffsetX OPTIONAL,
  UINT32        *ChildDrawingOffsetY OPTIONAL,
  UINT32        *ChildDrawingWidth   OPTIONAL,
  UINT32        *ChildDrawingHeight  OPTIONAL
)
{
  INT64 RegionX,RegionY,Width,Height;
  RegionX = DrawingOffsetX - Child->OffsetX;
  RegionY = DrawingOffsetY - Child->OffsetY;
  if(RegionX < 0) RegionX = 0;
  if(RegionY < 0) RegionY = 0;
  Width  = DrawingOffsetX + DrawingWidth  - Child->OffsetX;
  Height = DrawingOffsetY + DrawingHeight - Child->OffsetY;
  if(Width >Child->Width)  Width = Child->Width;
  if(Height>Child->Height)Height = Child->Height;
  if(Width<=0 || Height<=0) {
    return EFI_BUFFER_TOO_SMALL;
  }
  (void)(ChildDrawingOffsetX || (*ChildDrawingOffsetX = (UINT32)RegionX));
  (void)(ChildDrawingOffsetY || (*ChildDrawingOffsetY = (UINT32)RegionY));
  (void)(ChildDrawingWidth   || (*ChildDrawingWidth   = (UINT32)Width));
  (void)(ChildDrawingHeight  || (*ChildDrawingHeight  = (UINT32)Height));
  return EFI_SUCCESS;
}
EFI_STATUS
EFIAPI
UpdateRootLayout
(
  VOID
)
{
  CopyMem(FrameBuffer+CaptionHeight*GetScreenWidth(),
          RootWidget->Buffer,
          RootWidget->Width*RootWidget->Height*sizeof(UINT32));
  return RefreshPartialScreen(0,CaptionHeight,RootWidget->Width,RootWidget->Height);
}
EFI_STATUS
EFIAPI
InitLayout
(
  VOID
)
{
  RootWidget = AllocatePool(sizeof(MASTER_DETAIL_LAYOUT));
  EFI_STATUS Status = InitializeWidget (MasterDetailLayout,(MASTER_DETAIL_LAYOUT*)RootWidget);
  if(EFI_ERROR(Status)) {
    DEBUG ((DEBUG_ERROR,"Cannot Initialize Root Widget!\n"));
    return Status;
  }
  ((MASTER_DETAIL_LAYOUT*)RootWidget)->DefaultColor = 0xffccaa00;
  ((MASTER_DETAIL_LAYOUT*)RootWidget)->MasterDetailRatio = 0.3;
  COMMON_WIDGET *MasterLayout = AllocatePool(sizeof(TEXT_LABEL));
  Status = InitializeWidget (TextLabel,(TEXT_LABEL*)MasterLayout);
  if(EFI_ERROR(Status)) {
    DEBUG ((DEBUG_ERROR,"Cannot Initialize Master Widget!\n"));
    return Status;
  }
  ((TEXT_LABEL*)MasterLayout)->BackgroudColor = 0xff33aa99;
  ((TEXT_LABEL*)MasterLayout)->TextColor      = 0xff000000;
  ((TEXT_LABEL*)MasterLayout)->FontSize       = 16;
  ((TEXT_LABEL*)MasterLayout)->Text           = L"Test text label";
  ((TEXT_LABEL*)MasterLayout)->Common.HorizontalGravitity = LayoutGravityEnd;
  ((TEXT_LABEL*)MasterLayout)->Common.VerticalGravitity   = LayoutGravityCenter;
  ((MASTER_DETAIL_LAYOUT*)RootWidget)->MasterWidget = MasterLayout;
  Status = RootWidget->OnResize(RootWidget,GetScreenWidth(),GetScreenHeight()-CaptionHeight);
  if(EFI_ERROR(Status)) {
    DEBUG ((DEBUG_ERROR,"Cannot Resize Root Widget!\n"));
    return Status;
  }
  return UpdateRootLayout();
}

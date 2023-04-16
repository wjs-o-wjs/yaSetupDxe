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

COMMON_WIDGET *RootWidget;

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
  COMMON_WIDGET *MasterLayout = AllocatePool(sizeof(NAIVE_WIDGET));
  Status = InitializeWidget (NaiveWidget,(NAIVE_WIDGET*)MasterLayout);
  if(EFI_ERROR(Status)) {
    DEBUG ((DEBUG_ERROR,"Cannot Initialize Master Widget!\n"));
    return Status;
  }
  ((NAIVE_WIDGET*)MasterLayout)->Color = 0xff33aa99;
  ((MASTER_DETAIL_LAYOUT*)RootWidget)->MasterWidget = MasterLayout;
  Status = RootWidget->OnResize(RootWidget,GetScreenWidth(),GetScreenHeight()-CaptionHeight);
  if(EFI_ERROR(Status)) {
    DEBUG ((DEBUG_ERROR,"Cannot Resize Root Widget!\n"));
    return Status;
  }
  return UpdateRootLayout();
}

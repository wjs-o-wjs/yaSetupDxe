/** @file
  Simple linear layout implementation.
  SPDX-License-Identifier: WTFPL
**/

#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>

#include <Library/CommonWidgets/LinearLayout.h>

EFI_STATUS
EFIAPI
LinearLayoutOnClick
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
LinearLayoutOnHover
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
LinearLayoutOnActivate
(
  IN COMMON_WIDGET     *Instance
)
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
LinearLayoutOnDeactivate
(
  IN COMMON_WIDGET     *Instance
)
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
LinearLayoutOnRepaint
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
LinearLayoutOnResize
(
  COMMON_WIDGET  *Instance,
  UINT32          NewWidth,
  UINT32          NewHeight
)
{
  if(NewWidth*NewHeight>Instance->Width*Instance->Height) {
    if(Instance->Buffer!=NULL) {
      FreePool(Instance->Buffer);
    }
    Instance->Buffer = AllocatePool(NewWidth*NewHeight*sizeof(UINT32));

    DEBUG ((DEBUG_INFO,"Doing children updates.\n"));
    // TODO: Call children updates.
    Instance->Width  = NewWidth;
    Instance->Height = NewHeight;
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
InitializeLinearLayout
(
  LINEAR_LAYOUT *Instance
)
{
  ZeroMem(Instance,sizeof(LINEAR_LAYOUT));
  Instance->CommonLayout.LayoutType = LinearLayout;
  Instance->CommonLayout.CommonWidget.OnClick      = LinearLayoutOnClick;
  Instance->CommonLayout.CommonWidget.OnHover      = LinearLayoutOnHover;
  Instance->CommonLayout.CommonWidget.OnResize     = LinearLayoutOnResize;
  Instance->CommonLayout.CommonWidget.OnRepaint    = LinearLayoutOnRepaint;
  Instance->CommonLayout.CommonWidget.OnActivate   = LinearLayoutOnActivate;
  Instance->CommonLayout.CommonWidget.OnDeactivate = LinearLayoutOnDeactivate;
  return EFI_SUCCESS;
}

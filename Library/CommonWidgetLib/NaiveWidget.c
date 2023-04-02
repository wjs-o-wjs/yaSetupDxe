/** @file
  Sources to implement a naive widget, which only has one pure color.
  This widget is for layout testing only.
  SPDX-License-Identifier: WTFPL
**/

#include <Library/CommonWidgets/NaiveWidget.h>
#include <Library/MemoryAllocationLib.h>

extern
VOID
SetMemInt32
(
  UINT32       *Buffer,
  CONST UINTN   BufferSize,
  CONST UINT32  Value
);

EFI_STATUS
EFIAPI
NaiveWidgetOnClick
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
NaiveWidgetOnHover
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
NaiveWidgetOnActivate
(
  IN COMMON_WIDGET     *Instance
)
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
NaiveWidgetOnDeactivate
(
  IN COMMON_WIDGET     *Instance
)
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
NaiveWidgetOnRepaint
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
NaiveWidgetOnResize
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
    SetMemInt32(Instance->Buffer,NewWidth*NewHeight,((NAIVE_WIDGET*)Instance)->Color);
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
InitializeNaiveWidget
(
  NAIVE_WIDGET *Instance
)
{
  Instance->Common.OnClick      = NaiveWidgetOnClick;
  Instance->Common.OnHover      = NaiveWidgetOnHover;
  Instance->Common.OnRepaint    = NaiveWidgetOnRepaint;
  Instance->Common.OnActivate   = NaiveWidgetOnActivate;
  Instance->Common.OnDeactivate = NaiveWidgetOnDeactivate;
  Instance->Common.Buffer       = NULL;
  return EFI_SUCCESS;
}


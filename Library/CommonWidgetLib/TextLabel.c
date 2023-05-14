/** @file
  A simple text label.
  SPDX-License-Identifier: WTFPL
**/

#include <Library/BaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>

#include <Library/CommonWidgets/TextLabel.h>
#include <Library/ComposerLib.h>
#include <Library/FontLib.h>

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
TextLabelOnClick
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
TextLabelOnHover
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
TextLabelOnActivate
(
  IN COMMON_WIDGET     *Instance
)
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
TextLabelOnDeactivate
(
  IN COMMON_WIDGET     *Instance
)
{
  return EFI_SUCCESS;
}

STATIC
EFI_STATUS
TextLabelRenderText
(
  IN TEXT_LABEL *Instance
)
{
  EFI_STATUS  Status;
  UINT32     *RenderBuffer;
  UINT32      RenderHeight,RenderWidth;
  Status = RenderText(Instance->Text,Instance->FontSize,Instance->TextColor,&RenderBuffer,&RenderWidth,&RenderHeight);
  if(Status != EFI_SUCCESS) {
    return Status;
  }
  SetMemInt32(Instance->Common.Buffer,
              Instance->Common.Height*Instance->Common.Width*sizeof(UINT32),
              Instance->BackgroudColor);
  Status = AlphaBlendingArea(
    RenderBuffer,RenderWidth,RenderHeight,
    Instance->Common.Buffer,Instance->Common.Width,Instance->Common.Height,
    0,0,Instance->Common.Buffer,Instance->Common.Width
  );
  return Status;
}

EFI_STATUS
EFIAPI
TextLabelOnRepaint
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
TextLabelOnResize
(
  COMMON_WIDGET  *Instance,
  UINT32          NewWidth,
  UINT32          NewHeight
)
{
  EFI_STATUS Status;
  if(Instance->Buffer!=NULL) {
    FreePool(Instance->Buffer);
  }
  Instance->Buffer = AllocatePool(NewWidth*NewHeight*sizeof(UINT32));
  Instance->Width  = NewWidth;
  Instance->Height = NewHeight;
  Status = TextLabelRenderText((TEXT_LABEL*)Instance);
  return Status;
}

EFI_STATUS
EFIAPI
InitializeTextLabel
(
  TEXT_LABEL  *Instance
)
{
  SetMem(Instance,sizeof(TEXT_LABEL),0x00);
  Instance->Common.OnClick      = TextLabelOnClick;
  Instance->Common.OnHover      = TextLabelOnHover;
  Instance->Common.OnResize     = TextLabelOnResize;
  Instance->Common.OnRepaint    = TextLabelOnRepaint;
  Instance->Common.OnActivate   = TextLabelOnActivate;
  Instance->Common.OnDeactivate = TextLabelOnDeactivate;
  Instance->Common.Buffer       = NULL;
  return EFI_SUCCESS;
}

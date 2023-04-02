/** @file
  Functions that implements the Master-Detail layout.
  SPDX-License-Identifier: WTFPL
**/

#include <Library/CommonWidgets/MasterDetailLayout.h>

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
  //Not so much work to do here.
  return EFI_SUCCESS;
}

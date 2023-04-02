/** @file
  Layout manager for the Widget-layout system.
  SPDX-License-Identifier: WTFPL
**/

#include <Library/MemoryAllocationLib.h>

#include <Library/CommonWidgetLib.h>
#include <Library/CommonWidgets/NaiveWidget.h>

COMMON_WIDGET *RootWidget;

EFI_STATUS
EFIAPI
InitLayout
(
  VOID
)
{
  // Create a naive widget for now.
  RootWidget = AllocatePool(sizeof(NAIVE_WIDGET));
  return InitializeWidget (NaiveWidget,(NAIVE_WIDGET*)RootWidget);
}

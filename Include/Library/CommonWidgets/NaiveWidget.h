/** @file
  Headers to define a naive widget, which only has one pure color.
  This widget is for layout testing only.
  SPDX-License-Identifier: WTFPL
**/
#ifndef NAIVE_H
#define NAIVE_H
#include <Library/CommonWidgetLib.h>

typedef struct {
  COMMON_WIDGET Common;
  UINT32        Color;
} NAIVE_WIDGET;

EFI_STATUS
EFIAPI
InitializeNaiveWidget
(
  NAIVE_WIDGET *Instance
);
#endif

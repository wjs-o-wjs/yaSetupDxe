/** @file
  Headers to define linear layout.
  SPDX-License-Identifier: WTFPL
**/
#ifndef LINEAR_H
#define LINEAR_H
#include <Library/CommonWidgetLib.h>

// The basic Linear Layout model.
typedef struct _LINEAR_LAYOUT {
  COMMON_LAYOUT       CommonLayout;
  LAYOUT_GRAVITY      GravityHorizontal;
  LAYOUT_GRAVITY      GravityVertical;
  LAYOUT_ORIENTATION  Orientation;
} LINEAR_LAYOUT;


#endif

#ifndef MOUSE_LIB
#define MOUSE_LIB
/** @file
  Headers to define the mouse library.
  SPDX-License-Identifier: WTFPL
**/

#include <Uefi.h>

/**
  The enum type of the mouse status.
**/
typedef enum {
  MOUSE_CLICK_NONE        = 0x0,
  MOUSE_CLICK_LEFT_DOWN   = 0x1,
  MOUSE_CLICK_RIGHT_DOWN  = 0x2,
  MOUSE_CLICK_MIDDLE_DOWN = 0x4,
  // Enums below shows the sudden release event of the mouse.
  MOUSE_CLICK_LEFT_UP     = 0x8,
  MOUSE_CLICK_RIGHT_UP    = 0x10,
  MOUSE_CLICK_MIDDLE_UP   = 0x20
} MOUSE_CLICK_STATUS;

/**
  The struct describing mouse status.
  For touchpad/Tablet compat, we use absolute position rather than relative one.
 **/
typedef struct _MOUSE_STATUS {
  MOUSE_CLICK_STATUS ClickStatus;
  UINT32             CurrentX;
  UINT32             CurrentY;
} MOUSE_STATUS;

/**
  The function that initializes mouse.
  @return  EFI_SUCCESS  on successful call.
  @return  Others       on failed call.
**/
EFI_STATUS
EFIAPI
InitMouse
(
  VOID
);

#endif

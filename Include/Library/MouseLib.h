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
  The overall mouse click handler for the mouse lib.
  The composer shall use this as a click entry.
**/
typedef
EFI_STATUS
(EFIAPI *MOUSE_LIB_CLICK_HANDLER)
(
  IN MOUSE_CLICK_STATUS Status
);

/**
  The overall mouse move handler for the mouse lib.
  The composer shall use this as a move entry.
**/
typedef
EFI_STATUS
(EFIAPI *MOUSE_LIB_MOVE_HANDLER)
(
  IN UINT32 X_OFFSET,
  IN UINT32 Y_OFFSET
);
/**
  The function that registers overall handler.
  @param ClickHandler   The callback function that handles click event.
  @param MoveHandler    The callback function that handles move event.
  @return  EFI_SUCCESS  on successful call.
  @return  Others       on failed call.
**/
EFI_STATUS
EFIAPI
RegisterMouseEventHandler
(
  IN MOUSE_LIB_CLICK_HANDLER ClickHandler,
  IN MOUSE_LIB_MOVE_HANDLER  MoveHandler
);

#endif

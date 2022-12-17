#ifndef KEYBOARD_H
#define KEYBOARD_H
/** @file
  Headers to define the Keyboard interface.
  SPDX-License-Identifier: WTFPL
**/

#include <Uefi.h>

typedef struct {
  UINT16    ScanCode;
  CHAR16    UnicodeChar;
} KEYBOARD_INPUT_KEY;
/**
  This function initializes Keyboard.
**/

EFI_STATUS
EFIAPI
InitKeyboard
(
  VOID
);
#endif

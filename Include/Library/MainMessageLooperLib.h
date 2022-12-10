#ifndef MAIN_EVENT_LOOPER
#define MAIN_EVENT_LOOPER
/** @file
  Headers to define main event looper lib.
  SPDX-License-Identifier: WTFPL
**/
#include <Uefi.h>

typedef enum {
  MessageLooperMessageMouse,
  MessageLooperMessageKeyboard,
  MessageLooperMessageEndApplication,
  // Other message types.....
  MessageLooperMessageTypeMax
} MESSAGE_LOOPER_MESSAGE_TYPE;

typedef
EFI_STATUS
(EFIAPI *MESSAGE_LOOPER_MESSAGE_HANDLER)
(
  IN MESSAGE_LOOPER_MESSAGE_TYPE  MessageType,
  IN OUT VOID                    *ExtraContent
);


typedef struct _MESSAGE_LOOPER_MESSAGE_STRUCTURE {
  MESSAGE_LOOPER_MESSAGE_TYPE               MessageType;
  OPTIONAL MESSAGE_LOOPER_MESSAGE_HANDLER  *Handler;
  OPTIONAL VOID                            *ExtraContent;
} MESSAGE_LOOPER_MESSAGE_STRUCTURE;


/**
  This function enters the main message loop.
 **/
EFI_STATUS
EFIAPI
EnterMainMessageLoop
(
  VOID
);

#endif

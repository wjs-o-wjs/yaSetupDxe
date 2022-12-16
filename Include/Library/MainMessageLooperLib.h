#ifndef MAIN_EVENT_LOOPER
#define MAIN_EVENT_LOOPER
/** @file
  Headers to define main event looper lib.
  SPDX-License-Identifier: WTFPL
**/
#include <Uefi.h>

typedef enum {
  // Framework Base Messages.
  MessageLooperMessageMouse,
  MessageLooperMessageKeyboard,
  MessageLooperMessageEndApplication,
  // .....
  // User-defined Base Messages.
  MessageLooperMessageUserDefinedNumBegin=1024,
  // .....
  MessageLooperMessageTypeMax=32767
} MESSAGE_LOOPER_MESSAGE_TYPE;


// As we use mechanisms similar to "Hooks" in Microsoft, we can decide whether we shall pass the message to the following message handler, or just stop the processing.
typedef enum {
  MessageLooperContinueForwardingMessages,
  MessageLooperStopForwardingMessages
} MESSAGE_LOOPER_MESSAGE_FORWARDING_METHOD;


typedef
EFI_STATUS
(EFIAPI *MESSAGE_LOOPER_MESSAGE_HANDLER)
(
  IN MESSAGE_LOOPER_MESSAGE_TYPE                 MessageType,
  IN OUT VOID                                   *ExtraContent,
  OUT MESSAGE_LOOPER_MESSAGE_FORWARDING_METHOD  *ForwardingMethod
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

/**
  This function puts one message into the cycle queue.
  @param  MessageType  The message type as defined in enum.
  @param  Handler      The optional target callback function for some types of message.
  @param  ExtraContent The optional context that will passed to the function.
  @returns             EFI_STATUS on success call
  @returns             Other on failure
 **/
EFI_STATUS
EFIAPI
SendMessage
(
  IN MESSAGE_LOOPER_MESSAGE_TYPE               MessageType,
  IN OPTIONAL MESSAGE_LOOPER_MESSAGE_HANDLER  *Handler,
  IN OPTIONAL VOID                            *ExtraContent
);

/**
  This function registers the message handler.
  @param  MessageType  The message type as defined in enum.
  @param  Handler      The target callback function for some types of message.
  @returns             EFI_STATUS on success call
  @returns             Other on failure
 **/

EFI_STATUS
EFIAPI
RegisterMessageHandler
(
  IN  MESSAGE_LOOPER_MESSAGE_TYPE      MessageType,
  IN  MESSAGE_LOOPER_MESSAGE_HANDLER  *Handler
);
#endif

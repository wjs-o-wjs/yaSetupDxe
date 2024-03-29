/** @file
  The main message looper structure that enables inter-connection between modules.
  SPDX-License-Identifier: WTFPL
**/

#include <Library/MainMessageLooperLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiLib.h>
extern EFI_SYSTEM_TABLE   *gST;
extern EFI_BOOT_SERVICES  *gBS;

extern
EFI_STATUS
InvokeMessageHandler
(
  IN  MESSAGE_LOOPER_MESSAGE_TYPE      MessageType,
  IN OPTIONAL VOID                    *ExtraContent
);


//So far, holding a cycle queue of 128 elements is REALLY enough.
static MESSAGE_LOOPER_MESSAGE_STRUCTURE MessageQueue[_PCD_VALUE_MessageQueueSize];
static volatile UINTN QueuePointerFront=0,QueuePointerBack=0;

#define MessageQueueFull() ((QueuePointerBack+1)==(QueuePointerFront))
#define MessageQueueEmpty() ((QueuePointerBack)==(QueuePointerFront))
#define MessageQueueNext(x) (((x)+1)%_PCD_VALUE_MessageQueueSize)


STATIC
VOID
MessageQueueEnqueue
(
  IN MESSAGE_LOOPER_MESSAGE_STRUCTURE* Message
)
{
  UINTN QueuePointerBackCurrent = QueuePointerBack;
  QueuePointerBack = MessageQueueNext(QueuePointerBack);
  CopyMem(&MessageQueue[QueuePointerBackCurrent],Message,sizeof(MESSAGE_LOOPER_MESSAGE_STRUCTURE));
}

STATIC
VOID
MessageQueueDequeue
(
  OUT MESSAGE_LOOPER_MESSAGE_STRUCTURE  *Buf
)
{
  UINTN QueuePointerFrontCurrent = QueuePointerFront;
  QueuePointerFront = MessageQueueNext(QueuePointerFront);
  CopyMem(Buf,&MessageQueue[QueuePointerFrontCurrent],sizeof(MESSAGE_LOOPER_MESSAGE_STRUCTURE));
}

STATIC EFI_EVENT MessageLooperEndEvent;
STATIC EFI_EVENT MessageLooperTimerEvent;

STATIC
VOID
EFIAPI
MessageLooperEvent
(
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
)
{
  MESSAGE_LOOPER_MESSAGE_STRUCTURE  Buf;
  MESSAGE_LOOPER_MESSAGE_FORWARDING_METHOD ForwardingMethod=MessageLooperContinueForwardingMessages;
  while(!MessageQueueEmpty()) {
    MessageQueueDequeue(&Buf);
    switch(Buf.MessageType) {
      case MessageLooperMessageEndApplication: {
        gBS->SignalEvent(MessageLooperEndEvent);
        break;
      }
      default: {
        if(Buf.Handler!=NULL) {
          Buf.Handler(Buf.MessageType,Buf.ExtraContent,&ForwardingMethod);
        }
        else {
          InvokeMessageHandler(Buf.MessageType,Buf.ExtraContent);
        }
      }
    }
  }
  (VOID)Event;
  (VOID)Context;
}

EFI_STATUS
EFIAPI
SendMessage
(
  IN MESSAGE_LOOPER_MESSAGE_TYPE               MessageType,
  IN OPTIONAL MESSAGE_LOOPER_MESSAGE_HANDLER   Handler,
  IN OPTIONAL VOID                            *ExtraContent
)
{
  MESSAGE_LOOPER_MESSAGE_STRUCTURE Buf;
  if(MessageQueueFull()) {
    return EFI_OUT_OF_RESOURCES;
  }
  Buf.MessageType  = MessageType;
  Buf.Handler      = Handler;
  Buf.ExtraContent = ExtraContent;
  MessageQueueEnqueue(&Buf);
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EnterMainMessageLoop
(
  VOID
)
{
  EFI_STATUS Status;
  // Create end Event.
  Status = gBS->CreateEvent(0,TPL_APPLICATION,NULL,NULL,&MessageLooperEndEvent);
  if(EFI_ERROR(Status)) {
    gST->StdErr->OutputString(gST->StdErr,L"Cannot create looper End Event.\r\n");
    return Status;
  }
  // Create timer Event.
  Status = gBS->CreateEvent(EVT_TIMER | EVT_NOTIFY_SIGNAL,
                            TPL_CALLBACK,
                            MessageLooperEvent,
                            NULL,
                            &MessageLooperTimerEvent);
  if(EFI_ERROR(Status)) {
    gST->StdErr->OutputString(gST->StdErr,L"Cannot create looper timer Event.\r\n");
    return Status;
  }
  Status = gBS->SetTimer(MessageLooperTimerEvent,TimerPeriodic,PcdGet64(MessageLooperPeriod));
  if(EFI_ERROR(Status)) {
    gST->StdErr->OutputString(gST->StdErr,L"Cannot start looper timer Event.\r\n");
    return Status;
  }
  // Create an end message for test.
  // SendMessage(MessageLooperMessageEndApplication,NULL,NULL);
  // begin to wait for loop.
  Status = gBS->WaitForEvent(1,&MessageLooperEndEvent,NULL);
  if(EFI_ERROR(Status)) {
    gST->StdErr->OutputString(gST->StdErr,L"Cannot start message looper Event.\r\n");
    return Status;
  }
  gBS->CloseEvent(MessageLooperTimerEvent);
  return Status;
}


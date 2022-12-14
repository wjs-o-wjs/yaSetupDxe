#include <Library/MainMessageLooperLib.h>
#include <Library/BaseMemoryLib.h>
extern EFI_SYSTEM_TABLE   *gST;
extern EFI_BOOT_SERVICES  *gBS;
//So far, holding a cycle queue of 128 elements is REALLY enough.
static MESSAGE_LOOPER_MESSAGE_STRUCTURE MessageQueue[_PCD_VALUE_MessageQueueSize];
static volatile UINTN QueuePointerFront=0,QueuePointerBack=0;

#define MessageQueueFull() ((QueuePointerBack+1)==(QueuePointerFront))
#define MessageQueueEmpty() ((QueuePointerBack)==(QueuePointerFront))
#define MessageQueueNext(x) (((x)+1)%_PCD_VALUE_MessageQueueSize)

//STATIC
VOID
MessageQueueEnqueue
(
  IN MESSAGE_LOOPER_MESSAGE_STRUCTURE* Message
)
{
  QueuePointerBack = MessageQueueNext(QueuePointerBack);
  CopyMem(&MessageQueue[QueuePointerBack],Message,sizeof(MESSAGE_LOOPER_MESSAGE_STRUCTURE));
}

//STATIC
VOID
MessageQueueDequeue
(
  OUT MESSAGE_LOOPER_MESSAGE_STRUCTURE  *buf
)
{
  CopyMem(buf,&MessageQueue[QueuePointerFront],sizeof(MESSAGE_LOOPER_MESSAGE_STRUCTURE));
  QueuePointerFront = MessageQueueNext(QueuePointerFront);
}

STATIC EFI_EVENT MessageLooperEndEvent;
STATIC EFI_EVENT MessageLooperTimerEvent;

//STATIC
VOID
EFIAPI
MessageLooperEvent
(
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
)
{
  gST->ConOut->OutputString(gST->ConOut,L"Looper event triggered.\r\n");
  (VOID)Event;
  (VOID)Context;
  // Test end event.
  static int i=0;
  i++;
  if(i==20) {
    gBS->SignalEvent(MessageLooperEndEvent);
  }
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
    gST->ConOut->OutputString(gST->ConOut,L"Cannot create looper End Event.\r\n");
    return Status;
  }
  // Create timer Event.
  Status = gBS->CreateEvent(EVT_TIMER | EVT_NOTIFY_SIGNAL,
                            TPL_CALLBACK,
                            MessageLooperEvent,
                            NULL,
                            &MessageLooperTimerEvent);
  if(EFI_ERROR(Status)) {
    gST->ConOut->OutputString(gST->ConOut,L"Cannot create looper timer Event.\r\n");
    return Status;
  }
  Status = gBS->SetTimer(MessageLooperTimerEvent,TimerPeriodic,PcdGet64(MessageLooperPeriod));
  if(EFI_ERROR(Status)) {
    gST->ConOut->OutputString(gST->ConOut,L"Cannot start looper timer Event.\r\n");
    return Status;
  }
  // begin to wait for loop.
  Status = gBS->WaitForEvent(1,&MessageLooperEndEvent,NULL);
  if(EFI_ERROR(Status)) {
    gST->ConOut->OutputString(gST->ConOut,L"Cannot start message looper Event.\r\n");
    return Status;
  }
  gBS->CloseEvent(MessageLooperTimerEvent);
  return Status;
}


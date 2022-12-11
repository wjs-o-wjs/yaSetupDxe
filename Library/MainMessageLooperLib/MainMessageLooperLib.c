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

//STATIC
VOID
EFIAPI
MessageLooperEvent
(
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
)
{
  gST->ConOut->OutputString(gST->ConOut,L"Looper event triggered.\n");

  (VOID)Event;
  (VOID)Context;
}

STATIC EFI_EVENT MessageLooperEndEvent;
//STATIC
VOID
EFIAPI
MessageLooperEndEventNull
(
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
)
{
  (VOID)Event;
  (VOID)Context;
  gBS->SignalEvent(MessageLooperEndEvent);
  return;
}
EFI_STATUS
EFIAPI
EnterMainMessageLoop
(
  VOID
)
{
  EFI_STATUS Status;
  //UINTN Index;
  gST->ConOut->OutputString(gST->ConOut,L"Entering Main Message Loop.\r\n");
  Status = gBS->CreateEvent(0,TPL_APPLICATION,MessageLooperEndEventNull,NULL,&MessageLooperEndEvent);
  if(EFI_ERROR(Status)) {
    gST->ConOut->OutputString(gST->ConOut,L"Cannot create Looper End Event.\r\n");
    return Status;
  }
  gST->ConOut->OutputString(gST->ConOut,L"Create Message loop done.\r\n");
  Status = gBS->WaitForEvent(1,MessageLooperEndEvent,NULL);
  if(EFI_ERROR(Status)) {
    gST->ConOut->OutputString(gST->ConOut,L"Cannot start message looper Event.\r\n");
    return Status;
  }
  return Status;
}


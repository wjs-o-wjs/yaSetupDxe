#include <Library/MainMessageLooperLib.h>
#include <Library/BaseMemoryLib.h>

extern EFI_SYSTEM_TABLE *gST;
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

EFI_STATUS
EFIAPI
EnterMainMessageLoop
(
  VOID
)
{
  gST->ConOut->OutputString(gST->ConOut,L"Entering Main Message Loop.\n");
  return EFI_SUCCESS;
}


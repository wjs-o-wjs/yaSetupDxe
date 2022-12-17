#include <Library/MainMessageLooperLib.h>
#include <Library/UefiLib.h>
/**
 *
 *  We use a 2-dimensional Linked list to store the handles.
 *  e.g.:
 *
 *  Message type 0 ------- Message Type 1 ------- Message Type 2 ........  MESSAGE_TYPE_LINKED_LIST
 *         |                      |
 *     Handler 1              Handler 1
 *                                |
 *                            Handler 2
 *                              .....
 *                       HANDLER_LINKED_LIST
 **/
struct _HANDLER_LINKED_LIST;
struct _MESSAGE_TYPE_LINKED_LIST;
typedef struct _HANDLER_LINKED_LIST {
  MESSAGE_LOOPER_MESSAGE_HANDLER    Handler;
  struct _HANDLER_LINKED_LIST      *Next;
} HANDLER_LINKED_LIST;

typedef struct _MESSAGE_TYPE_LINKED_LIST {
  MESSAGE_LOOPER_MESSAGE_TYPE       MessageType;
  HANDLER_LINKED_LIST               HandlerEntry;
  HANDLER_LINKED_LIST              *HandlerTail;
  struct _MESSAGE_TYPE_LINKED_LIST *Next;
} MESSAGE_TYPE_LINKED_LIST;

extern EFI_BOOT_SERVICES  *gBS;
extern EFI_SYSTEM_TABLE   *gST;
STATIC struct {
  MESSAGE_TYPE_LINKED_LIST  Head;
  MESSAGE_TYPE_LINKED_LIST *Tail;
} MessageTypeLinkedList = {
    .Tail = &(MessageTypeLinkedList.Head),
    .Head.Next = NULL
};
STATIC
MESSAGE_TYPE_LINKED_LIST*
GetHandlerLinkedList
(
  IN  MESSAGE_LOOPER_MESSAGE_TYPE      MessageType
)
{
  MESSAGE_TYPE_LINKED_LIST* Start = MessageTypeLinkedList.Head.Next;
  while(Start!=NULL) {
    Print(L"Type:%x <->%x\n",Start->MessageType,MessageType);
    if(Start->MessageType == MessageType) {
      return Start;
    }
    Start = Start->Next;
  }
  return NULL;
}

EFI_STATUS
EFIAPI
RegisterMessageHandler
(
  IN  MESSAGE_LOOPER_MESSAGE_TYPE      MessageType,
  IN  MESSAGE_LOOPER_MESSAGE_HANDLER   Handler
)
{
  MESSAGE_TYPE_LINKED_LIST *TypeLinkedList;
  HANDLER_LINKED_LIST      *HandlerLinkedList;
  EFI_STATUS                Status;
  // Find the target HANDLER_LINKED_LIST.
  TypeLinkedList = GetHandlerLinkedList(MessageType);
  if(TypeLinkedList==NULL) {
    // Create a new type.
    Status = gBS->AllocatePool(EfiLoaderData,sizeof(MESSAGE_TYPE_LINKED_LIST),(VOID**)&TypeLinkedList);
    if(EFI_ERROR(Status)) {
      gST->StdErr->OutputString(gST->StdErr,L"Cannot create buffer for MESSAGE_TYPE_LINKED_LIST.\r\n");
      return Status;
    }
    TypeLinkedList->MessageType = MessageType;
    TypeLinkedList->Next        = NULL;
    TypeLinkedList->HandlerTail = &(TypeLinkedList->HandlerEntry);
    // Insert it.
    MessageTypeLinkedList.Tail->Next = TypeLinkedList;
    MessageTypeLinkedList.Tail       = TypeLinkedList;
  }
  // Insert the event.
  Status = gBS->AllocatePool(EfiLoaderData,sizeof(HANDLER_LINKED_LIST),(VOID**)&HandlerLinkedList);
  if(EFI_ERROR(Status)) {
    gST->StdErr->OutputString(gST->StdErr,L"Cannot create buffer for HANDLER_LINKED_LIST.\r\n");
    return Status;
  }
  HandlerLinkedList->Next           = NULL;
  HandlerLinkedList->Handler        = Handler;
  TypeLinkedList->HandlerTail->Next = HandlerLinkedList;
  TypeLinkedList->HandlerTail       = HandlerLinkedList;
  return EFI_SUCCESS;
}

EFI_STATUS
InvokeMessageHandler
(
  IN  MESSAGE_LOOPER_MESSAGE_TYPE      MessageType,
  IN OPTIONAL VOID                    *ExtraContent
)
{
  MESSAGE_TYPE_LINKED_LIST                 *TypeLinkedList;
  HANDLER_LINKED_LIST                      *HandlerLinkedList;
  MESSAGE_LOOPER_MESSAGE_FORWARDING_METHOD  ForwardingMethod = MessageLooperContinueForwardingMessages;
  // Find the target HANDLER_LINKED_LIST.
  Print(L"Get Type Linked List.\r\n");
  TypeLinkedList = GetHandlerLinkedList(MessageType);
  if(TypeLinkedList==NULL) {
    return EFI_NOT_FOUND;
  }
  HandlerLinkedList = TypeLinkedList->HandlerEntry.Next;
  while((HandlerLinkedList!=NULL)&&(ForwardingMethod==MessageLooperContinueForwardingMessages)) {
    Print(L"Invoking Handler.\r\n");
    HandlerLinkedList->Handler(MessageType,ExtraContent,&ForwardingMethod);
    HandlerLinkedList = HandlerLinkedList->Next;
  }
  return EFI_SUCCESS;
}

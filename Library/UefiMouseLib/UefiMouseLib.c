/* 该模块存在BUG，在macOS qemu上无法测试功能，暂时停止开发
 *
 *
*/

#include "UefiMouseLib.h"


EFI_GUID spp_guid = {0x31878c87, 0xb75, 0x11d5, {0x9a, 0x4f, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};

EFI_STATUS
EFIAPI
MouseServiceInitSimplePointerProtocol(IN MouseService * Service)
{
    EFI_SIMPLE_POINTER_PROTOCOL * SPP = NULL;

    Service->SystemTable->BootServices->LocateProtocol(&spp_guid,NULL,(void **)&SPP);
    Service->SPP = SPP;
    return (Service->SPP != NULL)? EFI_SUCCESS : EFI_ABORTED;
}
/*
uint64_t GetMouseState(OUT EFI_SIMPLE_POINTER_STATE *SimplePointerState){
    if (SPP == NULL) return 0;
    uint64_t status = SPP->GetState(SPP,SimplePointerState);
    return status;
}
*/
//EFI_STATUS EFIAPI 
VOID
EFIAPI
MouseServiceHandler(IN EFI_EVENT Event,IN void *Context){
    MouseService * Service = (MouseService *) Context;
    //UINTN WaitIdx = 0;
    if (Service == NULL) {
        Print(L"ERR: The first MouseServiceHandler's service arguement is NullPointer.");
        return;
    }
    Print(L"asdasd");
    while(1){
        EFI_SIMPLE_POINTER_STATE s;/*
        UINTN WaitIdx = 0;
        Service->SystemTable->BootServices->WaitForEvent(
            1,
            &(Service->SPP->WaitForInput),
            &WaitIdx
        );
        */
        uint64_t status = Service->SPP->GetState(Service->SPP, &s);
        Print(L"%p\n",status);
        Print(L"%p\n",s.RelativeMovementX);
        
    }

}

EFI_STATUS
EFIAPI
MouseServiceStartTimer(IN MouseService * Service){
    if (Service == NULL)
        return EFI_ABORTED;
    uint64_t status = Service->SystemTable->BootServices->SetTimer(Service->Event,TimerRelative,0);
    return (EFI_ERROR(status))? EFI_ABORTED : EFI_SUCCESS;
}

MouseService *
EFIAPI
CreateMouseService(IN EFI_SYSTEM_TABLE *SystemTable){
    if (SystemTable == NULL) return NULL;
    MouseService * Service;

    // Alloc service's memory
    SystemTable->BootServices->AllocatePool(EfiLoaderData,sizeof(MouseService),(void **)&Service);
    if (Service == NULL) return NULL;
    
    // Init service's data
    SystemTable->BootServices->SetMem(Service,sizeof(MouseService),0x0);
    Service->SystemTable = SystemTable;
    Service->CursorPostion.x = CURSOR_DEFAULT_X;
    Service->CursorPostion.x = CURSOR_DEFAULT_Y;
    Service->MouseServiceStatus = MouseServiceStatusReady;
    Service->StartTimer = MouseServiceStartTimer;
    Service->InitSimplePointerProtocol = MouseServiceInitSimplePointerProtocol;

    // Create event to deal with mouse service
    uint64_t status = SystemTable->BootServices->CreateEvent(
        EVT_TIMER | EVT_NOTIFY_SIGNAL,
        TPL_NOTIFY,
        MouseServiceHandler,
        Service,
        &Service->Event
    );

    if (EFI_ERROR(status)) return NULL;

    return Service;
}
#include "UefiAsyncTimerLib.h"

VOID
EFIAPI
TimerServiceCaller(IN EFI_EVENT Event,IN void *Context){
    TimerService * timer_caller_service = (TimerService *) Context;
    timer_caller_service->CallbackFuncPointer(timer_caller_service->CallbackFuncArgv,timer_caller_service->Event);
}

EFI_STATUS
EFIAPI
TimerServiceSetTimer(TimerService * Service){
    uint64_t status;
    status = Service->SystemTable->BootServices->SetTimer(Service->Event,TimerPeriodic, Service->Tick);
    return (EFI_ERROR(status)) ? EFI_ABORTED : EFI_SUCCESS;
}

TimerService *
EFIAPI
TimerServiceSetTick(IN TimerService * Service,IN uint32_t Tick){
    Service->Tick = Tick;
    return Service;
}

TimerService *
EFIAPI
TimerServiceSetCallback(IN TimerService * Service, IN void * FuncPointer,IN void * FuncArgv){
    Service->CallbackFuncArgv = FuncArgv;
    Service->CallbackFuncPointer = FuncPointer;
    return Service;
}


TimerService *
EFIAPI
CreateTimerService(IN EFI_SYSTEM_TABLE *SystemTable){
    uint64_t status;
    TimerService * timer_service;

    SystemTable->BootServices->AllocatePool(EfiLoaderData,sizeof(TimerService),(void **) &timer_service);
    timer_service->SystemTable = SystemTable;
    timer_service->SetCallback = TimerServiceSetCallback;
    timer_service->SetTick = TimerServiceSetTick;
    timer_service->SetTimer = TimerServiceSetTimer;

    if (timer_service == NULL)
        return NULL;
    
    status = SystemTable->BootServices->CreateEvent(
        EVT_TIMER | EVT_NOTIFY_SIGNAL,
        TPL_CALLBACK,
        TimerServiceCaller,
        timer_service,
        &timer_service->Event
    );

    if (EFI_ERROR(status))
        return NULL;

    return timer_service;
}
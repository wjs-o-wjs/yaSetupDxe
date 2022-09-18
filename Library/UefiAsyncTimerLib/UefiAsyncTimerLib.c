#include "UefiAsyncTimerLib.h"
VOID
EFIAPI
TimerServiceCaller(IN EFI_EVENT Event,IN void *Context){
    TimerService * timer_caller_service = (TimerService *) Context;
    InterlockedIncrement(&timer_caller_service->atomic_lock);
    timer_caller_service->CallbackFuncPointer(timer_caller_service->CallbackFuncArgv,timer_caller_service->Event);
    InterlockedDecrement(&timer_caller_service->atomic_lock);
    if (timer_caller_service->atomic_lock == 0 && timer_caller_service->TimerStatus == Stop){
        timer_caller_service->SystemTable->BootServices->FreePool(timer_caller_service);
    }
}

EFI_STATUS
EFIAPI
TimerServiceSetTimer(TimerService * Service){
    if (Service == NULL || Service->Tick == 0)
        return EFI_ABORTED;
    uint64_t status;
    status = Service->SystemTable->BootServices->SetTimer(Service->Event,TimerPeriodic, Service->Tick);
    return (EFI_ERROR(status)) ? EFI_ABORTED : (Service->TimerStatus = Running,EFI_SUCCESS);
}


EFI_STATUS
EFIAPI
TimerServiceStopTimer(TimerService * Service){
    if (Service == NULL)
        return EFI_ABORTED;
    Service->TimerStatus = Stop;
    return Service->SystemTable->BootServices->CloseEvent(Service->Event);
}

TimerService *
EFIAPI
TimerServiceSetTick(IN TimerService * Service,IN uint32_t Tick){
    if (Service == NULL)
        return NULL;
    Service->Tick = Tick;
    return Service;
}

TimerService *
EFIAPI
TimerServiceSetCallback(IN TimerService * Service, IN void * FuncPointer,IN void * FuncArgv){
    if (Service == NULL)
        return NULL;
    Service->CallbackFuncArgv = FuncArgv;
    Service->CallbackFuncPointer = FuncPointer;
    return Service;
}


TimerService *
EFIAPI
CreateTimerService(IN EFI_SYSTEM_TABLE *SystemTable){
    if (SystemTable == NULL)
        return NULL;
    uint64_t status;
    TimerService * timer_service;

    SystemTable->BootServices->AllocatePool(EfiLoaderData,sizeof(TimerService),(void **) &timer_service);
    if (timer_service == NULL)
        return NULL;
    
    SystemTable->BootServices->SetMem((VOID *)timer_service,sizeof(TimerService),0);
    timer_service->SystemTable = SystemTable;
    timer_service->SetCallback = TimerServiceSetCallback;
    timer_service->SetTick = TimerServiceSetTick;
    timer_service->SetTimer = TimerServiceSetTimer;
    timer_service->TimerStatus = Ready;
    timer_service->StopTimer = TimerServiceStopTimer;


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
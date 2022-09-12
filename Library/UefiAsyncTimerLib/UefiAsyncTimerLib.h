#ifndef UEFI_ASYNC_TIMER_LIB_H
#define UEFI_ASYNC_TIMER_LIB_H

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <stdint.h>

typedef struct TimerService{
    VOID EFIAPI (*CallbackFuncPointer)(void *,void *);
    void * CallbackFuncArgv;
    void * Event;
    uint32_t Tick;
    EFI_STATUS EFIAPI (*SetTimer)(struct TimerService *);
    EFI_SYSTEM_TABLE *SystemTable;
    struct TimerService * EFIAPI (*SetTick)(struct TimerService *, uint32_t Tick);
    struct TimerService * EFIAPI (*SetCallback)(IN struct TimerService * Service, IN void * FuncPointer,IN void * FuncArgv);
} TimerService;

VOID EFIAPI TimerServiceCaller(IN EFI_EVENT event,IN void *context);
EFI_STATUS EFIAPI TimerServiceSetTimer(TimerService * ate_caller_service);
TimerService * EFIAPI CreateTimerService      (IN EFI_SYSTEM_TABLE *SystemTable);
TimerService * EFIAPI TimerServiceSetCallback (IN TimerService * Service, IN void * FuncPointer,IN void * FuncArgv);
TimerService * EFIAPI TimerServiceSetTick     (IN TimerService * Service,IN uint32_t Tick);
#endif


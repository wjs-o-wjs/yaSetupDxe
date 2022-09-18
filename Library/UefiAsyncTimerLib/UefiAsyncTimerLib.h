#ifndef UEFI_ASYNC_TIMER_LIB_H
#define UEFI_ASYNC_TIMER_LIB_H

#include <Uefi.h>
#include <stdint.h>

enum TimerStatus{
    Ready=0,
    Stop=1,
    Running=2,
};

typedef struct TimerService{
    VOID EFIAPI (*CallbackFuncPointer)(void *,void *);
    void * CallbackFuncArgv;
    void * Event;
    uint32_t Tick;
    EFI_STATUS EFIAPI (*SetTimer)(struct TimerService *);
    EFI_SYSTEM_TABLE *SystemTable;
    struct TimerService * EFIAPI (*SetTick)(IN struct TimerService *, IN uint32_t Tick);
    struct TimerService * EFIAPI (*SetCallback)(IN struct TimerService * Service, IN void * FuncPointer,IN void * FuncArgv);
    EFI_STATUS EFIAPI (*StopTimer)(IN struct TimerService *);
    enum TimerStatus TimerStatus;
} TimerService;

VOID EFIAPI TimerServiceCaller(IN EFI_EVENT event,IN void *context);
EFI_STATUS EFIAPI TimerServiceSetTimer(IN TimerService * ate_caller_service);
TimerService * EFIAPI CreateTimerService      (IN EFI_SYSTEM_TABLE *SystemTable);
TimerService * EFIAPI TimerServiceSetCallback (IN TimerService * Service, IN void * FuncPointer,IN void * FuncArgv);
TimerService * EFIAPI TimerServiceSetTick     (IN TimerService * Service,IN uint32_t Tick);
EFI_STATUS EFIAPI TimerServiceSetStatus(TimerService * Service,enum TimerStatus timer_status);
#endif


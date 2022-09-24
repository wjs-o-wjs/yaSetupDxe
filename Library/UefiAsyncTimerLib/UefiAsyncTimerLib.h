#ifndef UEFI_ASYNC_TIMER_LIB_H
#define UEFI_ASYNC_TIMER_LIB_H

#include <Uefi.h>
#include <stdint.h>
#include <Library/UefiLib.h>
#include <Library/SynchronizationLib.h>

enum TimerStatus{
    TimerStatusReady=0,
    TimerStatusStop=1,
    TimerStatusRunning=2,
};

typedef struct TimerService{
    // Data
    void * CallbackFuncArgv;
    void * Event;
    uint32_t Tick;
    EFI_SYSTEM_TABLE *SystemTable;
    enum TimerStatus TimerStatus;
    uint32_t atomic_lock;

    // Function
    EFI_STATUS EFIAPI (*StartTimer)(struct TimerService *);
    struct TimerService * EFIAPI (*SetTick)(IN struct TimerService *, IN uint32_t Tick);
    struct TimerService * EFIAPI (*SetCallback)(IN struct TimerService * Service, IN void * FuncPointer,IN void * FuncArgv);
    EFI_STATUS EFIAPI (*StopTimer)(IN struct TimerService *);
    VOID EFIAPI (*CallbackFuncPointer)(void *,void *);
} TimerService;

VOID EFIAPI TimerServiceCaller(IN EFI_EVENT event,IN void *context);
EFI_STATUS EFIAPI TimerServiceStartTimer(IN TimerService * ate_caller_service);
TimerService * EFIAPI CreateTimerService      (IN EFI_SYSTEM_TABLE *SystemTable);
TimerService * EFIAPI TimerServiceSetCallback (IN TimerService * Service, IN void * FuncPointer,IN void * FuncArgv);
TimerService * EFIAPI TimerServiceSetTick     (IN TimerService * Service,IN uint32_t Tick);
EFI_STATUS EFIAPI TimerServiceSetStatus(TimerService * Service,enum TimerStatus timer_status);
#endif



#ifndef UEFI_MOUSE_LIB_H
#define UEFI_MOUSE_LIB_H
#include <Uefi.h>
#include <Protocol/SimplePointer.h>
#include <stdint.h>
#include <Library/UefiLib.h>

#define CURSOR_DEFAULT_X 0
#define CURSOR_DEFAULT_Y 0

// Define Enum
enum MouseServiceStatus{
    MouseServiceStatusReady=0,
    MouseServiceStatusStop=1,
    MouseServiceStatusRunning=2,
};

// Define Struct
typedef struct CursorPosition{
    uint32_t x;
    uint32_t y;
}CursorPosition;

typedef struct MouseService{
    // Data
    EFI_SYSTEM_TABLE *SystemTable;
    struct CursorPosition CursorPostion;
    enum MouseServiceStatus MouseServiceStatus;
    EFI_SIMPLE_POINTER_PROTOCOL * SPP;
    void * Event;

    // Function
    EFI_STATUS EFIAPI (*GetMouseDeltaPosition)(IN EFI_SYSTEM_TABLE *SystemTable);
    EFI_STATUS EFIAPI (*InitSimplePointerProtocol)(IN struct MouseService * Service);
    EFI_STATUS EFIAPI (*StartTimer)(IN struct MouseService * Service);
}MouseService;

// Define Function
EFI_STATUS EFIAPI MouseServiceInitSimplePointerProtocol(IN struct MouseService * Service);
uint64_t GetMouseState(OUT EFI_SIMPLE_POINTER_STATE *SimplePointerState);
MouseService * EFIAPI CreateMouseService(IN EFI_SYSTEM_TABLE *SystemTable);

#endif

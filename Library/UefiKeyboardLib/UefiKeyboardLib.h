#ifndef UEFI_KEYBOARD_LIB_H
#define UEFI_KEYBOARD_LIB_H

#include <Uefi.h>
#include <stdint.h>
#include <Library/UefiLib.h>
#include <Library/SynchronizationLib.h>

typedef struct KeyboardService{
    EFI_SYSTEM_TABLE *SystemTable;
    EFI_STATUS EFIAPI (*BindKey)(IN struct KeyboardService *,IN EFI_KEY_DATA * KeyData,IN void * KeyInputHandle,OUT void * NotifyHandle);

}KeyboardService;

KeyboardService * CreateKeyboardService(IN EFI_SYSTEM_TABLE * SystemTable);
EFI_STATUS EFIAPI KeyboardServiceBindKey(IN struct KeyboardService *,IN EFI_KEY_DATA * KeyData,IN void * KeyInputHandle,OUT void * NotifyHandle);
#endif
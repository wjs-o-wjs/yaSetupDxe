
#ifndef UEFI_MOUSE_LIB_H
#define UEFI_MOOUSE_LIB_H
#include <Uefi.h>
#include <Protocol/SimplePointer.h>
#include <stdint.h>

EFI_STATUS EFIAPI InitMouseSPP(IN EFI_SYSTEM_TABLE *SystemTable);
uint64_t GetMouseState(OUT EFI_SIMPLE_POINTER_STATE *SimplePointerState);

#endif

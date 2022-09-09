
#ifndef UEFI_MOUSE_LIB_H
#define UEFI_MOOUSE_LIB_H
#include <Uefi.h>
#include <Protocol/SimplePointer.h>


void InitMouseSPP(IN EFI_SYSTEM_TABLE *SystemTable);
unsigned long long GetMouseState(IN EFI_SYSTEM_TABLE *SystemTable,OUT EFI_SIMPLE_POINTER_STATE * SimplePointerState);

#endif

#ifndef UEFI_H
#define UEFI_H

#include <X64/ProcessorBind.h>
#include <Uefi.h>
#include <Library/UefiLib.h>
EFI_STATUS EFIAPI UefiMain(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable);

#endif


#include "UefiMouseLib.h"

EFI_SIMPLE_POINTER_PROTOCOL * SPP = NULL;
EFI_STATUS EFIAPI InitMouseSPP(IN EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_GUID spp_guid = {0x31878c87, 0xb75, 0x11d5, {0x9a, 0x4f, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
    SystemTable->BootServices->LocateProtocol(&spp_guid,NULL,(void **)&SPP);
    return (SPP != NULL)? EFI_SUCCESS : EFI_LOAD_ERROR;
}
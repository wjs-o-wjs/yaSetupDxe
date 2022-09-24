
#include "UefiKeyboardLib.h"

EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL * STIEP = NULL;

EFI_STATUS
EFIAPI
KeyboardServiceBindKey(
    IN struct KeyboardService * Service,
    IN EFI_KEY_DATA * KeyData,
    IN void * KeyInputHandle,
    OUT void * NotifyHandle
){
    return STIEP->RegisterKeyNotify(STIEP,KeyData,KeyInputHandle,NotifyHandle);
}


KeyboardService * CreateKeyboardService(IN EFI_SYSTEM_TABLE * SystemTable){
    // Check SystemTable NULL pointer
    if (SystemTable == NULL)
        return NULL;

    // get EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL by SystemTable
    EFI_GUID stiep_guid = {0xdd9e7534, 0x7762, 0x4698, { 0x8c, 0x14, 0xf5, 0x85, 0x17, 0xa6, 0x25, 0xaa } };
    SystemTable->BootServices->LocateProtocol(&stiep_guid,NULL,(void **)&STIEP);
    if (STIEP == NULL){
        return NULL;
    }

    // 
    KeyboardService * keyboard_service;
    SystemTable->BootServices->AllocatePool(EfiLoaderData,sizeof(KeyboardService),(void **) &keyboard_service);
    if (keyboard_service == NULL)
        return NULL;
    
    keyboard_service->BindKey = KeyboardServiceBindKey;
    keyboard_service->SystemTable = SystemTable;
    return keyboard_service;
}
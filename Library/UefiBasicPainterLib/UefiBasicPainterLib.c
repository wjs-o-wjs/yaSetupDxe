#include "UefiBasicPainterLib.h"

BasicPainterService *
EFIAPI
CreateBasicPainterService(IN EFI_SYSTEM_TABLE * SystemTable){
    BasicPainterService * Service;


    if (SystemTable == NULL) return NULL;


    SystemTable->BootServices->AllocatePool(EfiLoaderData,sizeof(BasicPainterService),(void **) &Service);
    if (Service == NULL) return NULL;


    SystemTable->BootServices->SetMem(Service,sizeof(BasicPainterService),0x0);
    Service->SystemTable = SystemTable;

    // Set Function Pointer
    Service->Draw = BasicPainterDraw;
    Service->SetColor = BasicPainterSetColor;
    Service->InitGraphicsOutputProtocol = InitGraphicsOutputProtocol;
    Service->SetDefaultColor = BasicPainterSetDefaultColor;
    Service->SetDefaultColorConfig = BasicPainterSetDefaultColorConfig;
    Service->SetStartPointer = BasicPainterSetStartPointer;
    Service->SetEndPointer = BasicPainterSetEndPointer;



    return Service;
}

EFI_STATUS
EFIAPI
InitGraphicsOutputProtocol(struct BasicPainterService * Service){
    EFI_GUID gop_guid = {0x9042a9de, 0x23dc, 0x4a38, {0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a}};
    Print(L"bbbb");
    EFI_STATUS Status = Service->SystemTable->BootServices->LocateProtocol(&gop_guid,NULL,(void **) &(Service->GOP));
    Print(L"aaaaaaa");
    return Status;

}


BasicPainterService *
EFIAPI
BasicPainterDraw(BasicPainterService * Service,enum BasicPointerDrawType DrawType){
    uint32_t HR = Service->GOP->Mode->Info->HorizontalResolution;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Base = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) Service->GOP->Mode->FrameBufferBase;
    switch(DrawType){
        case BasicPointerDrawTypePixel: {

            EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Pixel = Base + (HR * Service->StartPointer.y) + Service->StartPointer.x;
            Pixel->Blue = Service->Color.Blue;
            Pixel->Green = Service->Color.Blue;
            Pixel->Red = Service->Color.Red;
            Pixel->Reserved = Service->Color.Reserved;
            break;
        }
        default: {
            break;
        }
    }
    return Service;
}

BasicPainterService *
EFIAPI
BasicPainterSetColor(BasicPainterService * Service,uint8_t Red,uint8_t Blue,uint8_t Green,uint8_t Reserved){
    Service->Color.Blue  = Blue;
    Service->Color.Red   = Red;
    Service->Color.Green = Green;
    return Service;
}

BasicPainterService *
EFIAPI
BasicPainterSetDefaultColor(struct BasicPainterService * Service){
    Service->SystemTable->BootServices->CopyMem(&(Service->Color),&(Service->DefaultColor),sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
    return Service;
}

BasicPainterService *
EFIAPI
BasicPainterSetStartPointer(struct BasicPainterService * Service,uint32_t x,uint32_t y){
    Service->StartPointer.x = x;
    Service->StartPointer.y = y;
    return Service;
}

BasicPainterService *
EFIAPI
BasicPainterSetEndPointer(struct BasicPainterService * Service,uint32_t x,uint32_t y){
    Service->EndPointer.x = x;
    Service->EndPointer.y = y;
    return Service;
}


BasicPainterService *
EFIAPI
BasicPainterSetDefaultColorConfig(struct BasicPainterService * Service,uint8_t Red,uint8_t Blue,uint8_t Green,uint8_t Reserved){
    Service->DefaultColor.Blue  = Blue;
    Service->DefaultColor.Red   = Red;
    Service->DefaultColor.Green = Green;
    return Service;
}

/*



*/
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
    EFI_STATUS Status = Service->SystemTable->BootServices->LocateProtocol(&gop_guid,NULL,(void **) &(Service->GOP));
    return Status;

}

VOID
EFIAPI
BasicPainterDrawPixel(BasicPainterService * Service){
    uint32_t HR = Service->GOP->Mode->Info->HorizontalResolution;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Base = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) Service->GOP->Mode->FrameBufferBase;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Pixel = Base + (HR * Service->StartPointer.y) + Service->StartPointer.x;
    Pixel->Blue  = Service->Color.Blue;
    Pixel->Green = Service->Color.Blue;
    Pixel->Red   = Service->Color.Red;
    Pixel->Reserved = Service->Color.Reserved;
}

VOID
EFIAPI
BasicPainterDrawRect(BasicPainterService * Service){
    uint32_t HR = Service->GOP->Mode->Info->HorizontalResolution;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Base = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) Service->GOP->Mode->FrameBufferBase;
    uint32_t MinX=0, MinY=0, MaxX=0, MaxY=0;

    (Service->StartPointer.x < Service->EndPointer.x) ?
        (
            MinX = Service->StartPointer.x,
            MaxX = Service->EndPointer.x
        ):(
            MinX = Service->EndPointer.x,
            MaxX = Service->StartPointer.x
        );

    (Service->StartPointer.y < Service->EndPointer.y) ?
        (
            MinY = Service->StartPointer.y,
            MaxY = Service->EndPointer.y
        ):(
            MinY = Service->EndPointer.y,
            MaxY = Service->StartPointer.y
        );
    
    int TargetX;
    int TargetY;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Pixel;
    for(TargetX = MinX;TargetX <= MaxX;TargetX++){
        Pixel = Base + (HR * MinY) + TargetX;
        CopyBltPixelColor(Pixel,&Service->Color);

        Pixel = Base + (HR * MaxY) + TargetX;
        CopyBltPixelColor(Pixel,&Service->Color);
    }

    for(TargetY = MinY;TargetY <= MaxY;TargetY++){
        Pixel = Base + (HR * TargetY) + MinX;
        CopyBltPixelColor(Pixel,&Service->Color);

        Pixel = Base + (HR * TargetY) + MaxX;
        CopyBltPixelColor(Pixel,&Service->Color);
    }

}

VOID
EFIAPI
BasicPainterDrawLine(BasicPainterService * Service){
    return;
    // todo
    /*
    uint32_t HR = Service->GOP->Mode->Info->HorizontalResolution;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Base = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) Service->GOP->Mode->FrameBufferBase;
    uint32_t MinX=0,MinY=0,MaxX=0,MaxY=0;

    (Service->StartPointer.x < Service->EndPointer.x) ?
        (
            MinX = Service->StartPointer.x,
            MaxX = Service->EndPointer.x
        ):(
            MinX = Service->EndPointer.x,
            MaxX = Service->StartPointer.x
        );

    (Service->StartPointer.y < Service->EndPointer.y) ?
        (
            MinY = Service->StartPointer.y,
            MaxY = Service->EndPointer.y
        ):(
            MinY = Service->EndPointer.y,
            MaxY = Service->StartPointer.y
        );
    */

}

BasicPainterService *
EFIAPI
BasicPainterDraw(BasicPainterService * Service,enum BasicPointerDrawType DrawType){
    switch(DrawType){
        case BasicPointerDrawTypePixel: {
            BasicPainterDrawPixel(Service);
            break;
        }
        case BasicPointerDrawTypeLine: {
            BasicPainterDrawLine(Service);
            break;
        }
        case BasicPointerDrawTypeRect: {
            BasicPainterDrawRect(Service);
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

VOID
EFIAPI
SetBltPixelColorRGBR(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Base,uint8_t Red,uint8_t Blue,uint8_t Green,uint8_t Reserved){
    Base->Blue = Blue;
    Base->Green = Green;
    Base->Red = Red;
    Base->Reserved = Reserved;
}

VOID
EFIAPI
CopyBltPixelColor(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *des,EFI_GRAPHICS_OUTPUT_BLT_PIXEL *src){
    des->Blue = src->Blue;
    des->Green = src->Green;
    des->Red = src->Red;
    des->Reserved = des->Reserved;
}

uint32_t
EFIAPI
getConsoleWidth(BasicPainterService * Service){
    return Service->GOP->Mode->Info->HorizontalResolution;
}

uint32_t
EFIAPI
getConsoleHeight(BasicPainterService * Service){
    return Service->GOP->Mode->Info->VerticalResolution;
}

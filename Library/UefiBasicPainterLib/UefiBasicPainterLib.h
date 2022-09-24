#ifndef UEFI_BASIC_PAINTER_LIB_H
#define UEFI_BASIC_PAINTER_LIB_H

#include <Uefi.h>
#include <stdint.h>
#include <Library/UefiLib.h>
#include <Library/SynchronizationLib.h>

typedef struct Position2D{
    uint32_t x;
    uint32_t y;
}Position2D;

enum BasicPointerDrawType{
    BasicPointerDrawTypePixel = 0,
    BasicPointerDrawTypeLine  = 1,
    BasicPointerDrawTypeRect  = 2,
};

typedef struct BasicPainterService{
    // Data
    EFI_SYSTEM_TABLE * SystemTable;
    Position2D StartPointer;
    Position2D EndPointer;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL Color;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL DefaultColor;
    EFI_GRAPHICS_OUTPUT_PROTOCOL * GOP;
    

    // Function
    EFI_STATUS EFIAPI (*InitGraphicsOutputProtocol)(struct BasicPainterService * Service);
    struct BasicPainterService * EFIAPI (*Draw)(struct BasicPainterService * Service,enum BasicPointerDrawType);
    struct BasicPainterService * EFIAPI (*SetStartPointer)(struct BasicPainterService * Service,uint32_t x,uint32_t y);
    struct BasicPainterService * EFIAPI (*SetEndPointer)(struct BasicPainterService * Service,uint32_t x,uint32_t y);
    struct BasicPainterService * EFIAPI (*SetColor)(struct BasicPainterService * Service,uint8_t Red,uint8_t Blue,uint8_t Green,uint8_t Reserved);
    struct BasicPainterService * EFIAPI (*SetDefaultColor)(struct BasicPainterService * Service);
    struct BasicPainterService * EFIAPI (*SetDefaultColorConfig)(struct BasicPainterService * Service,uint8_t Red,uint8_t Blue,uint8_t Green,uint8_t Reserved);


}BasicPainterService;




BasicPainterService * EFIAPI CreateBasicPainterService(IN EFI_SYSTEM_TABLE * SystemTable);
BasicPainterService * EFIAPI BasicPainterSetColor(BasicPainterService * Service,uint8_t Red,uint8_t Blue,uint8_t Green,uint8_t Reserved);
BasicPainterService * EFIAPI BasicPainterDraw(BasicPainterService * Service,enum BasicPointerDrawType DrawType);
BasicPainterService * EFIAPI BasicPainterSetDefaultColor(struct BasicPainterService * Service);
BasicPainterService * EFIAPI BasicPainterSetStartPointer(struct BasicPainterService * Service,uint32_t x,uint32_t y);
BasicPainterService * EFIAPI BasicPainterSetEndPointer(struct BasicPainterService * Service,uint32_t x,uint32_t y);
BasicPainterService * EFIAPI BasicPainterSetDefaultColorConfig(struct BasicPainterService * Service,uint8_t Red,uint8_t Blue,uint8_t Green,uint8_t Reserved);
EFI_STATUS EFIAPI InitGraphicsOutputProtocol(struct BasicPainterService * Service);

#endif
#ifndef NINE_PATCH
#define NINE_PATCH
#include <stdint.h>
#include <common.h>
typedef struct {
    uint16_t width;
    uint16_t height;
    uint16_t scalable_x_begin;
    uint16_t scalable_x_end;
    uint16_t scalable_y_begin;
    uint16_t scalable_y_end;
    uint16_t content_x_begin;
    uint16_t content_x_end;
    uint16_t content_y_begin;
    uint16_t content_y_end;
    pixel    image_without_border[0];
} nine_patch_image;
int draw_nine_patch(nine_patch_image* image, uint32_t content_width, uint32_t content_height,
                    pixel* output_buffer, uint32_t buffer_width, uint32_t buffer_height);
#endif

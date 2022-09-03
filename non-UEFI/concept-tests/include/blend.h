#ifndef BLEND_H
#define BLEND_H

#include <common.h>
uint32_t alpha_blending_pixel(uint32_t a, uint32_t b);
pixel* alpha_blending_bitmap(pixel* front,uint32_t front_width, uint32_t front_height, pixel* back, uint32_t back_width, uint32_t back_height, uint32_t offset_x, uint32_t offset_y);
#endif

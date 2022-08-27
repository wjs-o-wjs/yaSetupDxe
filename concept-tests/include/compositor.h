#ifndef COMPOSITOR_H
#define COMPOSITOR_H
#include <stdint.h>
#include <wchar.h>
#include <common.h>
#define MOUSE_WIDTH  18
#define MOUSE_HEIGHT 24

#define RED_BIT_MASK 0xFF0000
#define GREEN_BIT_MASK 0xFF00
#define BLUE_BIT_MASK 0xFF
#define ALPHA_BIT_MASK 0xFF000000

#define red_bits(x) ((uint8_t)((x&RED_BIT_MASK)>>16))
#define green_bits(x) ((uint8_t)((x&GREEN_BIT_MASK)>>8))
#define blue_bits(x) ((uint8_t)((x&BLUE_BIT_MASK)))
extern double scale_factor;
void init_compositor(uint32_t width, uint32_t height);
void composite(void);
void move_mouse(int x, int y);
void fini_compositor(void);
void update_window_caption(wchar_t* caption);
#endif

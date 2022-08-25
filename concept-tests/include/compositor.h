#ifndef COMPOSITOR_H
#define COMPOSITOR_H
#include <stdint.h>
#define MOUSE_WIDTH  36
#define MOUSE_HEIGHT 48

extern double scale_factor;
void init_compositor(uint32_t width, uint32_t height);
void composite(void);
void move_mouse(int x, int y);
void fini_compositor(void);
#endif

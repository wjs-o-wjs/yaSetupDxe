#ifndef WINDOW_H
#define WINDOW_H
#include <stddef.h>
#include <stdint.h>
#include <common.h>

void create_window(uint32_t width, uint32_t height);
void destroy_window(void);
void update_window(uint32_t x,uint32_t y,uint32_t w, uint32_t h);
extern pixel* main_screen;
#endif

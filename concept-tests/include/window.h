#ifndef WINDOW_H
#define WINDOW_H
#include <stddef.h>
#include <stdint.h>
#include <common.h>
typedef struct {
    uint8_t b;
    uint8_t g;
    uint8_t r;
    uint8_t a;
} pixel;
void create_window(uint32_t width, uint32_t height);
void destroy_window();
void update_window();
extern pixel* main_screen;
#endif

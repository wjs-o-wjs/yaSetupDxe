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
typedef struct {
    uint16_t identifier;

    uint8_t  has_close_button   : 1;
    uint8_t  has_maximize_button: 1;
    uint8_t  has_minimize_button: 1;
    uint8_t                     : 5;

    uint8_t is_movable   : 1;
    uint8_t is_resizeable: 1;
    uint8_t is_visible   : 1;
    uint8_t              : 5;

    uint16_t parent_identifier;
    // callback function define
    // todo..
} __attribute__((packed)) u_window;
void create_window(uint32_t width, uint32_t height);
void destroy_window();
extern pixel* main_screen;
#endif

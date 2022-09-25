#ifndef FONT_H
#define FONT_H
#include <common.h>
#include <wchar.h>
typedef enum {
    TEXT_RENDER_AUTO_LINE_WRAP=0,
    TEXT_RENDER_NO_LINE_WRAP=1
} LineWrapPolicy;
void prepare_font(void* font_buffer, size_t font_buffer_size);
void draw_text(wchar_t* text,uint64_t text_length,uint32_t font_size,uint32_t color,\
               pixel* buffer,int buffer_width, int buffer_height, LineWrapPolicy policy);
#endif

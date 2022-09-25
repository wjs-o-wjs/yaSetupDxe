#include <font.h>
#include <freetype2/FreeTypeAmalgam.h>
#include "common.h"
#include <compositor.h>
#include <main.h>
static FT_Library library;
static FT_Face face;
void prepare_font(void* font_buffer, size_t font_buffer_size)
{
    int status = FT_Init_FreeType(&library);
    if(status!=FT_Err_Ok) {
        printf("Error in init FreeType!\n");
        fini(EXIT_FAILURE);
    }
    status = FT_New_Memory_Face(library,font_buffer,font_buffer_size,0,&face);
}
void draw_text(wchar_t* text,uint64_t text_length,uint32_t font_size,uint32_t color,\
               pixel* buffer,int buffer_width, int buffer_height,LineWrapPolicy policy)
{
    int status = FT_Set_Pixel_Sizes(face,0,font_size);
    FT_GlyphSlot  slot = face->glyph;
    int           pen_x=0, pen_y=0, n;
    for(n=0;n<text_length;n++) {
        status = FT_Load_Char(face,text[n],FT_LOAD_RENDER);
        if (status!=FT_Err_Ok) {
            continue;
        }
        //TODO:Alpha blending.
        //FIXME:No line wrap!
#if 1
        for(int i=0;i<slot->bitmap.rows;i++) {
            for(int j=0;j<slot->bitmap.width;j++) {
                buffer[(pen_y+i)*buffer_width+(pen_x+j)].value = color;
                buffer[(pen_y+i)*buffer_width+(pen_x+j)].a = slot->bitmap.buffer[(pen_y+i)*buffer_width+(pen_x+j)];
            }
        }
#endif
        pen_x += slot->advance.x >> 6;
    }
}


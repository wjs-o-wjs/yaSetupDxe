#include <compositor.h>
#include <window.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <nine-patch.h>
#include <theme.h>
pixel* mouse_area_buffer;
pixel* mouse_buffer;
uint32_t window_width, window_height, mouse_width, mouse_height, mouse_x, mouse_y;

double scale_factor;
double get_desired_scale_factor(void)
{
    //If not specified, try to scale to 1920x1080.
    double scale_factor_x = window_width/1920;
    double scale_factor_y = window_height/1080;
    if(scale_factor_x<1.0 || scale_factor_y<1.0) {
        return 1.0;
    }
    else {
        return (scale_factor_x>scale_factor_y?scale_factor_y:scale_factor_x);
    }
}
void define_mouse(double scale_factor)
{
    mouse_width  = MOUSE_WIDTH*scale_factor;
    mouse_height = MOUSE_HEIGHT*scale_factor;
    mouse_buffer = calloc(1,mouse_width*mouse_height*sizeof(pixel));
    mouse_area_buffer = calloc(1,mouse_width*mouse_height*sizeof(pixel));
    //TEST: an ugly triangle.
    for(int i=0;i<mouse_height;i++) {
        for(int j=0;j<(i*mouse_width/mouse_height);j++) {
            mouse_buffer[i*mouse_width+j].a = 0xFF;
            mouse_buffer[i*mouse_width+j].r = 0x20;
            mouse_buffer[i*mouse_width+j].g = 0xA0;
            mouse_buffer[i*mouse_width+j].b = 0xFF;
        }
    }
}
void move_mouse(int x, int y)
{
    if(x < 0) {
        x = 0;
    }
    else if(x >= window_width) {
        x = window_width - 1;
    }
    if(y < 0) {
        y = 0;
    }
    else if(y >= window_height) {
        y = window_height - 1;
    }
    //First, restore former underlying area.
    int restore_width=((mouse_width+mouse_x)>window_width?window_width-mouse_x:mouse_width);
    int restore_height=((mouse_height+mouse_y)>window_height?window_height-mouse_y:mouse_height);
    for(int i=0;i<restore_height;i++) {
        for(int j=0;j<restore_width;j++) {
            main_screen[(i+mouse_y)*window_width+(j+mouse_x)] = mouse_area_buffer[i*mouse_width+j];
        }
    }
    //Then, backup the underlying area.
    int copy_width=((mouse_width+x)>window_width?window_width-x:mouse_width);
    int copy_height=((mouse_height+y)>window_height?window_height-y:mouse_height);
    for(int i=0;i<copy_height;i++) {
        for(int j=0;j<copy_width;j++) {
            mouse_area_buffer[i*mouse_width+j] = main_screen[(i+y)*window_width+(j+x)] ;
            //FIXME:Transparency!
            if(mouse_buffer[i*mouse_width+j].a) {
                main_screen[(i+y)*window_width+(j+x)] = mouse_buffer[i*mouse_width+j];
            }
        }
    }
    //Finally, update window reigon.
    update_window(mouse_x,mouse_y,mouse_width,mouse_height);
    update_window(x,y,mouse_width,mouse_height);
    mouse_x = x;
    mouse_y = y;
}
void create_background(uint32_t width, uint32_t height)
{
    for(int i=0;i<height;i++) {
        for(int j=0;j<width;j++) {
            main_screen[i*width+j].r = red_bits(COLOUR_BACKGROUND);
            main_screen[i*width+j].g = green_bits(COLOUR_BACKGROUND);
            main_screen[i*width+j].b = blue_bits(COLOUR_BACKGROUND);
            main_screen[i*width+j].a = 0xFF;
        }
    }
}
void init_compositor(uint32_t width, uint32_t height)
{
    create_window(width, height);
    create_background(width,height);
    window_width = width;
    window_height = height;
    scale_factor=get_desired_scale_factor();
    //Do sth.....
    define_mouse(scale_factor);
    composite();
    move_mouse(width/2,height/2);
    //TEST:nine-patch.
    struct {
        nine_patch_image image;
        pixel p[7*7];
    } test_nine_patch = {
        .image.width = 7,
        .image.height = 7,
        .image.content_x_begin = 3,
        .image.content_x_end   = 4,
        .image.content_y_begin = 3,
        .image.content_y_end   = 4,
        .image.scalable_x_begin= 3,
        .image.scalable_x_end  = 4,
        .image.scalable_y_begin= 3,
        .image.scalable_y_end  = 4,
        .p = {
            {{0xf0,0xe6,0xd5,0xff}},{{0xeb,0xbd,0x65,0xff}},{{0xea,0xaf,0x40,0xff}},{{0xe9,0xae,0x3d,0xff}},
            {{0xea,0xaf,0x40,0xff}},{{0xeb,0xbc,0x64,0xff}},{{0xef,0xe5,0xd3,0xff}},{{0xeb,0xbc,0x64,0xff}},
            {{0xeb,0xbd,0x67,0xff}},{{0xef,0xda,0xb2,0xff}},{{0xee,0xdc,0xba,0xff}},{{0xed,0xd8,0xb1,0xff}},
            {{0xeb,0xbe,0x65,0xff}},{{0xeb,0xbc,0x63,0xff}},{{0xea,0xaf,0x40,0xff}},{{0xee,0xda,0xb2,0xff}},
            {{0xee,0xdc,0xba,0xff}},{{0xee,0xdc,0xba,0xff}},{{0xee,0xdc,0xba,0xff}},{{0xed,0xd8,0xb1,0xff}},
            {{0xea,0xaf,0x40,0xff}},{{0xe9,0xaf,0x3e,0xff}},{{0xee,0xdc,0xba,0xff}},{{0xee,0xdc,0xba,0xff}},
            {{0xee,0xdc,0xba,0xff}},{{0xee,0xdc,0xba,0xff}},{{0xee,0xdc,0xba,0xff}},{{0xe9,0xae,0x3d,0xff}},
            {{0xea,0xaf,0x40,0xff}},{{0xed,0xd8,0xb1,0xff}},{{0xee,0xdc,0xba,0xff}},{{0xee,0xdc,0xba,0xff}},
            {{0xee,0xdc,0xba,0xff}},{{0xee,0xda,0xb2,0xff}},{{0xea,0xaf,0x40,0xff}},{{0xeb,0xbc,0x63,0xff}},
            {{0xeb,0xbe,0x65,0xff}},{{0xee,0xd9,0xb2,0xff}},{{0xee,0xdc,0xba,0xff}},{{0xef,0xda,0xb2,0xff}},
            {{0xeb,0xbe,0x66,0xff}},{{0xeb,0xbc,0x64,0xff}},{{0xef,0xe5,0xd3,0xff}},{{0xeb,0xbc,0x64,0xff}},
            {{0xea,0xaf,0x40,0xff}},{{0xe9,0xae,0x3d,0xff}},{{0xea,0xaf,0x40,0xff}},{{0xeb,0xbd,0x65,0xff}},
            {{0xf0,0xe7,0xd6,0xff}}
        }
    };
    draw_nine_patch(&test_nine_patch.image,200,20,main_screen,window_width,window_height);
    draw_nine_patch(&test_nine_patch.image,50,300,main_screen+(200*window_width+200),window_width,window_height);
    draw_nine_patch(&test_nine_patch.image,400,400,main_screen+(300*window_width+300),window_width,window_height);
    composite();
}
void composite(void)
{
    update_window(0,0,window_width,window_height);
}
void fini_compositor(void)
{
    free(mouse_area_buffer);
    free(mouse_buffer);
    destroy_window();
}
void update_window_caption(wchar_t* caption)
{
    printf("Update Window Caption: %ls\n",caption);
}

#include <compositor.h>
#include <window.h>
#include <stdlib.h>
#include <string.h>
pixel* background_buffer;
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
    //First, restore former underlying area.
    for(int i=0;i<mouse_height;i++) {
        for(int j=0;j<mouse_width;j++) {
            main_screen[(i+mouse_y)*window_width+(j+mouse_x)] = background_buffer[(i+mouse_y)*window_width+(j+mouse_x)];
        }
    }
    //Then, composite new image in screen.
    int copy_width=((mouse_width+x)>window_width?window_width-x:mouse_width);
    int copy_height=((mouse_height+y)>window_height?window_height-y:mouse_height);
    for(int i=0;i<copy_height;i++) {
        for(int j=0;j<copy_width;j++) {
            //FIXME:Transparency!
            main_screen[(i+y)*window_width+(j+x)] = (mouse_buffer[i*mouse_width+j].a)?(mouse_buffer[i*mouse_width+j]):(background_buffer[(i+y)*window_width+(j+x)]);
        }
    }
    //Finally, update window reigon.
    update_window(mouse_x,mouse_y,mouse_width,mouse_height);
    update_window(x,y,mouse_width,mouse_height);
    mouse_x = x;
    mouse_y = y;
}
void init_compositor(uint32_t width, uint32_t height)
{
    create_window(width, height);
    background_buffer = malloc(height*width*sizeof(pixel));
    window_width = width;
    window_height = height;
    scale_factor=get_desired_scale_factor();
    //Do sth.....
    //TEST: a basic background.
    for(int i=0;i<height;i++) {
        for(int j=0;j<width;j++) {
            background_buffer[i*width+j].r = (uint8_t)(((double)j)/width*255);
            background_buffer[i*width+j].g = (uint8_t)(((double)i)/height*255);
        }
    }
    define_mouse(scale_factor);
    composite();
    move_mouse(100,100);
}
void composite(void)
{
    //Copy.
    memcpy(main_screen,background_buffer,window_width*window_height*sizeof(pixel));
    update_window(0,0,window_width,window_height);
}
void fini_compositor(void)
{
    free(background_buffer);
    free(mouse_buffer);
    destroy_window();
}

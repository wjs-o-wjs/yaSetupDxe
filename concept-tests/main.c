#include <stdio.h>
#include <window.h>
#include <event.h>
#include <stdlib.h>
int main(void)
{
    create_window(WIDTH, HEIGHT);
    //Do sth.....
    //Test.
    for(int i=0;i<HEIGHT;i++) {
        for(int j=0;j<WIDTH;j++) {
            main_screen[i*WIDTH+j].r = (uint8_t)(((double)j)/WIDTH*255);
            main_screen[i*WIDTH+j].g = (uint8_t)(((double)i)/HEIGHT*255);
        }
    }
    update_window();
    main_loop();
}
void fini(int retval)
{
    destroy_window();
    exit(retval);
}

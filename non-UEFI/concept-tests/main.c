#include <stdio.h>
#include <compositor.h>
#include <common.h>
#include <event.h>
#include <stdlib.h>
int main(void)
{
    init_compositor(WIDTH,HEIGHT);
    update_window_caption(L"BIOS Setup Utility - ECGM Demo Board");
    main_loop();
}
void fini(int retval)
{
    fini_compositor();
    exit(retval);
}

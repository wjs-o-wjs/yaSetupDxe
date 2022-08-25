#include <stdio.h>
#include <compositor.h>
#include <common.h>
#include <event.h>
#include <stdlib.h>
int main(void)
{
    init_compositor(WIDTH,HEIGHT);
    main_loop();
}
void fini(int retval)
{
    fini_compositor();
    exit(retval);
}

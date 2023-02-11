/*
  Here we override some platform functions that cannot be re-defined in macro.
  SPDX-License-Identifier: WTFPL
 */
#include "Override_include/FreeTypePlatformFunctions.h"
#include "Override_include/ftdebug.h"

FT_BASE( void )
ft_debug_init( void )
{
    // We do not need to init.
}

FT_Error FtLogEdk2(FT_Error Level, char* Format,...)
{
    return -1;
}
FT_Error FtErrEdk2   (char *Format,...)
{
    return -1;
}
FT_Error FtPanicEdk2 (char *Format,...)
{
    return -1;
}

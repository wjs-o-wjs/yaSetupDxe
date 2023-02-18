/*
  Here we override some platform functions that cannot be re-defined in macro.
  SPDX-License-Identifier: WTFPL
 */
#include "Override_include/FreeTypePlatformFunctions.h"
#include "Override_include/ftdebug.h"
#include <Library/DebugLib.h>
FT_BASE( void )
ft_debug_init( void )
{
    // We do not need to init.
}

FT_Error
EFIAPI
FtLogEdk2(FT_Error Level, char* Format,...)
{
    VA_LIST va;
    VA_START (va,Format);
    DebugVPrint(DEBUG_INFO,Format,va);
    VA_END (va);
    (VOID) Level;
    return -1;
}
FT_Error
EFIAPI
FtErrEdk2   (char *Format,...)
{
    VA_LIST va;
    VA_START (va,Format);
    DebugVPrint(DEBUG_ERROR,Format,va);
    VA_END (va);
    return -1;
}
FT_Error
EFIAPI
FtPanicEdk2 (char *Format,...)
{
    VA_LIST va;
    VA_START (va,Format);
    DebugVPrint(DEBUG_ERROR,Format,va);
    VA_END (va);
    return -1;
}

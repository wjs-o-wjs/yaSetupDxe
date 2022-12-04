#ifndef INTERNAL_HEADER
#define INTERNAL_HEADER
// Contains functions that shall be not exposed to outside.
#include <Uefi.h>

double
EFIAPI
GetScaleFactor (
  VOID
);

EFI_STATUS
EFIAPI
SetScaleFactor (
  double NewScaleFactor
);

#endif

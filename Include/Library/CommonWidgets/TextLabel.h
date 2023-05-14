/** @file
  Headers to define Text Label.
  SPDX-License-Identifier: WTFPL
**/
#ifndef TEXTLABEL_H
#define TEXTLABEL_H
#include <Library/CommonWidgetLib.h>

// Here we define the Text Label.
typedef struct _TEXT_LABEL {
  COMMON_WIDGET   Common;
  UINT32          FontSize;
  CHAR16         *Text;
  UINT32          BackgroudColor;
  UINT32          TextColor;
} TEXT_LABEL;

/**
  Do initialization on a new instance of Text Label.
  @param   Instance        The instace going to be initialized.
  @return  EFI_SUCESS      on success.
  @return  Other           if on error.
  @note The Instance points to a buffer that is allocated by caller.
**/

EFI_STATUS
EFIAPI
InitializeTextLabel
(
  IN OUT TEXT_LABEL  *Instance
);
#endif

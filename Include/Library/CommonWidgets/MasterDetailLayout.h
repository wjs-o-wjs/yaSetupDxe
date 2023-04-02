/** @file
  Headers to define Master-Detail layout.
  SPDX-License-Identifier: WTFPL
**/
#ifndef MASTER_DETAIL_H
#define MASTER_DETAIL_H

#include <Library/CommonWidgetLib.h>

// The basic Linear Layout model.
typedef struct _MASTER_DETAIL_LAYOUT {
  COMMON_LAYOUT       CommonLayout;
  COMMON_WIDGET      *MasterWidget;
  COMMON_WIDGET      *DetailWidget;
  UINT32              MasterDetailRatio;
  LAYOUT_ORIENTATION  Orientation;
} MASTER_DETAIL_LAYOUT;

/**
  Do initialization on a new instance of Text Label.
  @param   Instance        The instace going to be initialized.
  @return  EFI_SUCESS      on success.
  @return  Other           if on error.
  @note The Instance points to a buffer that is allocated by caller.
**/

EFI_STATUS
EFIAPI
InitializeMasterDetailLayout
(
  IN OUT MASTER_DETAIL_LAYOUT *Instance
);

#endif

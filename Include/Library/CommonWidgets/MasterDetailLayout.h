#ifndef MASTER_DETAIL_H
#define MASTER_DETAIL_H
#include <Library/CommonWidgetLib.h>
// The basic Linear Layout model.
typedef struct _MASTER_DETAIL_LAYOUT {
  COMMON_LAYOUT       CommonLayout;
  COMMON_WIDGET      *MasterWidget;
  COMMON_WIDGET      *DetailWidget;
  UINT32              MasterDetailDistance;
  LAYOUT_ORIENTATION  Orientation;
} MASTER_DETAIL_LAYOUT;
#endif

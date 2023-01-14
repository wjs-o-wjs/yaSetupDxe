#ifndef COMMON_WIDGET_H
#define COMMON_WIDGET_H
/** @file
  Headers to define some common widgets.
  SPDX-License-Identifier: WTFPL
**/

#include <Uefi.h>
#include <Library/MouseLib.h>

typedef enum {
  WidgetOverflowPolicyHidden,
  WidgetOverflowPolicyVisibleWithoutResize,
  WidgetOverflowPolicyResize
} WIDGET_OVERFLOW_POLICY;


/*
  Forward-define widget struct.
*/
typedef struct _COMMON_WIDGET COMMON_WIDGET;

/**
  Do initialization on a new instance of widget.
  It is defined as a macro in order to fit multiple types of widgets.
  @param   WidgetType      Type that is going to be extended.
  @param   Instance        The instace going to be initialized.
  @return  EFI_SUCESS      on success.
  @return  Other           if on error.
  @note The Instance points to a buffer that is allocated by caller.
**/
#define InitializeWidget ( WidgetType, Instance ) Initialize##WidgetType ( Instance )

/**
  The Click handler function.
  @param    Instance        The instance itself.
  @param    RelativeX       The click position relative X to the widget's position.
  @param    RelativeY       The click position relative Y to the widget's position.
  @param    ClickStatus     The click status according to the mouse lib.
  @return   EFI_SUCESS      on success.
  @return   Other           if on error.
**/
typedef
EFI_STATUS
(EFIAPI *COMMON_WIDGET_ON_CLICK)
(
  IN COMMON_WIDGET     *Instance,
  IN UINT32             RelativeX,
  IN UINT32             RelativeY,
  IN MOUSE_CLICK_STATUS Status
);

/**
  The hover handler function.
  @param    Instance        The instance itself.
  @param    RelativeX       The hover position relative X to the widget's position.
  @param    RelativeY       The hover position relative Y to the widget's position.
  @return   EFI_SUCESS      on success.
  @return   Other           if on error.
**/
typedef
EFI_STATUS
(EFIAPI *COMMON_WIDGET_ON_HOVER)
(
  IN UINT32             RelativeX,
  IN UINT32             RelativeY
);

/**
  The activate handler function.
  @param    Instance        The instance itself.
  @return   EFI_SUCESS      on success.
  @return   Other           if on error.
**/
typedef
EFI_STATUS
(EFIAPI *COMMON_WIDGET_ON_ACTIVATE)
(
  VOID
);

/**
  The activate handler function.
  @param    Instance        The instance itself.
  @return   EFI_SUCESS      on success.
  @return   Other           if on error.
**/
typedef
EFI_STATUS
(EFIAPI *COMMON_WIDGET_ON_DEACTIVATE)
(
  VOID
);

struct _COMMON_WIDGET {
  COMMON_WIDGET              *Parent;
  UINT32                      Width;
  UINT32                      Height;
  WIDGET_OVERFLOW_POLICY      OverflowPolicy;
  COMMON_WIDGET_ON_CLICK      OnClick;
  COMMON_WIDGET_ON_HOVER      OnHover;
  COMMON_WIDGET_ON_ACTIVATE   OnActivate;
  COMMON_WIDGET_ON_DEACTIVATE OnDeactivate;
};

#endif

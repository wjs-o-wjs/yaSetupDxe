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

typedef enum _LAYOUT_TYPE {
  LinearLayout,
  ConstraintLayout,
  MasterDetailLayout
} LAYOUT_TYPE;

typedef struct _CHILD_WIDGET_LINKED_NODE {
  struct _CHILD_WIDGET_LINKED_NODE *Next;
  struct _CHILD_WIDGET_LINKED_NODE *Prev;
  COMMON_WIDGET                    *Widget;
} CHILD_WIDGET_LINKED_NODE;

typedef struct {
  CHILD_WIDGET_LINKED_NODE  Head;
  CHILD_WIDGET_LINKED_NODE *Tail;
} CHILD_WIDGET_LINKED_LIST;

typedef struct _COMMON_LAYOUT {
  COMMON_WIDGET             CommonWidget;
  LAYOUT_TYPE               LayoutType;
  CHILD_WIDGET_LINKED_LIST  Children;
} COMMON_LAYOUT;

typedef enum _LAYOUT_GRAVITY {
  LayoutGravityBegin,
  LayoutGravityCenter,
  LayoutGravityEnd
} LAYOUT_GRAVITY;

typedef enum _LAYOUT_ORIENTATION {
  LayoutOrientationHorizontal,
  LayoutOrientationVertical
} LAYOUT_ORIENTATION;

typedef struct _LINEAR_LAYOUT {
  COMMON_LAYOUT       CommonLayout;
  LAYOUT_GRAVITY      GravityHorizontal;
  LAYOUT_GRAVITY      GravityVertical;
  LAYOUT_ORIENTATION  Orientation;
} LINEAR_LAYOUT;

/**
  This function creates the root layout.
  Remember, the size of root layout is ALWAYS the same size as the screen.
  @param        LayoutType      the type of root layout.
  @returns      EFI_SUCCESS     on success.
  @returns      Other           on failure.
**/
EFI_STATUS
EFIAPI
CreateRootLayout
(
  IN LAYOUT_TYPE   LayoutType
);

/**
  This function attaches widget to the layout.
  @param    Layout          The layout that is going to attach to.
  @param    Widget          The widget that is going to perform attachment.
  @returns  EFI_SUCCESS     on success.
  @returns  Other           on failure.
**/
EFI_STATUS
EFIAPI
AttachWidgetToLayout
(

);

/**
  Here we use a recursive-notify method for event notification.
  Let's assume a scenario with 3 layers of components:

        RootLayout -> LinearLayout -> TextLabel

  In this case, the system processes events (e.g., mouse hover event) like the following:

  Event From Message Queue                                          Composer -------> Composition
            \                                                          /
             \                                                        /
          RootLayout  -- In my range?                            RootLayout --In my range?
              \                                                     /
               \                                                   /
          LinearLayout -- In my range?                       LinearLayout -- In my range?
                \                                                 /
                 \                                               /
              TextLabel -- In my range?                      TextLabel -- In my range?
                  |                                              |
                  |               ------------------>            |
                  +--------------------do update-----------------+
**/

#endif

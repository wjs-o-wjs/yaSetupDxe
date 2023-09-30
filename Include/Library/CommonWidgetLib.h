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

typedef enum _LAYOUT_GRAVITY {
  LayoutGravityBegin,
  LayoutGravityCenter,
  LayoutGravityEnd
} LAYOUT_GRAVITY;

typedef enum _LAYOUT_ORIENTATION {
  LayoutOrientationHorizontal,
  LayoutOrientationVertical
} LAYOUT_ORIENTATION;

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
#define InitializeWidget( WidgetType, Instance ) Initialize##WidgetType ( Instance )

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
  IN COMMON_WIDGET     *Instance,
  IN UINT32             RelativeX,
  IN UINT32             RelativeY
);

/**
  The repaint handler function.
  @param   Instance           The instace going to be notified.
  @param   UpdateBeginX       The X value of region begin position.
  @param   UpdateBeginY       The Y value of region begin position.
  @param   UpdateWidth        The width of update region.
  @param   UpdateHeight       The height of update region.
  @note The region is considered as the metrics of the inner instance.
**/
typedef
EFI_STATUS
(EFIAPI *COMMON_WIDGET_ON_REPAINT)
(
  COMMON_WIDGET  *Instance,
  UINT32          RepaintBeginX,
  UINT32          RepaintBeginY,
  UINT32          RepaintWidth,
  UINT32          RepaintHeight
);

/**
  The size change handler function.
  @param   Instance           The instace going to be notified.
  @param   NewWidth           The new width of the widget.
  @param   NewHeight          The new height of the widget.
  @note The region is considered as the metrics of the inner instance.
**/
typedef
EFI_STATUS
(EFIAPI *COMMON_WIDGET_ON_RESIZE)
(
  COMMON_WIDGET  *Instance,
  UINT32          NewWidth,
  UINT32          NewHeight
);

/**
  Do partial area updates on a specified region of the parent widget.
  @param   Target             The target parent widget.
  @param   Instance           The instace going to be added.
  @param   UpdateBeginX       The X value of region begin position.
  @param   UpdateBeginY       The Y value of region begin position.
  @param   UpdateWidth        The width of update region.
  @param   UpdateHeight       The height of update region.
  @note The region is considered as the metrics of the inner instance.
**/
typedef
EFI_STATUS
(EFIAPI *COMMON_WIDGET_UPDATE_AREA)
(
  COMMON_WIDGET  *Target,
  COMMON_WIDGET  *Instance,
  UINT32          UpdateBeginX,
  UINT32          UpdateBeginY,
  UINT32          UpdateWidth,
  UINT32          UpdateHeight
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
  IN COMMON_WIDGET     *Instance
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
  IN COMMON_WIDGET     *Instance
);

struct _COMMON_WIDGET {
  COMMON_WIDGET              *Parent;
  UINT32                      Width;
  UINT32                      Height;
  INT32                       OffsetX;
  INT32                       OffsetY;
  WIDGET_OVERFLOW_POLICY      OverflowPolicy;
  LAYOUT_GRAVITY              VerticalGravitity;
  LAYOUT_GRAVITY              HorizontalGravitity;
  LAYOUT_ORIENTATION          Orientation;
  UINT32                     *Buffer;
  // Below are event callbacks.
  COMMON_WIDGET_ON_CLICK      OnClick;
  COMMON_WIDGET_ON_HOVER      OnHover;
  COMMON_WIDGET_ON_ACTIVATE   OnActivate;
  COMMON_WIDGET_ON_DEACTIVATE OnDeactivate;
  COMMON_WIDGET_ON_REPAINT    OnRepaint;
  COMMON_WIDGET_ON_RESIZE     OnResize;
  // Below are common functions.
  COMMON_WIDGET_UPDATE_AREA   UpdateArea;
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
  IN COMMON_LAYOUT *Layout,
  IN COMMON_WIDGET *Widget
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

/**
  This function initializes the layout.
  @returns  EFI_SUCCESS     on success.
  @returns  Other           on failure.
**/
EFI_STATUS
EFIAPI
InitLayout
(
  VOID
);

/**
  This function checks whether a child widget fits in parent.
  @param   Parent           The parent widget.
  @param   Child            The child  widget.
  @returns TRUE             if fits.
  @returns FALSE            if out of range.
**/
BOOLEAN
EFIAPI
CheckChildWidgetFitsInParent
(
  COMMON_WIDGET *Parent,
  COMMON_WIDGET *Child
);

/**
  This function converts parent's drawing area into child's .
  @param   Parent               The parent widget.
  @param   Child                The child  widget.
  @param   DrawingOffsetX       Thw parent drawing area, offset X.
  @param   DrawingOffsetY       Thw parent drawing area, offset Y.
  @param   DrawingWidth         The parent drawing width.
  @param   DrawingHeight        The parent drawing height.
  @param   ChildDrawingOffsetX  Optional output drawing offset X of child.
  @param   ChildDrawingOffsetY  Optional output drawing offset Y of child.
  @param   ChildDrawingWidth    Optional output child drawing width.
  @param   ChildDrawingHeight   Optional output child drawing height.
  @returns EFI_SUCCESS          if child's drawing area is in parent's area.
  @returns EFI_BUFFER_TOO_SMALL if out of range.
**/
EFI_STATUS
EFIAPI
CheckChildWidgetInParentDrawingArea
(
  COMMON_WIDGET *Parent,
  COMMON_WIDGET *Child,
  UINT32         DrawingOffsetX,
  UINT32         DrawingOffsetY,
  UINT32         DrawingWidth,
  UINT32         DrawingHeight,
  UINT32        *ChildDrawingOffsetX OPTIONAL,
  UINT32        *ChildDrawingOffsetY OPTIONAL,
  UINT32        *ChildDrawingWidth   OPTIONAL,
  UINT32        *ChildDrawingHeight  OPTIONAL
);
#endif

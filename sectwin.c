/*
	This file was generated by XVT-Design 4.5, a product of:

		XVT Software Inc.
		4900 Pearl East Circle
		Boulder, CO USA 80301
		303-443-4223, fax 303-443-0969

	Generated on Tue Sep 02 10:35:00 1997
*/
/* TAG BEGIN SPCL:Pre_Header */
/* TAG END SPCL:Pre_Header */

#include "xvt.h"
#include "xvtcm.h"
#include "nodInc.h"

/* 
	Information about the window
*/
#define WIN_RES_ID SECTION_WINDOW
#define WIN_FLAGS 0x810L
#define WIN_CLASS ""
#define WIN_BORDER W_DOC
/* TAG BEGIN SPCL:Obj_Decl */
/* TAG END SPCL:Obj_Decl */

/*
	Handler for window SECTION_WINDOW ("Section")
*/
long XVT_CALLCONV1
#if XVT_CC_PROTO
SECTION_WINDOW_eh XVT_CALLCONV2 (WINDOW xdWindow, EVENT *xdEvent)
#else
SECTION_WINDOW_eh XVT_CALLCONV2 (xdWindow, xdEvent)
WINDOW xdWindow;
EVENT *xdEvent;
#endif
{
	short xdControlId = xdEvent->v.ctl.id;
	/* TAG BEGIN SPCL:Var_Decl */
	/* TAG END SPCL:Var_Decl */

	switch (xdEvent->type) {
	case E_CREATE:
		/*
			Window has been created; first event sent to newly-created
			window.
		*/
		{
		/* TAG BEGIN EVNT:Create */
		setScrollRange (xdWindow, SECTION_POS_X_BAR, -10000, 10000);
		setScrollRange (xdWindow, SECTION_POS_Y_BAR, -10000, 10000);
		setScrollRange (xdWindow, SECTION_POS_Z_BAR, -10000, 10000);
		setScrollRange (xdWindow, SECTION_DECL_BAR, 0, 360);
		setScrollRange (xdWindow, SECTION_LENGTH_BAR, 0, 10000);
		setScrollRange (xdWindow, SECTION_HEIGHT_BAR, 0, 10000);
		/* TAG END EVNT:Create */
		}
		break;
	case E_DESTROY:
		/*
			Window has been closed; last event sent to window.
		*/
		xdRemoveHelpAssoc( xdWindow );
		{
		/* TAG BEGIN EVNT:Destroy */
		/* TAG END EVNT:Destroy */
		}
		break;
	case E_FOCUS:
		{
		/* TAG BEGIN EVNT:Focus */
		/*
			Window has lost or gained focus.
		*/
		if (xdEvent->v.active) {
			/*
				Window has gained focus
			*/
		} else {
			/*
				Window has lost focus
			*/
		}
		/* TAG END EVNT:Focus */
		}
		break;
	case E_SIZE:
		/*
			Size of window has been set or changed; sent when window is
			created or subsequently resized by user or via xvt_vobj_move.
		*/
		{
		/* TAG BEGIN EVNT:Size */
		/* TAG END EVNT:Size */
		}
		break;
	case E_UPDATE:
		/*
			Window requires updating.
		*/
		{
		/* TAG BEGIN EVNT:Update */
		xvt_dwin_clear(xdWindow, (COLOR)xvt_vobj_get_attr(xdWindow, ATTR_BACK_COLOR));
		/* TAG END EVNT:Update */
		}
		break;
	case E_CLOSE:
		/*
			Request to close window; user operated "close" menu item on
			window system menu, or operated "close" control on window
			frame. Not sent if Close on File menu is issued. Window not
			closed unless xvt_vobj_destroy is called.
		*/
		{
		/* TAG BEGIN EVNT:Close */
		xvt_vobj_destroy(xdWindow);
		/* TAG END EVNT:Close */
		}
		break;
	case E_CHAR:
		/*
			Character typed.
		*/
		{
		/* TAG BEGIN EVNT:Char */
		/* TAG END EVNT:Char */
		}
		break;
	case E_MOUSE_UP:
		/*
			Mouse was released
		*/
		{
		/* TAG BEGIN EVNT:Mouse_Up */
		/* TAG END EVNT:Mouse_Up */
		}
		break;
	case E_MOUSE_DOWN:
		/*
			Mouse was pressed
		*/
		{
		/* TAG BEGIN EVNT:Mouse_Down */
		/* TAG END EVNT:Mouse_Down */
		}
		break;
	case E_MOUSE_DBL:
		/*
			Mouse was double clicked
		*/
		{
		/* TAG BEGIN EVNT:Mouse_Dbl */
		/* TAG END EVNT:Mouse_Dbl */
		}
		break;
	case E_MOUSE_MOVE:
		/*
			Mouse was moved
		*/
		{
		/* TAG BEGIN EVNT:Mouse_Move */
		/* TAG END EVNT:Mouse_Move */
		}
		break;
	case E_HSCROLL:
		{
		/* TAG BEGIN EVNT:Hscroll */
		/*
			Horizontal scrollbar on frame was operated
		*/
		switch (xdEvent->v.scroll.what) {
		case SC_LINE_UP:
			break;
		case SC_LINE_DOWN:
			break;
		case SC_PAGE_UP:
			break;
		case SC_PAGE_DOWN:
			break;
		case SC_THUMB:
			break;
		case SC_THUMBTRACK:
			break;
		default:
			break;
		}
		/* TAG END EVNT:Hscroll */
		}
		break;
	case E_VSCROLL:
		{
		/* TAG BEGIN EVNT:Vscroll */
		/*
			Vertical scrollbar on frame was operated
		*/
		switch (xdEvent->v.scroll.what) {
		case SC_LINE_UP:
			break;
		case SC_LINE_DOWN:
			break;
		case SC_PAGE_UP:
			break;
		case SC_PAGE_DOWN:
			break;
		case SC_THUMB:
			break;
		case SC_THUMBTRACK:
			break;
		default:
			break;
		}
		/* TAG END EVNT:Vscroll */
		}
		break;
	case E_COMMAND:
		/*
			User issued command on window menu bar (menu bar at top of
			screen for Mac/CH).
		*/
		{
		/* TAG BEGIN EVNT:Command */
		/*
			No menubar was associated with this window
		*/
		/* TAG END EVNT:Command */
		}
		break;
	case E_CONTROL:
		/*
			User operated control in window.
		*/
		{
		/* TAG BEGIN SPCL:Control_Decl */
		/* TAG END SPCL:Control_Decl */

		switch(xdControlId) {
		case SECTION_DECL_BAR: /* "Horizontal Scrollbar Declination" */
			{
			/* TAG BEGIN SECTION_DECL_BAR EVNT:Control */
			         int pos = 0;
			         /*
			            Horizontal scrollbar control was operated
			         */
			         switch (xdEvent->v.ctl.ci.v.scroll.what) {
			         case SC_LINE_UP:
			            pos = xvt_sbar_get_pos (xdEvent->v.ctl.ci.win, HVSCROLL) - 1;
			            break;
			         case SC_LINE_DOWN:
			            pos = xvt_sbar_get_pos (xdEvent->v.ctl.ci.win, HVSCROLL) + 1;
			            break;
			         case SC_PAGE_UP:
			            pos = xvt_sbar_get_pos (xdEvent->v.ctl.ci.win, HVSCROLL) - TEN;
			            SNAP_DOWN_BY(pos, 10)
			            break;
			         case SC_PAGE_DOWN:
			            pos = xvt_sbar_get_pos (xdEvent->v.ctl.ci.win, HVSCROLL) + TEN;
			            SNAP_UP_BY(pos, 10)
			            break;
			         case SC_THUMB:
			            pos = xdEvent->v.ctl.ci.v.scroll.pos;
			            break;
			         case SC_THUMBTRACK:
			            pos = xdEvent->v.ctl.ci.v.scroll.pos;
			            break;
			         }
			         updateScrollField (xdWindow, xdControlId, pos);
			         updateNumericTextField (xdWindow, SECTION_DECL, pos);
			update3dPreview (NULL_WIN, (OBJECT *) NULL);
			/* TAG END SECTION_DECL_BAR EVNT:Control */
			}
			break;
		case SECTION_LENGTH_BAR: /* "Horizontal Scrollbar Length" */
			{
			/* TAG BEGIN SECTION_LENGTH_BAR EVNT:Control */
			         int pos = 0;
			         /*
			            Horizontal scrollbar control was operated
			         */
			         switch (xdEvent->v.ctl.ci.v.scroll.what) {
			         case SC_LINE_UP:
			            pos = xvt_sbar_get_pos (xdEvent->v.ctl.ci.win, HVSCROLL) - 1;
			            break;
			         case SC_LINE_DOWN:
			            pos = xvt_sbar_get_pos (xdEvent->v.ctl.ci.win, HVSCROLL) + 1;
			            break;
			         case SC_PAGE_UP:
			            pos = xvt_sbar_get_pos (xdEvent->v.ctl.ci.win, HVSCROLL) - THOUSAND;
			            SNAP_DOWN_BY(pos, 1000)
			            break;
			         case SC_PAGE_DOWN:
			            pos = xvt_sbar_get_pos (xdEvent->v.ctl.ci.win, HVSCROLL) + THOUSAND;
			            SNAP_UP_BY(pos, 1000)
			            break;
			         case SC_THUMB:
			            pos = xdEvent->v.ctl.ci.v.scroll.pos;
			            break;
			         case SC_THUMBTRACK:
			            pos = xdEvent->v.ctl.ci.v.scroll.pos;
			            break;
			         }
			         updateScrollField (xdWindow, xdControlId, pos);
			         updateNumericTextField (xdWindow, SECTION_LENGTH, pos);
			update3dPreview (NULL_WIN, (OBJECT *) NULL);
			/* TAG END SECTION_LENGTH_BAR EVNT:Control */
			}
			break;
		case SECTION_LENGTH: /* "5000" */
			{
			/* TAG BEGIN SECTION_LENGTH EVNT:Control */
			         /*
			            Edit control was operated.
			         */
			         if (xdEvent->v.ctl.ci.v.edit.focus_change) {
			            if (xdEvent->v.ctl.ci.v.edit.active) {
			               /*
			                  focus has entered the control
			               */
			            } else {
			               /*
			                  focus has left the control
			               */
			            }
			         } else {
			            /*
			               Contents of control were changed
			            */
			         updateScrollAndText (xdWindow, SECTION_LENGTH_BAR, SECTION_LENGTH, FALSE);
			update3dPreview (NULL_WIN, (OBJECT *) NULL);
			         }
			/* TAG END SECTION_LENGTH EVNT:Control */
			}
			break;
		case SECTION_DECL: /* "90" */
			{
			/* TAG BEGIN SECTION_DECL EVNT:Control */
			         /*
			            Edit control was operated.
			         */
			         if (xdEvent->v.ctl.ci.v.edit.focus_change) {
			            if (xdEvent->v.ctl.ci.v.edit.active) {
			               /*
			                  focus has entered the control
			               */
			            } else {
			               /*
			                  focus has left the control
			               */
			            }
			         } else {
			            /*
			               Contents of control were changed
			            */
			         updateScrollAndText (xdWindow, SECTION_DECL_BAR, SECTION_DECL, TRUE);
			update3dPreview (NULL_WIN, (OBJECT *) NULL);
			         }
			/* TAG END SECTION_DECL EVNT:Control */
			}
			break;
		case SECTION_POS_X_BAR: /* "Horizontal Scrollbar OX" */
			{
			/* TAG BEGIN SECTION_POS_X_BAR EVNT:Control */
			int pos = 0;
			/*
				Horizontal scrollbar control was operated
			*/
			switch (xdEvent->v.ctl.ci.v.scroll.what) {
			case SC_LINE_UP:
				pos = xvt_sbar_get_pos (xdEvent->v.ctl.ci.win, HVSCROLL) - 1;
				break;
			case SC_LINE_DOWN:
				pos = xvt_sbar_get_pos (xdEvent->v.ctl.ci.win, HVSCROLL) + 1;
				break;
			case SC_PAGE_UP:
				pos = xvt_sbar_get_pos (xdEvent->v.ctl.ci.win, HVSCROLL) - THOUSAND;
				SNAP_DOWN_BY(pos, 1000)
				break;
			case SC_PAGE_DOWN:
				pos = xvt_sbar_get_pos (xdEvent->v.ctl.ci.win, HVSCROLL) + THOUSAND;
				SNAP_UP_BY(pos, 1000)
				break;
			case SC_THUMB:
				pos = xdEvent->v.ctl.ci.v.scroll.pos;
				break;
			case SC_THUMBTRACK:
				pos = xdEvent->v.ctl.ci.v.scroll.pos;
				break;
			}
			updateScrollField (xdWindow, xdControlId, pos);
			updateNumericTextField (xdWindow, SECTION_POS_X, pos);
			update3dPreview (NULL_WIN, (OBJECT *) NULL);
			/* TAG END SECTION_POS_X_BAR EVNT:Control */
			}
			break;
		case SECTION_POS_Y_BAR: /* "Horizontal Scrollbar OY" */
			{
			/* TAG BEGIN SECTION_POS_Y_BAR EVNT:Control */
			int pos = 0;
			/*
				Horizontal scrollbar control was operated
			*/
			switch (xdEvent->v.ctl.ci.v.scroll.what) {
			case SC_LINE_UP:
				pos = xvt_sbar_get_pos (xdEvent->v.ctl.ci.win, HVSCROLL) - 1;
				break;
			case SC_LINE_DOWN:
				pos = xvt_sbar_get_pos (xdEvent->v.ctl.ci.win, HVSCROLL) + 1;
				break;
			case SC_PAGE_UP:
				pos = xvt_sbar_get_pos (xdEvent->v.ctl.ci.win, HVSCROLL) - THOUSAND;
				SNAP_DOWN_BY(pos, 1000)
				break;
			case SC_PAGE_DOWN:
				pos = xvt_sbar_get_pos (xdEvent->v.ctl.ci.win, HVSCROLL) + THOUSAND;
				SNAP_UP_BY(pos, 1000)
				break;
			case SC_THUMB:
				pos = xdEvent->v.ctl.ci.v.scroll.pos;
				break;
			case SC_THUMBTRACK:
				pos = xdEvent->v.ctl.ci.v.scroll.pos;
				break;
			}
			updateScrollField (xdWindow, xdControlId, pos);
			updateNumericTextField (xdWindow, SECTION_POS_Y, pos);
			update3dPreview (NULL_WIN, (OBJECT *) NULL);
			/* TAG END SECTION_POS_Y_BAR EVNT:Control */
			}
			break;
		case SECTION_POS_Z_BAR: /* "Horizontal Scrollbar OZ" */
			{
			/* TAG BEGIN SECTION_POS_Z_BAR EVNT:Control */
			int pos = 0;
			/*
				Horizontal scrollbar control was operated
			*/
			switch (xdEvent->v.ctl.ci.v.scroll.what) {
			case SC_LINE_UP:
				pos = xvt_sbar_get_pos (xdEvent->v.ctl.ci.win, HVSCROLL) - 1;
				break;
			case SC_LINE_DOWN:
				pos = xvt_sbar_get_pos (xdEvent->v.ctl.ci.win, HVSCROLL) + 1;
				break;
			case SC_PAGE_UP:
				pos = xvt_sbar_get_pos (xdEvent->v.ctl.ci.win, HVSCROLL) - THOUSAND;
				SNAP_DOWN_BY(pos, 1000)
				break;
			case SC_PAGE_DOWN:
				pos = xvt_sbar_get_pos (xdEvent->v.ctl.ci.win, HVSCROLL) + THOUSAND;
				SNAP_UP_BY(pos, 1000)
				break;
			case SC_THUMB:
				pos = xdEvent->v.ctl.ci.v.scroll.pos;
				break;
			case SC_THUMBTRACK:
				pos = xdEvent->v.ctl.ci.v.scroll.pos;
				break;
			}
			updateScrollField (xdWindow, xdControlId, pos);
			updateNumericTextField (xdWindow, SECTION_POS_Z, pos);
			update3dPreview (NULL_WIN, (OBJECT *) NULL);
			/* TAG END SECTION_POS_Z_BAR EVNT:Control */
			}
			break;
		case SECTION_POS_X: /* "x" */
			{
			/* TAG BEGIN SECTION_POS_X EVNT:Control */
			/*
				Edit control was operated.
			*/
			if (xdEvent->v.ctl.ci.v.edit.focus_change) {
				if (xdEvent->v.ctl.ci.v.edit.active) {
					/*
						focus has entered the control
					*/
				} else {
					/*
						focus has left the control
					*/
				}
			} else {
				/*
					Contents of control were changed
				*/
			updateScrollAndText (xdWindow, SECTION_POS_X_BAR, SECTION_POS_X, FALSE);
			update3dPreview (NULL_WIN, (OBJECT *) NULL);
			}
			/* TAG END SECTION_POS_X EVNT:Control */
			}
			break;
		case SECTION_POS_Z: /* "z" */
			{
			/* TAG BEGIN SECTION_POS_Z EVNT:Control */
			/*
				Edit control was operated.
			*/
			if (xdEvent->v.ctl.ci.v.edit.focus_change) {
				if (xdEvent->v.ctl.ci.v.edit.active) {
					/*
						focus has entered the control
					*/
				} else {
					/*
						focus has left the control
					*/
				}
			} else {
				/*
					Contents of control were changed
				*/
			updateScrollAndText (xdWindow, SECTION_POS_Z_BAR, SECTION_POS_Z, FALSE);
			update3dPreview (NULL_WIN, (OBJECT *) NULL);
			}
			/* TAG END SECTION_POS_Z EVNT:Control */
			}
			break;
		case SECTION_POS_Y: /* "y" */
			{
			/* TAG BEGIN SECTION_POS_Y EVNT:Control */
			/*
				Edit control was operated.
			*/
			if (xdEvent->v.ctl.ci.v.edit.focus_change) {
				if (xdEvent->v.ctl.ci.v.edit.active) {
					/*
						focus has entered the control
					*/
				} else {
					/*
						focus has left the control
					*/
				}
			} else {
				/*
					Contents of control were changed
				*/
			updateScrollAndText (xdWindow, SECTION_POS_Y_BAR, SECTION_POS_Y, FALSE);
			update3dPreview (NULL_WIN, (OBJECT *) NULL);
			}
			/* TAG END SECTION_POS_Y EVNT:Control */
			}
			break;
		case SECTION_HEIGHT_BAR: /* "Horizontal Scrollbar height" */
			{
			/* TAG BEGIN SECTION_HEIGHT_BAR EVNT:Control */
			         int pos = 0;
			         /*
			            Horizontal scrollbar control was operated
			         */
			         switch (xdEvent->v.ctl.ci.v.scroll.what) {
			         case SC_LINE_UP:
			            pos = xvt_sbar_get_pos (xdEvent->v.ctl.ci.win, HVSCROLL) - 1;
			            break;
			         case SC_LINE_DOWN:
			            pos = xvt_sbar_get_pos (xdEvent->v.ctl.ci.win, HVSCROLL) + 1;
			            break;
			         case SC_PAGE_UP:
			            pos = xvt_sbar_get_pos (xdEvent->v.ctl.ci.win, HVSCROLL) - THOUSAND;
			            SNAP_DOWN_BY(pos, 1000)
			            break;
			         case SC_PAGE_DOWN:
			            pos = xvt_sbar_get_pos (xdEvent->v.ctl.ci.win, HVSCROLL) + THOUSAND;
			            SNAP_UP_BY(pos, 1000)
			            break;
			         case SC_THUMB:
			            pos = xdEvent->v.ctl.ci.v.scroll.pos;
			            break;
			         case SC_THUMBTRACK:
			            pos = xdEvent->v.ctl.ci.v.scroll.pos;
			            break;
			         }
			         updateScrollField (xdWindow, xdControlId, pos);
			         updateNumericTextField (xdWindow, SECTION_HEIGHT, pos);
			update3dPreview (NULL_WIN, (OBJECT *) NULL);
			/* TAG END SECTION_HEIGHT_BAR EVNT:Control */
			}
			break;
		case SECTION_HEIGHT: /* "height" */
			{
			/* TAG BEGIN SECTION_HEIGHT EVNT:Control */
			         /*
			            Edit control was operated.
			         */
			         if (xdEvent->v.ctl.ci.v.edit.focus_change) {
			            if (xdEvent->v.ctl.ci.v.edit.active) {
			               /*
			                  focus has entered the control
			               */
			            } else {
			               /*
			                  focus has left the control
			               */
			            }
			         } else {
			            /*
			               Contents of control were changed
			            */
			         updateScrollAndText (xdWindow, SECTION_HEIGHT_BAR, SECTION_HEIGHT, FALSE);
			update3dPreview (NULL_WIN, (OBJECT *) NULL);
			         }
			/* TAG END SECTION_HEIGHT EVNT:Control */
			}
			break;
		default:
			break;
		}
		}
		break;
	case E_FONT:
		/*
			User issued font command on window menu bar (menu bar at top of
			screen for Mac/CH).
		*/
		{
		/* TAG BEGIN EVNT:Font */
		/* TAG END EVNT:Font */
		}
		break;
	case E_TIMER:
		/*
			Timer associated with window went off.
		*/
		{
		/* TAG BEGIN EVNT:Timer */
		/* TAG END EVNT:Timer */
		}
		break;
	case E_USER:
		/*
			Application initiated.
		*/
		{
		/* TAG BEGIN EVNT:User */
		switch (xdEvent->v.user.id) {
		case -1:
		default:
			break;
		}
		/* TAG END EVNT:User */
		}
		break;
	default:
		break;
	}
	/* TAG BEGIN SPCL:Bottom */
#ifdef XVT_R40_TXEDIT_BEHAVIOR
	xvt_tx_process_event(xdWindow, xdEvent);
#endif
	/* TAG END SPCL:Bottom */
	return 0L;
}

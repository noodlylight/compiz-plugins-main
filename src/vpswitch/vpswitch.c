/*
 * Compiz vpswitch plugin
 *
 * vpswitch.c
 *
 * Copyright (c) 2007 Dennis Kasprzyk <onestone@opencompositing.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <compiz.h>
#include "vpswitch_options.h"

#define GET_DATA \
 	CompScreen *s;\
 	CompWindow *w;\
	Window xid; \
	xid = getIntOptionNamed(option, nOption, "root", 0); \
	s = findScreenAtDisplay(d, xid); \
    if (!s) \
        return FALSE; \
    xid = getIntOptionNamed(option, nOption, "window", 0); \
    w = findWindowAtDisplay(d, xid); \
    if ((!w || (w->type & CompWindowTypeDesktopMask) == 0) && \
		xid != s->root) \
        return FALSE;



static void vpswitchGoto(CompScreen *s, int x, int y)
{
	XEvent xev;

    xev.xclient.type    = ClientMessage;
    xev.xclient.display = s->display->display;
    xev.xclient.format  = 32;

    xev.xclient.message_type = s->display->desktopViewportAtom;
    xev.xclient.window       = s->root;

    xev.xclient.data.l[0] = x * s->width;
    xev.xclient.data.l[1] = y * s->height;
    xev.xclient.data.l[2] = 0;
    xev.xclient.data.l[3] = 0;
    xev.xclient.data.l[4] = 0;

    XSendEvent (s->display->display, s->root, FALSE,
                SubstructureRedirectMask | SubstructureNotifyMask, &xev);
}

static Bool vpswitchNext(CompDisplay * d, CompAction * action,
					 CompActionState state, CompOption * option, int nOption)
{
	GET_DATA;

	if ((s->x == s->hsize - 1) && (s->y == s->vsize - 1))
		vpswitchGoto(s, 0, 0);
	else if (s->x == s->hsize - 1)
		vpswitchGoto(s, 0, s->y + 1);
	else
		vpswitchGoto(s, s->x + 1, s->y);

	return TRUE;
}

static Bool vpswitchPrev(CompDisplay * d, CompAction * action,
					 CompActionState state, CompOption * option, int nOption)
{
	GET_DATA;

	if ((s->x == 0) && (s->y == 0))
		vpswitchGoto(s, s->hsize - 1, s->vsize - 1);
	else if (s->x == 0)
		vpswitchGoto(s, s->hsize - 1, s->y - 1);
	else
		vpswitchGoto(s, s->x - 1, s->y);

	return TRUE;
}

static Bool vpswitchLeft(CompDisplay * d, CompAction * action,
					 CompActionState state, CompOption * option, int nOption)
{
	GET_DATA;

	if (s->x == 0)
		vpswitchGoto(s, s->hsize - 1, s->y);
	else
		vpswitchGoto(s, s->x - 1, s->y);
				
	return TRUE;
}

static Bool vpswitchRight(CompDisplay * d, CompAction * action,
					  CompActionState state, CompOption * option, int nOption)
{
	GET_DATA;

	if (s->x == s->hsize - 1)
		vpswitchGoto(s, 0, s->y);
	else
		vpswitchGoto(s, s->x + 1, s->y);
				
	return TRUE;
}

static Bool vpswitchUp(CompDisplay * d, CompAction * action,
				   CompActionState state, CompOption * option, int nOption)
{
	GET_DATA;

	if (s->y == 0)
		vpswitchGoto(s, s->x, s->vsize - 1);
	else
		vpswitchGoto(s, s->x, s->y - 1);
				
	return TRUE;
}

static Bool vpswitchDown(CompDisplay * d, CompAction * action,
					 CompActionState state, CompOption * option, int nOption)
{
	GET_DATA;

	if (s->y == s->vsize - 1)
		vpswitchGoto(s, s->x, 0);
	else
		vpswitchGoto(s, s->x, s->y + 1);
				
	return TRUE;
}


static Bool vpswitchInitDisplay(CompPlugin * p, CompDisplay * d)
{
	vpswitchSetLeftInitiate(d, vpswitchLeft);
	vpswitchSetRightInitiate(d, vpswitchRight);
	vpswitchSetUpInitiate(d, vpswitchUp);
	vpswitchSetDownInitiate(d, vpswitchDown);
	vpswitchSetNextInitiate(d, vpswitchNext);
	vpswitchSetPrevInitiate(d, vpswitchPrev);

	return TRUE;
}

static int vpswitchGetVersion(CompPlugin * p, int version)
{
	return ABIVERSION;
}

CompPluginVTable vpswitchVTable = {
	"vpswitch",
	vpswitchGetVersion,
	0,
	NULL,
	NULL,
	vpswitchInitDisplay,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	0,
	0,
	0,
	0
};

CompPluginVTable *getCompPluginInfo(void)
{
	return &vpswitchVTable;
}
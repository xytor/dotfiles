/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 10;       /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 5;       /* vertical padding of bar */
static const int sidepad            = 10;       /* horizontal padding of bar */
static const char *fonts[]          = { "sfmono:size=10:antialias=true",
					"FontAwesome:size=10:antialias=true:autohint=true"
					"MaterialIcons:size=10:antialias=true"
};
static const char dmenufont[]       = "monospace:size=10";

static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_gray5[]       = "#333333";
static const char col_cyan[]        = "#005577";
static const char col_black[]	    = "#000000";
static const char col_white[]	    = "#ffffff";
static const char col_red1[]	    = "#ff0000";
static const char col_blue1[]	    = "#0000ff";
static const char col_blue2[]	    = "#0066cc";
static const char col_green1[]	    = "#00ff00";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray4, col_gray1, col_gray2 },
	[SchemeSel]  = { col_white, col_gray5,  col_cyan },
};

/* tagging */
/*static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" }; */
static const  char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class          instance    title       tags mask     isfloating   monitor */
	{ "Gimp",         NULL,       NULL,       1 << 6,       1,           -1 },
	{ "Chromium",     NULL,       NULL,       1 << 2,       0,           -1 },
	{ "Spotify Free", NULL,	      NULL,       1 << 8,       1,	     -1 },
	{ "discord",      NULL,	      NULL,	  1 << 7,       0,	     -1 },
	{ "Emacs",        NULL,	      NULL,       1 << 1,       0,	     -1 },
	{ "xterm",        NULL,       NULL,       1 << 5,       1,           -1 },
	{ "mpv",          "gl",       NULL,       1 << 6,       1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* multimedia keys */
#include "X11/XF86keysym.h"

/* key definitions */
#define ALTKEY Mod1Mask
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *soundup[]  = { "amixer", "-q", "sset", "Master", "5%+", NULL };
static const char *sounddown[]  = { "amixer", "-q", "sset", "Master", "5%-", NULL };
static const char *mute[]  = { "amixer", "-q", "sset", "Master", "toggle", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ 0,                        XF86XK_Search, spawn,          {.v = dmenucmd } },
	{ MODKEY,	                XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_j,      aspectresize,   {.i = +24} },
	{ MODKEY|ShiftMask,             XK_k,      aspectresize,   {.i = -24} },
	{ MODKEY,	                XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY,                       XK_c,      spawn,          SHCMD("chromium") },
	{ MODKEY,                       XK_g,      spawn,          SHCMD("gimp") },
	{ ALTKEY,                       XK_e,      spawn,          SHCMD("emacs") },
	{ ALTKEY,                       XK_s,      spawn,          SHCMD("spotify") },
	{ ALTKEY,                       XK_d,      spawn,          SHCMD("discord") },
	{ ALTKEY,                       XK_t,      spawn,          SHCMD("urxvt -e gotop") },
	{ ALTKEY,                       XK_a,      spawn,          SHCMD("st -e alsamixer") },
	{ ALTKEY,                       XK_m,      spawn,          SHCMD("urxvt -e ranger") },
	{ 0,         			XK_Print,  spawn,	   SHCMD("scrot") },
        { MODKEY,			XK_Print,  spawn,	   SHCMD("scrot -s") },
	{ 0,             XF86XK_MonBrightnessDown, spawn,          SHCMD("light -U 10") },
	{ 0,              XF86XK_MonBrightnessUp,  spawn,          SHCMD("light -A 10") },
	{ 0,                     XF86XK_AudioMute, spawn,          {.v = mute } },
        { 0,              XF86XK_AudioRaiseVolume, spawn,          {.v = soundup } },
        { 0,              XF86XK_AudioLowerVolume, spawn,          {.v = sounddown } },
	/*{ 0,                     XF86XK_Display,   spawn,          SHCMD("xrandr --output VGA-1 --auto --left-of eDP-1")
	{ MODKEY,                XF86XK_Display,   spawn,          SHCMD("xrandr --output VGA-1 --auto --right-of eDP-1")*/

	/*{ ALTKEY|ShiftMask,          XK_BackSpace, self_restart,   {0} },*/
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


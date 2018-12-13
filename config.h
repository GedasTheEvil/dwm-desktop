/* See LICENSE file for copyright and license details. */

/* appearance */
static const char *fonts[] = {
        "monospace:size=10"
};
static const char dmenufont[]       = "monospace:size=10";
static const char normbordercolor[] = "#444444";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbordercolor[]  = "#5383d5";
static const char selbgcolor[]      = "#5383d5";
static const char selfgcolor[]      = "#eeeeee";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

#define FN_KEY                      0
#define MUTE                        0x1008ff12
#define VOLUME_DOWN                 0x1008ff11
#define VOLUME_UP                   0x1008ff13
#define KEYBOARD_FN                 0x1008ff42
#define STAR_FN                     0x1008ff41

#define KEY_CMD(mod,key,cmd) { mod, key, spawn, { .v = cmd } }
#define DEF_CMD(var,cmd) static const char * var[] = {cmd, NULL}
#define FN_CMD(key,cmd) KEY_CMD(FN_KEY,key,cmd)
#define ALT_SHIFT_CMD(key,cmd) KEY_CMD(Mod1Mask|ShiftMask,key,cmd)

/* tagging */
static const char *tags[] = {"1.web", "2", "3", "4", "5", "6", "7", "8.mail", "9.vm"};

static const Rule rules[] = {
        /* xprop(1):
         *	WM_CLASS(STRING) = instance, class
         *	WM_NAME(STRING) = title
         */
        /* class      instance    title       tags mask     isfloating   monitor */
        {"Gimp",    NULL, NULL, 0,      1, -1},
};

/* layout(s) */
static const float mfact = 0.5;
/* factor of master area size [0.05..0.95] */
static const int nmaster = 1;
/* number of clients in master area */
static const int resizehints = 1;
/* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
        /* symbol     arrange function */
        {"[]=", tile},    /* first entry is default */
        {"><>", NULL},    /* no layout function means floating behavior */
        {"[M]", monocle},
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY, TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* commands */
static char dmenumon[2] = "0";
/* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {"dmenu_run", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor,
                                 "-sb", selbgcolor, "-sf", selfgcolor, NULL};

//DEF_CMD(termCmd, "gnome-terminal");
static const char *termCmd[] = {"gnome-terminal", NULL};
DEF_CMD(lockCmd, "slock");
DEF_CMD(changeLanguageCmd, "dwm.lang");
DEF_CMD(afterStartCmd, "dwm.gedas");
DEF_CMD(muteCmd, "dwm.volume.mute");
DEF_CMD(volumeUpCmd, "dwm.volume.up");
DEF_CMD(volumeDownCmd, "dwm.volume.down");

static Key keys[] = {
        /* modifier                     key        function        argument */
        {MODKEY, XK_p, spawn, {.v = dmenucmd}},
        ALT_SHIFT_CMD(XK_Return, termCmd),
        FN_CMD(KEYBOARD_FN, changeLanguageCmd),
        KEY_CMD(ControlMask | ShiftMask, XK_l, lockCmd),
        KEY_CMD(MODKEY | ControlMask | ShiftMask , XK_s, afterStartCmd),
        FN_CMD(MUTE, muteCmd),
        FN_CMD(VOLUME_DOWN, volumeDownCmd),
        FN_CMD(VOLUME_UP, volumeUpCmd),
        {MODKEY, XK_b, togglebar, {0}},
        {MODKEY, XK_j, focusstack, {.i = +1}},
        {MODKEY, XK_k, focusstack, {.i = -1}},
        {MODKEY, XK_i, incnmaster, {.i = +1}},
        {MODKEY, XK_d, incnmaster, {.i = -1}},
        {MODKEY, XK_h, setmfact, {.f = -0.05}},
        {MODKEY, XK_l, setmfact, {.f = +0.05}},
        {MODKEY, XK_Return, zoom, {0}},
        {MODKEY, XK_Tab, view, {0}},
        {MODKEY | ShiftMask, XK_c, killclient, {0}},
        {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
        {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
        {MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
        {MODKEY, XK_space, setlayout, {0}},
        {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
        {MODKEY, XK_0, view, {.ui = ~0}},
        {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
        {MODKEY, XK_comma, focusmon, {.i = -1}},
        {MODKEY, XK_period, focusmon, {.i = +1}},
        {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
        {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
        TAGKEYS(XK_1, 0)
        TAGKEYS(XK_2, 1)
        TAGKEYS(XK_3, 2)
        TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4)
        TAGKEYS(XK_6, 5)
        TAGKEYS(XK_7, 6)
        TAGKEYS(XK_8, 7)
        TAGKEYS(XK_9, 8)
        {MODKEY | ShiftMask, XK_q, quit, {0}},
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
        /* click                event mask      button          function        argument */
        {ClkLtSymbol,   0,     Button1, setlayout,      {0}},
        {ClkLtSymbol,   0,     Button3, setlayout,      {.v = &layouts[2]}},
        {ClkWinTitle,   0,     Button2, zoom,           {0}},
        {ClkStatusText, 0,     Button2, spawn,          {.v = termCmd}},
        {ClkClientWin, MODKEY, Button1, movemouse,      {0}},
        {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
        {ClkClientWin, MODKEY, Button3, resizemouse,    {0}},
        {ClkTagBar,     0,     Button1, view,           {0}},
        {ClkTagBar,     0,     Button3, toggleview,     {0}},
        {ClkTagBar,    MODKEY, Button1, tag,            {0}},
        {ClkTagBar,    MODKEY, Button3, toggletag,      {0}},
};


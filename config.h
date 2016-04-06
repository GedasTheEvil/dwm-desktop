/* See LICENSE file for copyright and license details. */
/*config*/
void cview(const Arg *arg);

/* appearance */
static const char font[] = "-*-terminus-medium-r-*-*-12-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#00ccff";
static const char normbgcolor[] = "#12306c";
static const char normfgcolor[] = "#a0fff5";
static const char selbordercolor[] = "#ffffff";
static const char selbgcolor[] = "#12306c";
static const char selfgcolor[] = "#ffffff";
static const unsigned int borderpx = 1;
/* border pixel of windows */
static const unsigned int snap = 32;
/* snap pixel */
static const Bool showbar = True;
/* False means no bar */
static const Bool topbar = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

static const Rule rules[] = {
        /* class      instance    title       tags mask     isfloating   monitor */
        {"evince",  NULL, NULL, 0,      True,  -1},
        {"Firefox", NULL, NULL, 1 << 8, False, -1},
};

/* layout(s) */
static const float mfact = 0.55;
/* factor of master area size [0.05..0.95] */
static const Bool resizehints = True;
/* True means respect size hints in tiled resizals */

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

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */

static const char *menucmd[] = {"dwm-menu", NULL}; // command for menu
static const char *termcmd[] = {"dwm-term", NULL}; // command for term
static const char *browsercmd[] = {"dwm-browser", NULL}; // command for browser
static const char *lockcmd[] = {"dwm-lock", NULL}; // command for lock
static const char *changeLanguage[] = {"dwm-switch-language", NULL};
static const char *afterStart[] = {"dwm-after-start", NULL};

static Key keys[] = {
        /* modifier                     key        function        argument */
        {MODKEY, XK_m, spawn, {.v = menucmd}},
        {MODKEY, XK_Caps_Lock, spawn, {.v = changeLanguage}},
        {MODKEY | ShiftMask, XK_t, spawn, {.v = termcmd}},
        {MODKEY | ShiftMask, XK_l, spawn, {.v = lockcmd}},
        {MODKEY | ShiftMask, XK_b, spawn, {.v = browsercmd}},
        {MODKEY, XK_s, spawn, {.v = afterStart}},
        {MODKEY, XK_Up, focusstack, {.i = +1}},
        {MODKEY, XK_Down, focusstack, {.i = -1}},
        {MODKEY | ShiftMask, XK_Left, setmfact, {.f = -0.05}},
        {MODKEY | ShiftMask, XK_Right, setmfact, {.f = +0.05}},
        {MODKEY | ShiftMask, XK_BackSpace, killclient, {0}},
        {MODKEY, XK_0, view, {.ui = ~0}},
        {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
        {MODKEY, XK_Left, cview, {.i =  -1}},
        {MODKEY, XK_Right, cview, {.i =  +1}},
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
        {ClkStatusText, 0,     Button2, spawn,          {.v = termcmd}},
        {ClkClientWin, MODKEY, Button1, movemouse,      {0}},
        {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
        {ClkClientWin, MODKEY, Button3, resizemouse,    {0}},
        {ClkTagBar,     0,     Button1, view,           {0}},
        {ClkTagBar,     0,     Button3, toggleview,     {0}},
        {ClkTagBar,    MODKEY, Button1, tag,            {0}},
        {ClkTagBar,    MODKEY, Button3, toggletag,      {0}},
};

// a small function to get the current desktop
int get_desk() {
    for (int i = 0; i < 9; i++) {
        if ((selmon->tagset[selmon->seltags]) == ((1 << i) & TAGMASK))
            return i;
    }
    return 0;
}

// a small function to change the desktop for the next or the previous one
void cview(const Arg *arg) {
    int desk = get_desk();

    if ((desk == 0) && (arg->i == -1))
        desk = 9;
    if ((desk == 8) && (arg->i == 1))
        desk = -1;
    desk += arg->i;

    if (((1 << desk) & TAGMASK) == selmon->tagset[selmon->seltags])
        return;

    selmon->seltags ^= 1; /* toggle sel tagset */
    if (arg->ui & TAGMASK)
        selmon->tagset[selmon->seltags] = (1 << desk) & TAGMASK;
    arrange(selmon);
    return;
}


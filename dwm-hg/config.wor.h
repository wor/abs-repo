/* See LICENSE file for copyright and license details. */

#define XKEYS 1
#define DEFAULT_COLORS 0

#if XKEYS
#include <X11/XF86keysym.h> /* makes XF86* keys work */
#endif

/* small fonts for alternative shell */
static const char altfn[]           = "-windows-dina-medium-r-normal--13-80-96-96-c-70-iso8859-1";
static const char altfb[]           = "-windows-dina-bold-r-normal--13-80-96-96-c-70-iso8859-1";
static const char altfi[]           = "-windows-dina-medium-i-normal--13-80-96-96-c-70-iso8859-1";
static const char altfbi[]          = "-windows-dina-bold-i-normal--13-80-96-96-c-70-iso8859-1";

/* appearance */
static const char font[]            = "-*-terminus-medium-r-*-*-12-*-*-*-*-*-iso10646-*";
#if DEFAULT_COLORS
static const char normbordercolor[] = "#cccccc";
static const char normbgcolor[]     = "#cccccc";
static const char normfgcolor[]     = "#000000";
static const char selbordercolor[]  = "#0066ff";
static const char selbgcolor[]      = "#0066ff";
static const char selfgcolor[]      = "#ffffff";
#elif OLD_DEFAULT_COLORS
static const char normbordercolor[] = "#333333"; // border color unselected
static const char normbgcolor[]     = "#222222"; // bg of status bar
static const char normfgcolor[]     = "#cccccc";
static const char selbordercolor[]  = "#59aaaa"; // border color selected
static const char selbgcolor[]      = "#555555";
static const char selfgcolor[]      = "#ffffff"; // sel is selection part of the status bar
#else
// zenburn colors got from vim with gcolor2 color picker
static const char normbordercolor[] = "#333333";
//static const char normbgcolor[]     = "#afaf87";
static const char normbgcolor[]     = "#303030";
static const char normfgcolor[]     = "#afaf87";
static const char selbordercolor[]  = "#87D7D7";
static const char selbgcolor[]      = "#3a3a3a";
static const char selfgcolor[]      = "#afaf87";
#endif
static const unsigned int borderpx        = 1;        /* border pixel of windows */
static const unsigned int snap            = 32;       /* snap pixel */
static const Bool showbar                 = True;     /* False means no bar */
static const Bool topbar                  = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "www", "4", "5", "6", "7", "8", "9", "0", "Q", "W", "E", "A" };

static const Rule rules[] = {
    /* class                instance    title       tags mask   isfloating   monitor */
    { "Opera",              NULL,       NULL,       1 << 2,     True,        -1 },
    { "Chromium",           NULL,       NULL,       1 << 2,     True,        -1 },
    { "Firefox",            NULL,       NULL,       1 << 2,     True,        -1 },
    { "jd-Main",            NULL,       NULL,       1 << 2,     True,        -1 },
    { "Wine",               "spotify",  NULL,       1 << 1,     False,       -1 },
    { "Wine",               "explorer.exe",NULL,    1 << 1,     False,       -1 },
    { "Pcsx2",              NULL,       NULL,       0,          True,        -1 },
    { "Gimp",               NULL,       NULL,       0,          True,        -1 },
    { "Vlc",                NULL,       NULL,       0,          True,        -1 },
    { "MPlayer",            NULL,       NULL,       0,          True,        -1 },
    { "qemu-system-x86_64", NULL,       NULL,       0,          True,        -1 },
    { "Wine",               NULL,       NULL,       0,          True,        -1 },
    { "fontforge",          NULL,       NULL,       0,          True,        -1 },
    { "Arcoread",           NULL,       NULL,       0,          True,        -1 },
    { "Spring",             NULL,       NULL,       0,          True,        -1 },
    { "Springlobby",        NULL,       NULL,       0,          True,        -1 },
    { NULL,                 "sun-awt-X11-XFramePeer",NULL,0,    True,        -1 },
    { "com-mathworks-util-PostVMInit",NULL,NULL,    0,          True,        -1 },
    { "broken",             "broken",   NULL,       0,          True,        -1 }, /* Float broken clients */
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "><>",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define MONSLEEP "sleep 1 && exec xlock -mode blank -dpmssuspend 10 -endCmd 'xset dpms 0 900 0'"

/* commands */
static const char *dmenucmd[]   = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *urxvtcmd[]   = { "urxvtc", NULL };
static const char *urxvtcmd2[]  = { "urxvtc", NULL };
static const char *urxvtcmd3[]  = { "urxvtc", "-fn", altfn, "-fb", altfb, "-fi", altfi, "-fbi", altfbi, NULL };
static const char *uxtermcmd[]  = { "uxterm", NULL };
static const char *screenshot[] = { "import", "-window", "root", "~/Desktop/screenshot.png", NULL };
static const char *allmail[]    = { "/home/wor/bin/get_mail", NULL };
static const char *workmail[]   = { "getmail", "-n", "--rcfile", "getmailrc_itut", "--rcfile", "getmailrc_ltut", NULL };
static const char *screensaver[] = { "xlock", "-mode",  "xjack", NULL };
static const char *mixertoggle[]  = { "avolt", "-t", NULL };
static const char *mixermasslower[]  = { "avolt", "-s", "-1", NULL };
static const char *mixermasllower[] = { "avolt", "-s", "-5", NULL };
static const char *mixermasshigher[]  = { "avolt", "-s", "+1", NULL };
static const char *mixermaslhigher[] = { "avolt", "-s", "+5", NULL };
static const char *musinfo[] = { "cmdp", "info", NULL };
static const char *mustoggle[] = { "cmdp", "toggle", NULL };
static const char *musstop[]   = { "cmdp", "stop", NULL };
static const char *musprev[]   = { "cmdp", "prev", NULL };
static const char *musnext[]   = { "cmdp", "next", NULL };
static const char *musseekfs[]   = { "cmdp", "seek", "10", NULL };
static const char *musseekbs[]   = { "cmdp", "seek", "-10", NULL };
static const char *musseekfl[]   = { "cmdp", "seek", "30", NULL };
static const char *musseekbl[]   = { "cmdp", "seek", "-30", NULL };

static Key keys[] = {
    /* modifier             key             function        argument */ \
    { MODKEY,               XK_p,           spawn,          {.v = dmenucmd } },
    { MODKEY|ShiftMask|ControlMask,XK_Return,spawn,         {.v = urxvtcmd } },
    { MODKEY|ShiftMask,     XK_Return,      spawn,          {.v = urxvtcmd2 } },
    { MODKEY|ShiftMask,     XK_s,           spawn,          {.v = urxvtcmd3 } }, 
    { MODKEY|ControlMask,   XK_Return,      spawn,          {.v = uxtermcmd } },

    { MODKEY,               XK_b,           togglebar,      {0} },
    { MODKEY,               XK_j,           focusstack,     {.i = +1 } },
    { MODKEY,               XK_k,           focusstack,     {.i = -1 } },
    { MODKEY,               XK_i,           incnmaster,     {.i = +1 } },
    { MODKEY,               XK_d,           incnmaster,     {.i = -1 } },
    { MODKEY,               XK_h,           setmfact,       {.f = -0.05} },
    { MODKEY,               XK_l,           setmfact,       {.f = +0.05} },

    { MODKEY,               XK_Return,      zoom,           {0} },
    { MODKEY,               XK_Tab,         view,           {0} },
    { MODKEY|ShiftMask,     XK_c,           killclient,     {0} },
    { MODKEY,               XK_t,           setlayout,      {.v = &layouts[0]} },
    { MODKEY,               XK_f,           setlayout,      {.v = &layouts[1]} },
    { MODKEY,               XK_m,           setlayout,      {.v = &layouts[2]} },
    { MODKEY,               XK_space,       setlayout,      {0} },
    { MODKEY|ShiftMask,     XK_space,       togglefloating, {0} },
    { MODKEY,               XK_plus,        view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,     XK_plus,        tag,            {.ui = ~0 } },
    { MODKEY,               XK_comma,       focusmon,       {.i = -1 } },
    { MODKEY,               XK_period,      focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,     XK_comma,       tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,     XK_period,      tagmon,         {.i = +1 } },
    TAGKEYS(                XK_1,                           0)
    TAGKEYS(                XK_2,                           1)
    TAGKEYS(                XK_3,                           2)
    TAGKEYS(                XK_4,                           3)
    TAGKEYS(                XK_5,                           4)
    TAGKEYS(                XK_6,                           5)
    TAGKEYS(                XK_7,                           6)
    TAGKEYS(                XK_8,                           7)
    TAGKEYS(                XK_9,                           8)
    TAGKEYS(                XK_0,                           9)
    TAGKEYS(                XK_q,                           10)
    TAGKEYS(                XK_w,                           11)
    TAGKEYS(                XK_e,                           12)
    TAGKEYS(                XK_a,                           13)
    { 0,                    XK_Print,       spawn,          {.v = screenshot } },
    { MODKEY,               XK_Home,        spawn,          {.v = workmail } },
    { 0,                    XK_Pause,       spawn,          SHCMD(MONSLEEP) },
    { MODKEY,               XK_Pause,       spawn,          {.v = screensaver } },
    { MODKEY|ShiftMask,     XK_z,           quit,           {0} },
    /* music seeking using arrow keys */
    { MODKEY,               XK_Right,       spawn,          {.v = musseekfs } },
    { MODKEY,               XK_Up,          spawn,          {.v = musseekfl } },
    { MODKEY,               XK_Left,        spawn,          {.v = musseekbs } },
    { MODKEY,               XK_Down,        spawn,          {.v = musseekbl } },
#if XKEYS
    { 0,                    XF86XK_Mail,            spawn,  {.v = allmail } },
    { MODKEY,               XF86XK_Mail,            spawn,  {.v = workmail } },
    { 0,                    XF86XK_AudioMute,       spawn,  {.v = mixertoggle } },
    { 0,                    XF86XK_AudioLowerVolume,spawn,  {.v = mixermasslower } },
    { MODKEY,               XF86XK_AudioLowerVolume,spawn,  {.v = mixermasllower } },
    { 0,                    XF86XK_AudioRaiseVolume,spawn,  {.v = mixermasshigher } },
    { MODKEY,               XF86XK_AudioRaiseVolume,spawn,  {.v = mixermaslhigher } },
    { 0,                    XF86XK_AudioPlay,       spawn,  {.v = mustoggle } }, // broken on my logitech wave keyboard
    { 0,                    XF86XK_Tools,           spawn,  {.v = musinfo } },
    { 0,                    XF86XK_AudioStop,       spawn,  {.v = musstop } },
    { 0,                    XF86XK_AudioPrev,       spawn,  {.v = musprev } },
    { 0,                    XF86XK_AudioNext,       spawn,  {.v = musnext } },
    { 0,                    XF86XK_Sleep,           spawn,  SHCMD(MONSLEEP) },
    { MODKEY,               XF86XK_Sleep,           spawn,  {.v = screensaver } },
    { 0,                    XF86XK_Standby,         spawn,  SHCMD(MONSLEEP) },
#endif
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = uxtermcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


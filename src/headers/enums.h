#pragma once
#include "Header.h"

enum SCENES {
    SC_INVALID,
    SC_MAIN_MENU,
    SC_GAME_MODES,
    SC_SAVE_LOAD,
    SC_GAME,
    SC_GAME_OVER,
    SC_LEADERBOARD,
    SC_ACHIEVEMENTS,
    SC_STATS
};

NLOHMANN_JSON_SERIALIZE_ENUM(SCENES, {
{SC_INVALID     ,nullptr},
{SC_MAIN_MENU   ,"SC_MAIN_MENU"},
{SC_GAME_MODES  ,"SC_GAME_MODES"},
{SC_SAVE_LOAD   ,"SC_SAVE_LOAD"},
{SC_GAME        ,"SC_GAME"},
{SC_GAME_OVER   ,"SC_GAME_OVER"},
{SC_LEADERBOARD ,"SC_LEADERBOARD"},
{SC_ACHIEVEMENTS,"SC_ACHIEVEMENTS"},
{SC_STATS       ,"SC_STATS"}
})



enum SPRITES {
    SP_INVALID,
    SP_GEMS,
    SP_UI_1,
    SP_UI_2,
    SP_BG_PATTERNS,
};
NLOHMANN_JSON_SERIALIZE_ENUM(SPRITES, {
{SP_INVALID      ,nullptr},
{SP_GEMS         ,"gems"},
{SP_UI_1         ,"ui_1"},
{SP_UI_2         ,"ui_2"},
{SP_BG_PATTERNS  ,"bg_patterns"},
})

enum UI_ELEMENTS {
    UI_INVALID,
    UI_BUTTON,
    UI_ICON_BUTTON,
    UI_TEXT_BUTTON_4,
    UI_TEXT_BUTTON_5,
    UI_TEXT_BUTTON_6,
    UI_TEXT_BUTTON_7,
    UI_TEXT_BUTTON_8,

    UI_GEM_SLOT,
    UI_GEM,
};
NLOHMANN_JSON_SERIALIZE_ENUM(UI_ELEMENTS, {
{UI_INVALID          ,nullptr},
{UI_BUTTON           ,"Button"},
{UI_ICON_BUTTON      ,"IconButton"},
{UI_TEXT_BUTTON_4    ,"TextButton4"},
{UI_TEXT_BUTTON_5    ,"TextButton5"},
{UI_TEXT_BUTTON_6    ,"TextButton6"},
{UI_TEXT_BUTTON_7    ,"TextButton7"},
{UI_TEXT_BUTTON_8    ,"TextButton8"},
{UI_GEM_SLOT         ,"GemSlot"},
{UI_GEM              ,"Gem"},
})

enum UI_ANIMATIONS {
    AN_INVALID,
    AN_IDLE,
    AN_HOVER,
    AN_PRESS,
};
NLOHMANN_JSON_SERIALIZE_ENUM(UI_ANIMATIONS, {
{AN_INVALID ,nullptr},
{AN_IDLE    ,"idle"},
{AN_HOVER   ,"hover"},
{AN_PRESS   ,"press"},
})

enum UI_EXPANSION {
    EX_INVALID,
    EX_HORIZONTAL,
    EX_VERTICAL,
};
NLOHMANN_JSON_SERIALIZE_ENUM(UI_EXPANSION, {
{EX_INVALID     ,nullptr},
{EX_HORIZONTAL   ,"horizontal"},
{EX_VERTICAL     ,"vertical"},
})

enum VARIANTS {

/*******************************
 * Categories
 *******************************/

    V_INVALID,
    V_COLOR,
    V_SHAPE,
    V_ICON,
    V_TEXT,
    V_STATE,

/*******************************
 * Values
 *******************************/

    // COLORS
    C_INVALID,
    C_GRAY,     C_BLUE,
    C_GREEN,    C_CYAN,
    C_ORANGE,   C_PINK,
    C_PURPLE,   C_RED,
    C_WHITE,    C_YELLOW,

    // SHAPES
    SH_INVALID,
    SH_DIAMOND,      SH_RHOMBUS,
    SH_HEARTH,       SH_OVAL,
    SH_ROUND,        SH_SQUARE,
    SH_KITE,         SH_LONG_HEX,
    SH_TRIANGLE,     SH_HEX,

    // STATES
    ST_INVALID,
    ST_OPEN, ST_CLOSED,

    // ICONS
    IC_INVALID,         IC_ZERO,            IC_RIGHT,
    IC_LEFT,            IC_DOWN,            IC_UP,
    IC_QUESTION,        IC_LEADERBOARD,     IC_MONEY,
    IC_STATS,           IC_SETTINGS,        IC_ONE,
    IC_TWO,             IC_THREE,           IC_ACHIEVEMENT,
    IC_SHOP,            IC_FOUR,            IC_FIVE,
    IC_SIX,             IC_VOLUME_ON,       IC_VOLUME_OFF,
    IC_SEVEN,           IC_EIGHT,           IC_NINE,
    IC_EXCHANGE,        IC_DELETE,          IC_STAR,
    IC_LIGHTNING,       IC_HEART,           IC_PAUSE,
    IC_EXCLAMATION,     IC_IMAGE,           IC_VIDEO,
    IC_CROSS,           IC_CHECK,           IC_HOME,
    IC_MUSIC_OFF,       IC_UNKNOWN_1,       IC_UNKNOWN_2,
    IC_RELOAD,          IC_CAMERA,          IC_RESUME,
    IC_MAIL,            IC_RESTART,         IC_GIFT,
    IC_MUSIC_ON,        IC_SPEED_UP,        IC_PLUS,
    IC_MINUS,           IC_LOCK,            IC_UNDO,

    // TEXTS
    TXT_RATE,        TXT_SHOP,       TXT_YES,
    TXT_START,       TXT_SAVE,       TXT_NO,
    TXT_MENU,        TXT_LOAD,       TXT_BUY,
    TXT_PLAY,        TXT_BACK,       TXT_GET,
    TXT_SELL,        TXT_BONUS,      TXT_CLOSE,
    TXT_NEXT,        TXT_NEW,        TXT_QUIT,
    TXT_MORE,        TXT_MUTE,       TXT_CREDITS,
    TXT_RESTART,     TXT_OPTION,     TXT_CANCEL,
    TXT_MAINMENU,    TXT_GAMEOVER,   TXT_CONTINUE,
    TXT_COLLECTION,  TXT_INVENTORY,  TXT_EQUIPMENT,
    TXT_COMPLETED,   TXT_ACHIEVEMENT,TXT_LEADERBOARD
};

using V_CATEGORIES  = VARIANTS;
using V_COLORS      = VARIANTS;
using V_SHAPES      = VARIANTS;
using V_ICONS       = VARIANTS;
using V_TEXTS       = VARIANTS;
using V_STATES      = VARIANTS;


NLOHMANN_JSON_SERIALIZE_ENUM(VARIANTS, {
/*******************************
 * Categories
 *******************************/

{V_INVALID  ,nullptr},
{V_COLOR    ,"Color"},
{V_SHAPE    ,"Shape"},
{V_ICON     ,"Icon"},
{V_TEXT     ,"Text"},
{V_STATE    ,"State"},

/*******************************
 * Values
*******************************/
// COLORS
{C_INVALID ,nullptr},
{C_GRAY    ,"gray"},      {C_BLUE    ,"blue"},
{C_GREEN   ,"green"},     {C_CYAN    ,"cyan"},
{C_ORANGE  ,"orange"},    {C_PINK    ,"pink"},
{C_PURPLE  ,"purple"},    {C_RED     ,"red"},
{C_WHITE   ,"white"},     {C_YELLOW  ,"yellow"},

// SHAPES
{SH_INVALID ,nullptr},
{SH_DIAMOND ,"diamond"},      {SH_RHOMBUS ,"rhombus"},
{SH_HEARTH  ,"hearth"},       {SH_OVAL    ,"oval"},
{SH_ROUND   ,"round"},        {SH_SQUARE  ,"square"},
{SH_KITE    ,"kite"},         {SH_LONG_HEX,"long_hex"},
{SH_TRIANGLE,"triangle"},     {SH_HEX     ,"hex"},

// STATES
{ST_INVALID ,nullptr},
{ST_OPEN    ,"open"},
{ST_CLOSED  ,"closed"},

// ICONS
{IC_INVALID     ,nullptr},      {IC_ZERO        ,"zero"},
{IC_RIGHT       ,"right"},      {IC_LEFT        ,"left"},
{IC_DOWN        ,"down"},       {IC_UP          ,"up"},
{IC_QUESTION    ,"question"},   {IC_LEADERBOARD ,"leaderboard"},
{IC_MONEY       ,"money"},      {IC_STATS       ,"stats"},
{IC_SETTINGS    ,"settings"},   {IC_ONE         ,"one"},
{IC_TWO         ,"two"},        {IC_THREE       ,"three"},
{IC_ACHIEVEMENT ,"achievement"},{IC_SHOP        ,"shop"},
{IC_FOUR        ,"four"},       {IC_FIVE        ,"five"},
{IC_SIX         ,"six"},        {IC_VOLUME_ON   ,"volume_on"},
{IC_VOLUME_OFF  ,"volume_off"}, {IC_SEVEN       ,"seven"},
{IC_EIGHT       ,"eight"},      {IC_NINE        ,"nine"},
{IC_EXCHANGE    ,"exchange"},   {IC_DELETE      ,"delete"},
{IC_STAR        ,"star"},       {IC_LIGHTNING   ,"lightning"},
{IC_HEART       ,"heart"},      {IC_PAUSE       ,"pause"},
{IC_EXCLAMATION ,"exclamation"},{IC_IMAGE       ,"image"},
{IC_VIDEO       ,"video"},      {IC_CROSS       ,"cross"},
{IC_CHECK       ,"check"},      {IC_HOME        ,"home"},
{IC_MUSIC_OFF   ,"music_off"},  {IC_UNKNOWN_1   ,"unknown_1"},
{IC_UNKNOWN_2   ,"unknown_2"},  {IC_RELOAD      ,"reload"},
{IC_CAMERA      ,"camera"},     {IC_RESUME      ,"resume"},
{IC_MAIL        ,"mail"},       {IC_RESTART     ,"restart"},
{IC_GIFT        ,"gift"},       {IC_MUSIC_ON    ,"music_on"},
{IC_SPEED_UP    ,"speed_up"},   {IC_PLUS        ,"plus"},
{IC_MINUS       ,"minus"},      {IC_LOCK        ,"lock"},
{IC_UNDO        ,"undo"},

// TEXTS
{TXT_RATE       ,"rate"},       {TXT_SHOP       ,"shop"},
{TXT_YES        ,"yes"},        {TXT_START      ,"start"},
{TXT_SAVE       ,"save"},       {TXT_NO         ,"no"},
{TXT_MENU       ,"menu"},       {TXT_LOAD       ,"load"},
{TXT_BUY        ,"buy"},        {TXT_PLAY       ,"play"},
{TXT_BACK       ,"back"},       {TXT_GET        ,"get"},
{TXT_SELL       ,"sell"},       {TXT_BONUS      ,"bonus"},
{TXT_CLOSE      ,"close"},      {TXT_NEXT       ,"next"},
{TXT_NEW        ,"new"},        {TXT_QUIT       ,"quit"},
{TXT_MORE       ,"more"},       {TXT_MUTE       ,"mute"},
{TXT_CREDITS    ,"credits"},    {TXT_RESTART    ,"restart"},
{TXT_OPTION     ,"option"},     {TXT_CANCEL     ,"cancel"},
{TXT_MAINMENU   ,"mainmenu"},   {TXT_GAMEOVER   ,"gameover"},
{TXT_CONTINUE   ,"continue"},   {TXT_COLLECTION ,"collection"},
{TXT_INVENTORY  ,"inventory"},  {TXT_EQUIPMENT  ,"equipment"},
{TXT_COMPLETED  ,"completed"},  {TXT_ACHIEVEMENT,"achievement"},
{TXT_LEADERBOARD,"leaderboard"}
});

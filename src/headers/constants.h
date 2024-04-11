#pragma once

#define SCREEN_WIDTH    1200
#define SCREEN_HEIGHT   750
#define FRAME_RATE      60
#define TILE_SIZE       16
#define UI_SCALE        1

// Paths
static const Path ROOT_PATH     = FileSys::current_path().parent_path();
static const Path ASSETS_PATH   = ROOT_PATH   / "assets";
static const Path SPRITES_PATH  = ASSETS_PATH / "sprites";
static const Path AUDIO_PATH    = ASSETS_PATH / "audio";

static const Path SPRITESHEETS_DATA  = SPRITES_PATH / "spritesheets.json";
static const Path SPRITES_DATA       = SPRITES_PATH / "sprites.json";


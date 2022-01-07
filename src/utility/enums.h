#ifndef UTILITY_ENUMS_H
#define UTILITY_ENUMS_H

#include <QString>

// GridScale
enum class GridScale
{
    TINY,
    SMALL,
    MEDIUM,
    LARGE,
    HUGE,
    GARGANTUAN,

    SIZE_0_625,
    SIZE_0_750,
    SIZE_0_875,
    SIZE_1_250,
    SIZE_1_500,
    SIZE_1_750,
    SIZE_2_500,
    SIZE_3_500,

    SCALE_MAX
};

float scale(GridScale scale);
int as_int(GridScale scale);
QString as_string(GridScale scale);


// MessageType
enum class MessageType
{
    ERROR, // 0, so it will be this on failure to parse.

    // system messages
    HANDSHAKE,
    DATA_CONNECTED,
    SYNCHRONIZE,
    SYNCHRONIZE_LINES,
    SYNCHRONIZE_ENTITIES,
    SYNCHRONIZE_GRID_GROUP,
    SYNCHRONIZE_MAP,
    PLAYER_CONNECTED,
    PLAYER_DISCONNECTED,
    PING,
    PONG,

    // file transfer
    PIXMAP_REQUEST,
    PIXMAP_TRANSFER,
    PIXMAP_NOT_FOUND,

    // simple messages
    CHAT,
    RICH_TEXT,
    DISPLAY_UPDATE,

    // entity control
    PLAYER_MOVED,
    PLAYER_ENTITY_ADDED,
    ENTITY_ADDED,
    ENTITIES_MOVED,
    ENTITIES_REMOVED,
    ENTITIES_CLEARED,
    ENTITIES_ROTATED,

    // mapping stuff
    GRID_ITEM_ADDED,
    GRID_ITEM_REMOVED,
    GRID_GROUP_REMOVED,
    GRID_GROUP_VISIBILITY,
    GRID_GROUPS_CLEARED,

    // drawing
    LINE_DRAWN,
    LINES_DELETED,
    LINES_CLEARED
};

int as_int(MessageType type);
QString as_string(MessageType type);


// Mouse Modes
enum class MouseMode
{
    FREE_DRAW,
    LINE_DRAW,
    MOVE_CHARACTER,
    MOVE_GRID,
    PING,
    GRID_ITEM_PLACEMENT,
    GRID_ITEM_SELECTION,
};

QString as_string(MouseMode mode);


// VisibilityMode
enum class VisibilityMode
{
    VISIBLE,
    HIDDEN,
    PARENT
};

int as_int(VisibilityMode mode);
QString as_string(VisibilityMode mode);

#endif
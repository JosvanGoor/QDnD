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
    GARGANTUAN
};

float scale(GridScale scale);
int as_int(GridScale scale);
QString as_string(GridScale scale);


// MessageType
enum class MessageType
{
    // system messages
    WELCOME,
    HANDSHAKE,
    DISCONNECTED,
    PING,
    PONG,

    // file transfer
    PIXMAP_REQUEST,
    PIXMAP_TRANSFER,
    PIXMAP_NOT_FOUND,

    // simple messages
    CHAT_MESSAGE,
    DIEROLL_MESSSAGE,
    DISPLAY_UPDATE,
};

int as_int(MessageType type);
QString as_string(MessageType type);


// Mouse Modes
enum class MouseMode
{
    SELECT,
    DRAW
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
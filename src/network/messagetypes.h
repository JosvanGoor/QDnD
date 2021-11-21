#ifndef NETWORK_MESSAGETYPES_H
#define NETWORK_MESSAGETYPES_H

#include <QColor>
#include <QString>

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
    DISPLAY_UPDATE,
};

int as_int(MessageType type);
QString as_string(MessageType type);

#endif
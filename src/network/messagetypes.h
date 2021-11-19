#ifndef NETWORK_MESSAGETYPES_H
#define NETWORK_MESSAGETYPES_H

#include <QColor>
#include <QString>

enum class MessageType
{
    // system messages
    WELCOME,
    HANDSHAKE,
    PING,
    PONG,

    CHAT_MESSAGE,
};

int as_int(MessageType type);
QString as_string(MessageType type);

#endif
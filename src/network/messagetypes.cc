#include "messagetypes.h"

int as_int(MessageType type)
{
    return static_cast<int>(type);
}


QString as_string(MessageType type)
{
    switch (type)
    {
        case MessageType::WELCOME:          return "WELCOME";
        case MessageType::HANDSHAKE:        return "HANDSHAKE";
        case MessageType::PING:             return "PING";
        case MessageType::PONG:             return "PONG";
        case MessageType::CHAT_MESSAGE:     return "CHAT_MESSAGE";
    }

    return "If you read this Jos fucked up.";
}
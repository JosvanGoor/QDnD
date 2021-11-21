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

        case MessageType::PIXMAP_REQUEST:   return "PIXMAP_REQUEST";
        case MessageType::PIXMAP_TRANSFER:  return "PIXMAP_TRANSFER";
        case MessageType::PIXMAP_NOT_FOUND: return "PIXMAP_NOT_FOUND";

        case MessageType::CHAT_MESSAGE:     return "CHAT_MESSAGE";
        case MessageType::DIEROLL_MESSSAGE: return "DIEROLL_MESSSAGE";
        case MessageType::DISPLAY_UPDATE:   return "DISPLAY_UPDATE";
    }

    return "If you read this Jos fucked up.";
}
#include "enums.h"

////////////////////
//   GridScale    //
////////////////////

float scale(GridScale scale)
{
    switch (scale)
    {
        case GridScale::TINY: return 0.25f;
        case GridScale::SMALL: return 1.0f;
        case GridScale::MEDIUM: return 1.0f;
        case GridScale::LARGE: return 2.0f;
        case GridScale::HUGE: return 3.0f;
        case GridScale::GARGANTUAN: return 4.0f;
    }

    // TODO: add warning
    return 1.0f;
}


int as_int(GridScale scale)
{
    return static_cast<int>(scale);
}


QString as_string(GridScale scale)
{
    switch (scale)
    {
        case GridScale::TINY: return "TINY";
        case GridScale::SMALL: return "SMALL";
        case GridScale::MEDIUM: return "MEDIUM";
        case GridScale::LARGE: return "LARGE";
        case GridScale::HUGE: return "HUGE";
        case GridScale::GARGANTUAN: return "GARGANTUAN";
    }
    
    return "GridScale: If you read this Jos fucked up.";
}


////////////////////
//  MessageType   //
////////////////////

int as_int(MessageType type)
{
    return static_cast<int>(type);
}


QString as_string(MessageType type)
{
    switch (type)
    {
        case MessageType::ERROR:                return "ERROR";
        case MessageType::SYNCHRONIZE:          return "SYNCHRONIZE";
        case MessageType::HANDSHAKE:            return "HANDSHAKE";
        case MessageType::PLAYER_CONNECTED:     return "PLAYER_CONNECTED";
        case MessageType::PLAYER_DISCONNECTED:  return "PLAYER_DISCONNECTED";
        case MessageType::PING:                 return "PING";
        case MessageType::PONG:                 return "PONG";

        case MessageType::PIXMAP_REQUEST:       return "PIXMAP_REQUEST";
        case MessageType::PIXMAP_TRANSFER:      return "PIXMAP_TRANSFER";
        case MessageType::PIXMAP_NOT_FOUND:     return "PIXMAP_NOT_FOUND";

        case MessageType::CHAT:                 return "CHAT";
        case MessageType::RICH_TEXT:            return "RICH_TEXT";
        case MessageType::DISPLAY_UPDATE:       return "DISPLAY_UPDATE";
    }

    return "MessageType: If you read this Jos fucked up.";
}


////////////////////
//   MouseMode    //
////////////////////

QString as_string(MouseMode mode)
{
    switch (mode)
    {
        case MouseMode::SELECT:     return "SELECT";
        case MouseMode::DRAW:       return "DRAW";
    }
    
    return "MouseMode: If you read this Jos fucked up.";
}


////////////////////
//   Visibility   //
////////////////////

int as_int(VisibilityMode mode)
{
    return static_cast<int>(mode);
}


QString as_string(VisibilityMode mode)
{
    switch (mode)
    {
        case VisibilityMode::VISIBLE: return "VISIBLE";
        case VisibilityMode::HIDDEN: return "HIDDEN";
        case VisibilityMode::PARENT: return "PARENT";
    }

    return "VisibilityMode: If you read this Jos fucked up.";
}
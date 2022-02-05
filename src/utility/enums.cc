#include "enums.h"

////////////////////
//   GridScale    //
////////////////////

float scale(GridScale scale)
{
    switch (scale)
    {
        case GridScale::TINY: return 0.25f;
        case GridScale::SMALL: return 0.5f;
        case GridScale::MEDIUM: return 1.0f;
        case GridScale::LARGE: return 2.0f;
        case GridScale::HUGE: return 3.0f;
        case GridScale::GARGANTUAN: return 4.0f;

        case GridScale::SIZE_0_625: return 0.625f;
        case GridScale::SIZE_0_750: return 0.750f;
        case GridScale::SIZE_0_875: return 0.875f;
        case GridScale::SIZE_1_250: return 1.250f;
        case GridScale::SIZE_1_500: return 1.500f;
        case GridScale::SIZE_1_750: return 1.750f;
        case GridScale::SIZE_2_500: return 2.500f;
        case GridScale::SIZE_3_500: return 3.500f;
        case GridScale::SIZE_5:     return 5.0f;
        case GridScale::SIZE_10:    return 10.0f;

        case GridScale::SCALE_MAX: return 30.0f; // ROC size yeah
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
        case GridScale::TINY: return "Tiny (0.250)";
        case GridScale::SMALL: return "Small (0.500)";
        case GridScale::MEDIUM: return "Medium (1.000)";
        case GridScale::LARGE: return "Large (2.000)";
        case GridScale::HUGE: return "Huge (3.000)";
        case GridScale::GARGANTUAN: return "Gargantuan (4.000)";
        case GridScale::SIZE_0_625: return "0.625";
        case GridScale::SIZE_0_750: return "0.750";
        case GridScale::SIZE_0_875: return "0.875";
        case GridScale::SIZE_1_250: return "1.250";
        case GridScale::SIZE_1_500: return "1.500";
        case GridScale::SIZE_1_750: return "1.750";
        case GridScale::SIZE_2_500: return "2.500";
        case GridScale::SIZE_3_500: return "3.500";
        case GridScale::SIZE_5:     return "5.000";
        case GridScale::SIZE_10:    return "10.000";
        case GridScale::SCALE_MAX: return "30.00";
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
        case MessageType::ERROR:                    return "ERROR";
        case MessageType::SYNCHRONIZE:              return "SYNCHRONIZE";
        case MessageType::SYNCHRONIZE_LINES:        return "SYNCHRONIZE_LINES";
        case MessageType::SYNCHRONIZE_ENTITIES:     return "SYNCHRONIZE_ENTITIES";
        case MessageType::SYNCHRONIZE_GRID_GROUP:   return "SYNCHRONIZE_GRID_GROUP";
        case MessageType::SYNCHRONIZE_MAP:          return "SYNCHRONIZE_MAP";
        case MessageType::HANDSHAKE:                return "HANDSHAKE";
        case MessageType::PLAYER_CONNECTED:         return "PLAYER_CONNECTED";
        case MessageType::PLAYER_DISCONNECTED:      return "PLAYER_DISCONNECTED";
        case MessageType::PING:                     return "PING";
        case MessageType::PONG:                     return "PONG";

        case MessageType::PIXMAP_REQUEST:           return "PIXMAP_REQUEST";
        case MessageType::PIXMAP_TRANSFER:          return "PIXMAP_TRANSFER";
        case MessageType::PIXMAP_NOT_FOUND:         return "PIXMAP_NOT_FOUND";

        case MessageType::CHAT:                     return "CHAT";
        case MessageType::RICH_TEXT:                return "RICH_TEXT";
        case MessageType::DISPLAY_UPDATE:           return "DISPLAY_UPDATE";

        case MessageType::PLAYER_MOVED:             return "PLAYER_MOVED";
        case MessageType::PLAYER_ENTITY_ADDED:      return "PLAYER_ENTITY_ADDED";
        case MessageType::ENTITY_ADDED:             return "ENTITY_ADDED";
        case MessageType::ENTITIES_MOVED:           return "ENTITIES_MOVED";
        case MessageType::ENTITIES_REMOVED:         return "ENTITIES_REMOVED";
        case MessageType::ENTITIES_CLEARED:         return "ENTITIES_CLEARED";
        case MessageType::ENTITIES_ROTATED:         return "ENTITIES_ROTATED";

        case MessageType::GRID_ITEM_ADDED:          return "GRID_ITEM_ADDED";
        case MessageType::GRID_ITEM_REMOVED:        return "GRID_ITEM_REMOVED";
        case MessageType::GRID_GROUP_REMOVED:       return "GRID_GROUP_REMOVED";
        case MessageType::GRID_GROUP_VISIBILITY:    return "GRID_GROUP_VISIBILITY";
        case MessageType::GRID_GROUPS_CLEARED:      return "GRID_GROUPS_CLEARED";

        case MessageType::LINE_DRAWN:               return "LINE_DRAWN";
        case MessageType::LINES_DELETED:            return "LINES_DELETED";
        case MessageType::LINES_CLEARED:            return "LINES_CLEARED";
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
        case MouseMode::FREE_DRAW:              return "FREE_DRAW";
        case MouseMode::LINE_DRAW:              return "LINE_DRAW";
        case MouseMode::MOVE_CHARACTER:         return "MOVE_CHARACTER";
        case MouseMode::MOVE_GRID:              return "MOVE_GRID";
        case MouseMode::PING:                   return "PING";
        case MouseMode::GRID_ITEM_PLACEMENT:    return "GRID_ITEM_PLACEMENT";
        case MouseMode::GRID_ITEM_SELECTION:    return "GRID_ITEM_SELECTION";
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
        case VisibilityMode::VISIBLE:   return "VISIBLE";
        case VisibilityMode::HIDDEN:    return "HIDDEN";
        case VisibilityMode::PARENT:    return "PARENT";
    }

    return "VisibilityMode: If you read this Jos fucked up.";
}

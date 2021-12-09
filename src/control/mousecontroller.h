#ifndef CONTROL_MOUSECONTROLLER_H
#define CONTROL_MOUSECONTROLLER_H

#include <QMouseEvent>
#include <QObject>
#include <QPoint>
#include <QSize>
#include <QWheelEvent>

#include "../utility/enums.h"

/*
    Mouse control separated from the grid.
*/

class MouseController : public QObject
{
    Q_OBJECT
    
    // dimensions
    QSize d_grid_size;
    QPoint d_grid_offset;

    // position
    QPoint d_old_position;

    // modes
    bool d_entity_mode; // <-- overrules the actual mouse mode
    MouseMode d_mouse_mode;
    bool d_left_mouse_button;
    bool d_right_mouse_button;

    public:
        explicit MouseController(QObject *parent = nullptr);
        ~MouseController();

        // utility
        void reset_offset();
        void grid_resized(int width, int height);
        QPoint world_position(QPoint const &point);
        QPoint snap_to_grid(QPoint const &point, bool round = true);

        // getters
        QSize const &grid_size();
        QPoint const &grid_offset();

        // events
        void mouse_press_event(QMouseEvent *event);
        void mouse_release_event(QMouseEvent *event);
        void mouse_move_event(QMouseEvent *event);
        void mouse_wheel_event(QWheelEvent *event);

    signals:
        void debug_message(QString const &message);
        void ortho_changed(int x, int y, int width, int height);
};

#endif
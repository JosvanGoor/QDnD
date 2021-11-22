#ifndef GRID_GRIDMOUSESTATE_H
#define GRID_GRIDMOUSESTATE_H

#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QRect>

enum class AlignMode
{
    NO_ALIGN,
    CENTER_ALIGN,
    HORIZONTAL_ALIGN,
    VERTICAL_ALIGN
};


enum class GridScale
{
    NONE        = 0,
    TINY        = 16,
    SMALL       = 32,
    MEDIUM      = 64,
    LARGE       = 128,
    HUGE        = 192,
    GARGANTUAN  = 256
};
int as_int(GridScale scale);


class GridMouseState
{
    int d_delta_x;
    int d_delta_y;
    int d_screenpos_x;
    int d_screenpos_y;
    int d_screen_offset_x;
    int d_screen_offset_y;

    QPixmap d_pixmap;
    AlignMode d_pixmap_align;
    GridScale d_pixmap_scale;

    public:
        GridMouseState();
        ~GridMouseState();

        // getters
        int delta_x() const noexcept;
        int delta_y() const noexcept;
        int screenpos_x() const noexcept;
        int screenpos_y() const noexcept;
        int gridpos_x() const noexcept;
        int gridpos_y() const noexcept;
        QRect grid_placement() const noexcept;
        QRect screen_placement() const noexcept;

        // updates
        void update_pixmap(QPixmap const &pixmap);
        void update_align_mode(AlignMode mode);
        void update_grid_scale(GridScale scale);
        void update_screen_offset(int offset_x, int offset_y);
        void update_mouse_position(QMouseEvent *event);

        // paint
        void paint_pixmap(QPainter &painter);
};

#endif
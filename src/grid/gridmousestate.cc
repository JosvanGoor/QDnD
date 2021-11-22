#include "gridmousestate.h"

////////////////////
//   GridScale    //
////////////////////

int as_int(GridScale scale)
{
    return static_cast<int>(scale);
}


////////////////////
//  Constructor   //
////////////////////

GridMouseState::GridMouseState()
:   d_delta_x(0),
    d_delta_y(0),
    d_screenpos_x(0),
    d_screenpos_y(0),
    d_screen_offset_x(0),
    d_screen_offset_y(0),
    d_pixmap(),
    d_pixmap_align(AlignMode::NO_ALIGN),
    d_pixmap_scale(GridScale::MEDIUM)
{ }


GridMouseState::~GridMouseState()
{

}


////////////////////
//    Getters     //
////////////////////

int GridMouseState::delta_x() const noexcept
{
    return d_delta_x;
}


int GridMouseState::delta_y() const noexcept
{
    return d_delta_y;
}


int GridMouseState::screenpos_x() const noexcept
{
    return d_screenpos_x;
}


int GridMouseState::screenpos_y() const noexcept
{
    return d_screenpos_y;
}


int GridMouseState::gridpos_x() const noexcept
{
    return d_screen_offset_x + d_screenpos_x;
}


int GridMouseState::gridpos_y() const noexcept
{
    return d_screen_offset_y + d_screenpos_y;
}


QRect GridMouseState::grid_placement() const noexcept
{
    int xpos = 0;
    int ypos = 0;
    int width = as_int(d_pixmap_scale);
    int height = as_int(d_pixmap_scale);

    switch (d_pixmap_align)
    {
        case AlignMode::NO_ALIGN: 
            xpos = (d_screen_offset_x + d_screenpos_x) - (width / 2);
            ypos = (d_screen_offset_y + d_screenpos_y) - (height / 2);
        break;

        case AlignMode::CENTER_ALIGN:
            xpos = ((d_screen_offset_x + d_screenpos_x) / 64) * 64;
            ypos = ((d_screen_offset_y + d_screenpos_y) / 64) * 64;
        break;

        case AlignMode::HORIZONTAL_ALIGN:
            xpos = ((((d_screen_offset_x + d_screenpos_x) - 32) / 64) * 64) + (width / 2);
            ypos = (((d_screen_offset_y + d_screenpos_y)) / 64) * 64;
        break;

        case AlignMode::VERTICAL_ALIGN:
            xpos = (((d_screen_offset_x + d_screenpos_x)) / 64) * 64;
            ypos = ((((d_screen_offset_y + d_screenpos_y) - 32) / 64) * 64) + (height / 2);
        break;
    }

    return {xpos, ypos, width, height};
}


QRect GridMouseState::screen_placement() const noexcept
{
    int xpos = 0;
    int ypos = 0;
    int width = as_int(d_pixmap_scale);
    int height = as_int(d_pixmap_scale);

    switch (d_pixmap_align)
    {
        case AlignMode::NO_ALIGN: 
            xpos = d_screenpos_x - (width / 2);
            ypos = d_screenpos_y - (height / 2);
        break;

        case AlignMode::CENTER_ALIGN:
            xpos = (d_screenpos_x / 64) * 64;
            ypos = (d_screenpos_y / 64) * 64;
        break;

        case AlignMode::HORIZONTAL_ALIGN:
            xpos = (((d_screenpos_x - 32) / 64) * 64) + (width / 2);
            ypos = ((d_screenpos_y) / 64) * 64;
        break;

        case AlignMode::VERTICAL_ALIGN:
            xpos = ((d_screenpos_x) / 64) * 64;
            ypos = (((d_screenpos_y - 32) / 64) * 64) + (height / 2);
        break;
    }

    return {xpos, ypos, width, height};
}


////////////////////
//    Updates     //
////////////////////

void GridMouseState::update_pixmap(QPixmap const &pixmap)
{
    d_pixmap = pixmap;
}


void GridMouseState::update_align_mode(AlignMode mode)
{
    d_pixmap_align = mode;
}


void GridMouseState::update_grid_scale(GridScale scale)
{
    d_pixmap_scale = scale;
}


void GridMouseState::update_screen_offset(int offset_x, int offset_y)
{
    d_screen_offset_x = offset_x;
    d_screen_offset_y = offset_y;
}


void GridMouseState::update_mouse_position(QMouseEvent *event)
{
    d_delta_x = d_screenpos_x - event->x();
    d_delta_y = d_screenpos_y - event->y();
    d_screenpos_x = event->x();
    d_screenpos_y = event->y();
}


////////////////////
//     Paint      //
////////////////////

void GridMouseState::paint_pixmap(QPainter &painter)
{
    if (d_pixmap.isNull())
        return;

    painter.drawPixmap(screen_placement(), d_pixmap);
}
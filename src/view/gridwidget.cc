#include "gridwidget.h"

////////////////////
//  Constructors  //
////////////////////

GridWidget::GridWidget(QWidget *parent)
:   QOpenGLWidget(parent)
{
    d_draw_color = Qt::black;
    setMouseTracking(true);

    d_line_vao = line_array_vao();
}


GridWidget::~GridWidget()
{ }

////////////////////
//    virtuals    //
////////////////////

void GridWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    update();
}


void GridWidget::resizeGL(int width, int height)
{
    Q_UNUSED(width);
    Q_UNUSED(height);
}


void GridWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}


////////////////////
//      Modes     //
////////////////////

void GridWidget::entity_mode(bool enabled)
{
    // TODO
}


void GridWidget::set_mouse_mode(MouseMode mode)
{
    // TODO
}


////////////////////
//     Utility    //
////////////////////

void GridWidget::reset_offset()
{
    d_mouse.reset_offset();
}


void GridWidget::set_draw_color(QColor color)
{
    d_draw_color = color;
}


MouseController &GridWidget::mouse_controller()
{
    return d_mouse;
}


////////////////////
//     Events     //
////////////////////

void GridWidget::mousePressEvent(QMouseEvent *event)
{
    d_mouse.mouse_press_event(event);
}


void GridWidget::mouseReleaseEvent(QMouseEvent *event)
{
    d_mouse.mouse_release_event(event);
}


void GridWidget::mouseMoveEvent(QMouseEvent *event)
{
    d_mouse.mouse_move_event(event);
}


void GridWidget::wheelEvent(QWheelEvent *event)
{
    d_mouse.mouse_wheel_event(event);
}


////////////////////
//   Rendering    //
////////////////////

void GridWidget::render_grid()
{

}


////////////////////
//    Private     //
////////////////////

GLuint GridWidget::load_programs()
{

}


GLuint GridWidget::line_array_vao()
{
    
}

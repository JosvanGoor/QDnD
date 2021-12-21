#include "gridwidget.h"

#include <iostream>

////////////////////
//  Constructors  //
////////////////////

GridWidget::GridWidget(QWidget *parent)
:   QOpenGLWidget(parent)
{
    d_grid_mesh = nullptr;
    d_draw_color = Qt::black;
    setMouseTracking(true);

    QObject::connect(&d_mouse, &MouseController::ortho_changed, this, &GridWidget::on_ortho_update);
}


GridWidget::~GridWidget()
{
    if (d_grid_mesh)
        delete d_grid_mesh;
}

////////////////////
//    virtuals    //
////////////////////

void GridWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    render_grid();
    emit render_player_lines();

    update();
}


void GridWidget::resizeGL(int width, int height)
{
    d_mouse.grid_resized({width, height});
}


void GridWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    
    d_grid_mesh = new StaticMesh<2, 3, 0>(this);

    load_programs();
}


////////////////////
//      Modes     //
////////////////////

void GridWidget::entity_mode(bool enabled)
{
    d_mouse.set_entity_mode(enabled);
}


void GridWidget::set_mouse_mode(MouseMode mode)
{
    d_mouse.set_mouse_mode(mode);
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
    d_line_program.bind();
    glUniformMatrix4fv(0, 1, GL_FALSE, d_ortho_projection.data());

    glLineWidth(1);
    d_grid_mesh->render(GL_LINES);
}


void GridWidget::on_ortho_update(int left, int right, int bottom, int top)
{
    generate_grid_mesh();
    d_ortho_projection.setToIdentity();
    d_ortho_projection.ortho(left, right, bottom, top, -1, 1);
}


////////////////////
//    Private     //
////////////////////

void GridWidget::load_programs()
{
    d_line_program.addShaderFromSourceCode(QOpenGLShader::Vertex, s_line_vertex_shader);
    d_line_program.addShaderFromSourceCode(QOpenGLShader::Fragment, s_line_fragment_shader);
    d_line_program.link();
}


void GridWidget::generate_grid_mesh()
{
    QVector<float> mesh;

    QSize grid_size = d_mouse.grid_size();
    QPoint grid_offset = d_mouse.grid_offset();

    int x_start = (grid_offset.x() / 64) * 64 - 64;
    int y_start = (grid_offset.y() / 64) * 64 - 64;
    int x_end = (grid_size.width() + grid_offset.x()) + 64;
    int y_end = (grid_size.height() + grid_offset.y()) + 64;

    for (int xpos = x_start; xpos <= x_end; xpos += 64)
    {
        mesh +=
        {
            float(xpos), float(y_start),    0.0f, 0.0f, 0.0f,
            float(xpos), float(y_end),      0.0f, 0.0f, 0.0f
        };
    }

    for (int ypos = y_start; ypos < y_end; ypos += 64)
    {
        mesh +=
        {
            float(x_start), float(ypos),    0.0f, 0.0f, 0.0f,
            float(x_end), float(ypos),      0.0f, 0.0f, 0.0f
        };
    }

    d_grid_mesh->update(mesh);
}


////////////////////
//    Statics     //
////////////////////

char const *GridWidget::s_line_vertex_shader =
R"_shader_(
    #version 440 core

    layout (location = 0) in vec2 vertex;
    layout (location = 1) in vec3 color;
    layout (location = 0) uniform mat4 mvp;

    out vec3 vs_color;

    void main()
    {
        vs_color = color;
        gl_Position = mvp * vec4(vertex, 0.0, 1.0);
    }
)_shader_";


char const *GridWidget::s_line_fragment_shader =
R"_shader_(
    #version 440 core

    in vec3 vs_color;
    layout (location = 0) out vec4 frag_color;

    void main()
    {
        frag_color = vec4(vs_color, 1.0);
    }
)_shader_";
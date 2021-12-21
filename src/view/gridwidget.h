#ifndef VIEW_GRIDWIDGET_H
#define VIEW_GRIDWIDGET_H

#include <QColor>
#include <QMatrix4x4>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QPoint>
#include <QResizeEvent>

#include "../control/mousecontroller.h"
#include "../model/player.h"
#include "../opengl/staticmesh.h"
#include "../utility/enums.h"

class GridWidget : public QOpenGLWidget, public QOpenGLFunctions_4_5_Core
{
    Q_OBJECT

    QColor d_draw_color;
    MouseController d_mouse;
    
    // shaders
    QOpenGLShaderProgram d_line_program;

    // default meshes
    StaticMesh<2, 3, 0> *d_grid_mesh;

    // ortho mvp
    QMatrix4x4 d_ortho_projection;

    // shaders
    static const char *s_line_vertex_shader;
    static const char *s_line_fragment_shader;

    public:
        explicit GridWidget(QWidget *parent = nullptr);
        ~GridWidget();

        // virtuals
        virtual void paintGL() override;
        virtual void resizeGL(int width, int height) override;
        virtual void initializeGL() override;

        // mode stuff
        void entity_mode(bool enabled);
        void set_mouse_mode(MouseMode mode);

        // utility
        void reset_offset();
        void set_draw_color(QColor color);
        MouseController &mouse_controller();
        StaticMesh<2, 3, 0> *get_line_mesh();

        // passthrough events
        void mousePressEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void wheelEvent(QWheelEvent *event) override;

        // rendering stuff
        void render_grid();
        void on_ortho_update(int left, int right, int bottom, int top);

    signals:
        void debug_message(QString const &message);
        void render_player_lines();

    private: // opengl stuffs
        void load_programs();

        void generate_grid_mesh();
        
};

#endif
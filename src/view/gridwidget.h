#ifndef VIEW_GRIDWIDGET_H
#define VIEW_GRIDWIDGET_H

#include <QColor>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLWidget>
#include <QPoint>

#include "../control/mousecontroller.h"
#include "../model/player.h"
#include "../utility/enums.h"

class GridWidget : public QOpenGLWidget, public QOpenGLFunctions_4_5_Core
{
    Q_OBJECT

    QColor d_draw_color;
    MouseController d_mouse;

    // vao's
    GLuint  d_line_vao;
    
    // buffers
    GLuint d_grid_buffer;

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

        // passthrough mouse events
        void mousePressEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void wheelEvent(QWheelEvent *event) override;

        // rendering stuff
        void render_grid();

    signals:
        void debug_message(QString const &message);

    private: // opengl stuffs
        GLuint load_programs();

        GLuint line_array_vao();
        void line_array_buffer(GLuint buffer, QMap<QString, DrawLine> const &lines);
        void grid_array_buffer(GLuint buffer);
        
};

#endif
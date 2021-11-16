#ifndef GRIDCONTROLWIDGET_H
#define GRIDCONTROLWIDGET_H

#include <QGroupBox>
#include <QListWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QWidget>

struct AvatarControl
{
    QPixmap avatar;
    QPoint position;
};

class GridControlWidget : public QWidget
{
    Q_OBJECT

    int d_selection;
    QString d_selection_name;

    QGroupBox *d_mode_group;
        QRadioButton *d_draw;
        QRadioButton *d_select;

    QGroupBox *d_reset_group;
        QPushButton *d_reset_position;
        QPushButton *d_clear_lines;
        QPushButton *d_clear_grid;

    QGroupBox *d_lines_group;
        QListWidget *d_lines_list;
        QPushButton *d_delete;
        QPushButton *d_unselect;

    public:
        explicit GridControlWidget(QWidget *parent = nullptr);
        ~GridControlWidget();

        void add_line(QString const &line);

        void on_delete_line();
        void on_selection_changed(int selection);
        void on_unselect();

        bool is_drawing();
        bool is_selected(QString const &name);
        void remove_entry_by_name(QString const &name);

    signals:
        void reset_position();
        void clear_lines();
        void clear_grid();

        void delete_line(QString const &name);
};

#endif
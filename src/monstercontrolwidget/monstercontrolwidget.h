#ifndef MONSTERCONTROLWIDGET_H
#define MONSTERCONTROLWIDGET_H

#include <QByteArray>
#include <QFile>
#include <QFileDialog>
#include <QFormLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

struct MonsterInfo
{
    QString name;
    QByteArray raw_pixmap;
};

class MonsterControlWidget : public QWidget
{
    Q_OBJECT

    int d_selection;

    QListWidget *d_monster_list;
    QPushButton *d_remove;
    QGroupBox *d_add_box;
        QLineEdit *d_name;
        QLineEdit *d_pixmap_path;
        QPushButton *d_select_image;
        QPushButton *d_add_monster;

    public:
        explicit MonsterControlWidget(QWidget *parent = nullptr);
        ~MonsterControlWidget();

        void on_remove();
        void on_select();
        void on_add();
        void on_selection_changed(int selected);

    signals:
        void monster_removed(QString const &name);
        void monster_added(MonsterInfo const &info);
        void monster_selected(QString const &name);
        
};

#endif
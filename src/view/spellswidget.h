#ifndef VIEW_SPELLSWIDGET_H
#define VIEW_SPELLSWIDGET_H

#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QSplitter>
#include <QTextEdit>

class SpellsWidget : public QSplitter
{
    Q_OBJECT

    QWidget *d_list_widget;
        QLabel *d_spells_label;
        QListWidget *d_spells_list;

    QWidget *d_description_widget;
        QLineEdit *d_search;
        QTextEdit *d_description;

    public:
        explicit SpellsWidget(QWidget *parent = nullptr);
        ~SpellsWidget();

        void add_spell(QString const &file) noexcept;
        void show_description(QString const &description) noexcept;

    private slots:
        void on_search_change(QString const &term);
        void on_selection_change(int selected);

    signals:
        void selection_changed(QString const &name);
};

#endif
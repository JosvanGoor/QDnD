#ifndef SPELLSWIDGET_H
#define SPELLSWIDGET_H

#include <QFile>
#include <QFormLayout>
#include <QJsonDocument>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QSplitter>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

#include "spell/spell.h"

class SpellsWidget : public QSplitter
{
    Q_OBJECT

    QWidget *d_list_widget;
        QLabel *d_spells_label;
        QListWidget *d_spells_list;
    QWidget *d_description_widget;
        QLineEdit *d_spell_search;
        QTextEdit *d_description;

    public:
        explicit SpellsWidget(QWidget *parent = nullptr);
        ~SpellsWidget();

        void load_spells(QString const &file);

    private slots:
        void on_search_change(QString const &term);
        void on_selection_change(int selected);
};

#endif
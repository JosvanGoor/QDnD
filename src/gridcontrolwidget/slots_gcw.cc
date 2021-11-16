#include "gridcontrolwidget.h"

#include <iostream>

void GridControlWidget::add_line(QString const &str)
{
    d_lines_list->addItem(str);
}


void GridControlWidget::on_delete_line()
{
    if (d_selection == -1)
        return;

    delete_line(d_selection_name);
    delete d_lines_list->item(d_selection);
    on_unselect();
}


void GridControlWidget::on_selection_changed(int selected)
{
    d_selection = selected;

    if (d_selection == -1)
        d_selection_name = "";
    else
        d_selection_name = d_lines_list->item(d_selection)->text();
}


void GridControlWidget::on_unselect()
{
    d_lines_list->clearSelection();
    d_selection = -1;
    d_selection_name = "";
}


bool GridControlWidget::is_selected(QString const &name)
{
    return d_selection_name == name;
}


bool GridControlWidget::is_drawing()
{
    return d_draw->isChecked();
}


void GridControlWidget::remove_entry_by_name(QString const &name)
{
    for (int idx = 0; idx < d_lines_list->count(); ++idx)
    {
        if (d_lines_list->item(idx)->text() == name)
            delete d_lines_list->item(idx);
    }
}
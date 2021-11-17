#include "monstercontrolwidget.h"

void MonsterControlWidget::on_remove()
{
    if (d_selection == -1)
        return;

    monster_removed(d_monster_list->item(d_selection)->text());
    delete d_monster_list->item(d_selection);
}


void MonsterControlWidget::on_select()
{
    d_pixmap_path->setText
    (
        QFileDialog::getOpenFileName(this, "Select Image", "", "Any File")
    );
}


void MonsterControlWidget::on_add()
{
    if (d_pixmap_path->text().isEmpty())
        return;
    if (d_name->text().isEmpty())
        return;

    QFile file(d_pixmap_path->text());
    file.open(QIODevice::ReadOnly);
    
    MonsterInfo info;
    info.raw_pixmap = file.readAll();
    info.name = d_name->text();

    d_monster_list->addItem(info.name);
    monster_added(info);
}


void MonsterControlWidget::on_selection_changed(int selected)
{
    d_selection = selected;
    
    if (selected != -1)
        monster_selected(d_monster_list->item(selected)->text());
}
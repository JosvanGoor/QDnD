#include "connectdialog.h"

ConnectDialogInfo ConnectDialog::get_entries()
{
    ConnectDialogInfo info;

    info.hostname = d_hostname->text();
    bool status = false;
    info.port = d_port->text().toUShort(&status);
    if (!status)
        info.port = 4144;
    info.character_name = d_character_name->text();
    info.pixmap_path = d_pixmap_path->text();

    return info;
}
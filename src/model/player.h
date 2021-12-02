#ifndef MODEL_PLAYER_H
#define MODEL_PLAYER_H

#include <QColor>
#include <QJsonObject>
#include <QString>

#include "../utility/enums.h"

class Player
{
    QString d_identifier;
    QString d_avatar_key;
    QColor d_color;
    GridScale d_size;

    public:
        Player();
        Player(QString const &id, QString const &key, QColor const &col, GridScale size = GridScale::MEDIUM);
        ~Player();

        // getters
        QString const &identifier() const;
        QString const &avatar_key() const;
        QColor const &color() const;
        GridScale size() const;

        // serialize
        QJsonObject serialize() const noexcept;
};

#endif
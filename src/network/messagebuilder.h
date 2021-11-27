#ifndef NETWORK_MESSAGEBUILDER_H
#define NETWORK_MESSAGEBUILDER_H

#include <QJsonDocument>
#include <QJsonObject>

#include "../utility/enums.h"

// system
QJsonDocument ping_message() noexcept;
QJsonDocument pong_message() noexcept;

// file transfer

// simple

#endif
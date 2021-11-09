#include "spell.h"

QString const &Spell::name() const noexcept
{
    return d_name;
}

QString const &Spell::source() const noexcept
{
    return d_source;
}

int Spell::level() const noexcept
{
    return d_level;
}

bool Spell::is_ritual() const noexcept
{
    return d_ritual;
}

QString const &Spell::range() const noexcept
{
    return d_range;
}

QString const &Spell::casting_time() const noexcept
{
    return d_casting_time;
}

QString const &Spell::components() const noexcept
{
    return d_components;
}

QString const &Spell::school() const noexcept
{
    return d_school;
}

QString const &Spell::classes() const noexcept
{
    return d_classes;
}

QString const &Spell::description() const noexcept
{
    return d_description;
}
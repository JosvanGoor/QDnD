#include "griditemgroup.h"

GridItemGroup::GridItemGroup(QString const &name)
:   d_name(name),
    d_visibility(VisibilityMode::HIDDEN),
    d_items(),
    d_subgroups()
{ }
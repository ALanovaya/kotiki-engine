#pragma once

#include "src/entities/states.h"

namespace entity {
struct Entity {
    double x;
    double y;
    EntityState state;
};

}  // namespace entity
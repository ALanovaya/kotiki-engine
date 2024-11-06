#pragma once

#include <kotiki-engine/entities/entity.hpp>

namespace algo {
class Metric {
public:
    virtual double Calculate(entity::Entity first, entity::Entity second) = 0;
};
}  // namespace algo
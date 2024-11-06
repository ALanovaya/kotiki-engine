#pragma once

#include <kotiki-engine/entities/entity.hpp>
#include <vector>

namespace mover {
class Mover {
public:
    virtual void Move(std::vector<entity::Entity> &entities) = 0;
};
}  // namespace mover
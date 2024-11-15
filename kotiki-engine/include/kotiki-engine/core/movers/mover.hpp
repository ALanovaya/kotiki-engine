#pragma once

#include <vector>

#include "kotiki-engine/entities/entity.hpp"

namespace mover {
class Mover {
public:
    virtual void Move(std::vector<entity::Entity>& entities) = 0;
};
}  // namespace mover
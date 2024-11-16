#pragma once

#include <vector>

#include "kotiki-engine/entities/entity.hpp"

namespace entity {
class EntitiesCollection {
private:
    std::vector<Entity> entities_;
    int number_of_moving_entites_;
    std::vector<int> moving_entities_indices_;

public:
    EntitiesCollection(std::vector<Entity> const& entities);
    EntitiesCollection(std::vector<Entity> const& entities, int number_of_moving_entites);
    void SampleNewIndices();

    std::vector<Entity> const& GetEntites() const {
        return entities_;
    }

    std::vector<int> const& GetIndices() const {
        return moving_entities_indices_;
    }
};
}  // namespace entity
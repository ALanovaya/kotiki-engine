#pragma once

#include <random>
#include <set>
#include <vector>

#include "kotiki-engine/entities/entity.hpp"

namespace entity {
class EntitiesCollection {
private:
    std::vector<Entity> entities_;
    std::size_t max_number_of_moving_entites_;
    std::set<int> moving_entities_indices_;

public:
    EntitiesCollection(std::vector<Entity> const& entities);

    EntitiesCollection(std::vector<Entity> const& entities,
                       std::size_t max_number_of_moving_entites);
    void SampleNewIndices();

    std::vector<Entity>& GetEntites() {
        return entities_;
    }

    std::set<int>& GetIndices() {
        return moving_entities_indices_;
    }

    std::vector<Entity> const& GetEntites() const {
        return entities_;
    }

    std::set<int> const& GetIndices() const {
        return moving_entities_indices_;
    }

    std::size_t GetMaxMoving() const {
        return max_number_of_moving_entites_;
    }

    void SetMaxMoving(std::size_t max_number_of_moving_entites) {
        max_number_of_moving_entites_ = std::min(entities_.size(), max_number_of_moving_entites);
        SampleNewIndices();
    }
};
}  // namespace entity
#pragma once

#include <random>
#include <set>
#include <vector>

#include "kotiki-engine/entities/entity.hpp"
#include "kotiki-engine/utils/random.hpp"

namespace entity {
class EntitiesCollection {
public:
    struct StartCoordinates {
        coord_t x0;
        coord_t y0;
    };

private:
    std::vector<Entity> entities_;
    std::vector<StartCoordinates> start_coordinates_;
    std::size_t max_number_of_moving_entites_;

    std::set<std::size_t> moving_entities_indices_;

    util::RandomIntGenerator<std::size_t> gen_;

public:
    EntitiesCollection(std::vector<Entity> const& entities);

    EntitiesCollection(std::vector<Entity> const& entities,
                       std::size_t max_number_of_moving_entites);
    void GenerateNewIndices();

    std::vector<Entity>& GetEntites() {
        return entities_;
    }

    std::set<std::size_t>& GetIndices() {
        return moving_entities_indices_;
    }

    std::vector<StartCoordinates>& GetStartCoordinates() {
        return start_coordinates_;
    }

    std::vector<Entity> const& GetEntites() const {
        return entities_;
    }

    std::set<std::size_t> const& GetIndices() const {
        return moving_entities_indices_;
    }

    std::vector<StartCoordinates> const& GetStartCoordinates() const {
        return start_coordinates_;
    }

    std::size_t GetMaxMoving() const {
        return max_number_of_moving_entites_;
    }

    void SetMaxMoving(std::size_t max_number_of_moving_entites) {
        max_number_of_moving_entites_ = std::min(entities_.size(), max_number_of_moving_entites);
        GenerateNewIndices();
    }
};
}  // namespace entity
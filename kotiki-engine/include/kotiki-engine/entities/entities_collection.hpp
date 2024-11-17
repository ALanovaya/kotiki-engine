#pragma once

#include <algorithm>
#include <random>
#include <set>
#include <vector>

#include "kotiki-engine/entities/entity.hpp"
#include "kotiki-engine/entities/field.h"
#include "kotiki-engine/utils/random.hpp"

namespace entity {
class EntitiesCollection {
private:
    std::vector<Entity> entities_;
    std::vector<std::pair<coord_t, coord_t>> start_coordinates_;
    std::size_t max_number_of_moving_entites_;

    std::set<std::size_t> moving_entities_indices_;

    FieldParams field_params_;

    util::RandomIntGenerator<std::size_t> indices_gen_;

public:
    EntitiesCollection(std::size_t number_of_entities, FieldParams field_params);
    EntitiesCollection(std::size_t number_of_entities, std::size_t max_number_of_moving_entites,
                       FieldParams field_params);
    EntitiesCollection(std::vector<Entity> const& entities, FieldParams field_params);
    EntitiesCollection(std::vector<Entity> const& entities,
                       std::size_t max_number_of_moving_entites, FieldParams field_params);

    void GenerateNewIndices();

    std::vector<Entity>& GetEntites() {
        return entities_;
    }

    std::vector<Entity> const& GetEntites() const {
        return entities_;
    }

    std::set<std::size_t>& GetIndices() {
        return moving_entities_indices_;
    }

    std::set<std::size_t> const& GetIndices() const {
        return moving_entities_indices_;
    }

    std::vector<std::pair<coord_t, coord_t>>& GetStartCoordinates() {
        return start_coordinates_;
    }

    std::vector<std::pair<coord_t, coord_t>> const& GetStartCoordinates() const {
        return start_coordinates_;
    }

    void FixateStartCoordinates() {
        std::transform(entities_.begin(), entities_.end(), start_coordinates_.begin(),
                       [](entity::Entity const& entity) { return std::pair{entity.x, entity.y}; });
    }

    std::size_t GetMaxMoving() const {
        return max_number_of_moving_entites_;
    }

    void SetMaxMoving(std::size_t max_number_of_moving_entites) {
        max_number_of_moving_entites_ = std::min(entities_.size(), max_number_of_moving_entites);
        GenerateNewIndices();
    }

    std::size_t GetNumberOfEntities() const {
        return entities_.size();
    }

    void SetNumberOfEntities(std::size_t number);

    FieldParams& GetFieldParams() {
        return field_params_;
    }

    FieldParams const& GetFieldParams() const {
        return field_params_;
    }

    virtual void SetFieldParams(FieldParams field_params) {
        field_params_ = field_params;
    }
};
}  // namespace entity
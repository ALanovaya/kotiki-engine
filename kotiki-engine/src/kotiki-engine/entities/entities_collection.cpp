#include "kotiki-engine/entities/entities_collection.hpp"

#include <algorithm>
#include <random>

namespace entity {
EntitiesCollection::EntitiesCollection(std::vector<Entity> const& entities)
    : entities_(entities),
      start_coordinates_(entities.size()),
      max_number_of_moving_entites_(entities.size()),
      gen_(0, entities.size() - 1) {
    std::transform(entities.begin(), entities.end(), start_coordinates_.begin(),
                   [](entity::Entity const& entity) { return std::pair{entity.x, entity.y}; });
    GenerateNewIndices();
}

EntitiesCollection::EntitiesCollection(std::vector<Entity> const& entities,
                                       std::size_t max_number_of_moving_entites)
    : entities_(entities),
      start_coordinates_(entities.size()),
      max_number_of_moving_entites_(std::min(entities.size(), max_number_of_moving_entites)),
      gen_(0, entities.size() - 1) {
    std::transform(entities.begin(), entities.end(), start_coordinates_.begin(),
                   [](entity::Entity const& entity) { return std::pair{entity.x, entity.y}; });
    GenerateNewIndices();
}

void EntitiesCollection::GenerateNewIndices() {
    moving_entities_indices_.clear();
    for (int i = 0; i < max_number_of_moving_entites_; ++i) {
        moving_entities_indices_.insert(gen_.Generate());
    }
}
}  // namespace entity
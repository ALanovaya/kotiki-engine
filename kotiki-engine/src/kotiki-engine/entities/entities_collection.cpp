#include "kotiki-engine/entities/entities_collection.hpp"

namespace entity {
EntitiesCollection::EntitiesCollection(std::size_t number_of_entities, FieldParams field_params)
    : entities_(number_of_entities),
      start_coordinates_(number_of_entities),
      max_number_of_moving_entites_(number_of_entities),
      indices_gen_(0, number_of_entities - 1),
      field_params_(field_params) {
    coord_t x_min = static_cast<coord_t>(field_params.x);
    coord_t x_max = static_cast<coord_t>(field_params.x + field_params.w);
    coord_t y_min = static_cast<coord_t>(field_params.y);
    coord_t y_max = static_cast<coord_t>(field_params.y + field_params.h);

    for (int i = 0; i < number_of_entities; ++i) {
        coord_t x = x_min + util::generate_uniform_real() * (x_max - x_min);
        coord_t y = y_min + util::generate_uniform_real() * (y_max - y_min);

        entities_[i] = {x, y};
        start_coordinates_[i] = {x, y};
    }
}

EntitiesCollection::EntitiesCollection(std::size_t number_of_entities,
                                       std::size_t max_number_of_moving_entites,
                                       FieldParams field_params)
    : entities_(number_of_entities),
      start_coordinates_(number_of_entities),
      max_number_of_moving_entites_(max_number_of_moving_entites),
      indices_gen_(0, number_of_entities - 1),
      field_params_(field_params) {
    coord_t x_min = static_cast<coord_t>(field_params.x);
    coord_t x_max = static_cast<coord_t>(field_params.x + field_params.w);
    coord_t y_min = static_cast<coord_t>(field_params.y);
    coord_t y_max = static_cast<coord_t>(field_params.y + field_params.h);

    for (int i = 0; i < number_of_entities; ++i) {
        coord_t x = x_min + util::generate_uniform_real() * (x_max - x_min);
        coord_t y = y_min + util::generate_uniform_real() * (y_max - y_min);

        entities_[i] = {x, y};
        start_coordinates_[i] = {x, y};
    }
}

EntitiesCollection::EntitiesCollection(std::vector<Entity> const& entities,
                                       FieldParams field_params)
    : entities_(entities),
      start_coordinates_(entities.size()),
      max_number_of_moving_entites_(entities.size()),
      indices_gen_(0, entities.size() - 1),
      field_params_(field_params) {
    std::transform(entities.begin(), entities.end(), start_coordinates_.begin(),
                   [](entity::Entity const& entity) { return std::make_pair(entity.x, entity.y); });
    GenerateNewIndices();
}

EntitiesCollection::EntitiesCollection(std::vector<Entity> const& entities,
                                       std::size_t max_number_of_moving_entites,
                                       FieldParams field_params)
    : entities_(entities),
      start_coordinates_(entities.size()),
      max_number_of_moving_entites_(std::min(entities.size(), max_number_of_moving_entites)),
      indices_gen_(0, entities.size() - 1),
      field_params_(field_params) {
    std::transform(entities.begin(), entities.end(), start_coordinates_.begin(),
                   [](entity::Entity const& entity) { return std::make_pair(entity.x, entity.y); });
    GenerateNewIndices();
}

void EntitiesCollection::GenerateNewIndices() {
    moving_entities_indices_.clear();
    for (int i = 0; i < max_number_of_moving_entites_; ++i) {
        moving_entities_indices_.insert(indices_gen_.Generate());
    }
}

void EntitiesCollection::SetNumberOfEntities(std::size_t number) {
    std::size_t prev_size = entities_.size();
    max_number_of_moving_entites_ = std::min(max_number_of_moving_entites_, number);
    entities_.resize(number);
    start_coordinates_.resize(number);

    coord_t x_min = static_cast<coord_t>(field_params_.x);
    coord_t x_max = static_cast<coord_t>(field_params_.x + field_params_.w);
    coord_t y_min = static_cast<coord_t>(field_params_.y);
    coord_t y_max = static_cast<coord_t>(field_params_.y + field_params_.h);

    for (int i = prev_size; i < entities_.size(); ++i) {
        coord_t x = x_min + util::generate_uniform_real() * (x_max - x_min);
        coord_t y = y_min + util::generate_uniform_real() * (y_max - y_min);

        entities_[i] = {x, y};
        start_coordinates_[i] = {x, y};
    }
}
}  // namespace entity
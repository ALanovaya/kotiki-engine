#include "kotiki-engine/entities/scene_manager.hpp"

namespace entity {
void SceneManager::FixAllCoordinates() {
    for (auto& entity : entities_) {
        while (entity.x < field_params_.x) {
            entity.x += field_params_.w;
        }
        while (entity.x > field_params_.x + field_params_.w) {
            entity.x -= field_params_.w;
        }
        while (entity.y < field_params_.y) {
            entity.y += field_params_.h;
        }
        while (entity.y > field_params_.y + field_params_.h) {
            entity.y -= field_params_.h;
        }
    }
}

SceneManager::SceneManager(std::vector<Entity> const& entities, FieldParams field_params,
                           std::size_t max_number_of_moving_entites, int daytime_delta)
    : entities_(entities),
      start_coordinates_(entities.size()),
      max_number_of_moving_entites_(max_number_of_moving_entites),
      indices_gen_(0, entities.size() - 1),
      field_params_(field_params),
      daytime_(DayTime::Day),
      daytime_delta_(daytime_delta),
      current_time_(0) {
    std::transform(entities.begin(), entities.end(), start_coordinates_.begin(),
                   [](entity::Entity const& entity) { return std::make_pair(entity.x, entity.y); });
    GenerateNewIndices();
}

SceneManager::SceneManager(std::size_t number_of_entities, entity::FieldParams field_params,
                           std::size_t max_number_of_moving_entites, int daytime_delta)
    : entities_(number_of_entities),
      start_coordinates_(number_of_entities),
      max_number_of_moving_entites_(max_number_of_moving_entites),
      indices_gen_(0, number_of_entities - 1),
      field_params_(field_params),
      daytime_(DayTime::Day),
      daytime_delta_(daytime_delta),
      current_time_(0) {
    coord_t x_min = static_cast<coord_t>(field_params.x);
    coord_t x_max = static_cast<coord_t>(field_params.x + field_params.w);
    coord_t y_min = static_cast<coord_t>(field_params.y);
    coord_t y_max = static_cast<coord_t>(field_params.y + field_params.h);

    for (int i = 0; i < number_of_entities; ++i) {
        coord_t x = x_min + util::generate_uniform_real() * (x_max - x_min);
        coord_t y = y_min + util::generate_uniform_real() * (y_max - y_min);

        entities_[i] = {x, y};
    }

    std::transform(entities_.begin(), entities_.end(), start_coordinates_.begin(),
                   [](entity::Entity const& entity) { return std::make_pair(entity.x, entity.y); });
}

void SceneManager::GenerateNewIndices() {
    ++current_time_;
    if (current_time_ == daytime_delta_) {
        current_time_ = 0;
        daytime_ = daytime_ == DayTime::Day ? DayTime::Night : DayTime::Day;
    }

    moving_entities_indices_.clear();
    auto number_of_moving = std::min(entities_.size(), max_number_of_moving_entites_);
    number_of_moving = daytime_ == DayTime::Day ? number_of_moving : number_of_moving / 10;
    for (int i = 0; i < number_of_moving; ++i) {
        moving_entities_indices_.insert(indices_gen_.Generate());
    }
}

void SceneManager::SetNumberOfEntities(std::size_t number) {
    std::size_t prev_size = entities_.size();
    indices_gen_.SetMax(number - 1);
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
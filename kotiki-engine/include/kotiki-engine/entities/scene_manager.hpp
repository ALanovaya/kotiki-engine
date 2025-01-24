#pragma once

#include <algorithm>
#include <set>
#include <vector>

#include "kotiki-engine/entities/entity.hpp"
#include "kotiki-engine/utils/random.hpp"

namespace entity {

// Struct to describe size parameters of scene
struct FieldParams {
    int x;
    int y;
    int w;
    int h;
};

// Enum for manipulation with day and night change
enum class DayTime : char { Day = 0, Night };

// SceneManager class to manage events on scene
class SceneManager {
private:
    std::vector<Entity> entities_;  // Vector of entities on scene
    std::vector<std::pair<coord_t, coord_t>>
            start_coordinates_;                 // Starting coordinates of entities
    std::size_t max_number_of_moving_entites_;  // Maximal number of simultanious moving entities
    std::set<std::size_t> moving_entities_indices_;  // Indices of currently moving entities

    FieldParams field_params_;  // Scene size parameters
    DayTime daytime_;           // Current daytime
    int daytime_delta_;         // To determinate how often daytime gonna change
    int current_time_;          // Current step from application start

    util::RandomIntGenerator<std::size_t> indices_gen_;  // Moving entities indices generator

    /**
     * Fixes coordinates of all entities on a scene
     */
    void FixAllCoordinates();

public:
    /**
     * Scene Manager constructor
     *
     * @param entities Vector of entities
     * @param field_params Size parameters of scene
     * @param max_number_of_moving_entities Maximal number of moving entities
     * @param daytime_delta Daytime delta to determinate how often daytime is gonna change
     */
    SceneManager(std::vector<Entity> const& entities, FieldParams field_params,
                 std::size_t max_number_of_moving_entites = 250, int daytime_delta = 20);
    /**
     * Scene Manager constructor
     * Generate entities randomly
     *
     * @param number_of_entities Number of entities
     * @param field_params Size parameters of scene
     * @param max_number_of_moving_entities Maximal number of moving entities
     * @param daytime_delta Daytime delta to determinate how often daytime is gonna change
     */
    SceneManager(std::size_t number_of_entities, FieldParams field_params,
                 std::size_t max_number_of_moving_entites = 250, int daytime_delta = 20);

    /**
     * Generates new indices of moving entities
     */
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

    /**
     * Fixate starting coordinates
     * Makes starting coordinates equal to current entities coordinates
     */
    void FixateStartCoordinates() {
        std::transform(
                entities_.begin(), entities_.end(), start_coordinates_.begin(),
                [](entity::Entity const& entity) { return std::make_pair(entity.x, entity.y); });
    }

    std::size_t GetMaxMoving() const {
        return max_number_of_moving_entites_;
    }

    void SetMaxMoving(std::size_t max_number_of_moving_entites) {
        max_number_of_moving_entites_ = max_number_of_moving_entites;
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

    DayTime GetDayTime() const {
        return daytime_;
    }

    virtual void SetFieldParams(FieldParams field_params) {
        field_params_ = field_params;
        FixAllCoordinates();
    }
};
}  // namespace entity
#pragma once

#include <QApplication>
#include <QComboBox>
#include <QDockWidget>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPen>
#include <QTimer>
#include <memory>
#include <vector>

#include "kotiki-engine/graphics/cats_models.hpp"
#include "kotiki-engine/graphics/fps_counter.hpp"
#include "kotiki-engine/graphics/settings.hpp"
#include "kotiki-engine/graphics/view.hpp"

namespace graphics {
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

private:
    // Initialization methods
    void InitializeScene();
    void InitializeEntities();
    void InitializeWidgets();
    void InitializeTimers();

    void CreateCats();
    void UpdateSceneRect(int width, int height);
    void UpdateCats();

    void ConnectSignals();

private slots:
    // Slots for handling settings changes
    void OnNumberOfCatsChanged(int new_count);

    void OnSceneDimensionsChanged(int new_width, int new_height);

    void OnMetricChanged(std::unique_ptr<algo::Metric>& new_metric);

    void OnR0Changed(coord_t new_R0);

    void OnR1Changed(coord_t new_R1);

    void OnMaxMovingCatsChanged(int new_max_moving_cats);

    void OnMoverChanged(std::unique_ptr<mover::Mover>& new_mover);

    void OnTauChanged(int new_tau);

    // Timer update slots
    void OnUpdateTimer();  // Handles graphical updates (FPS, positions)

    void OnPointTimer();  // Handles game logic updates (movement, states)

private:
    uint64_t iterations_ = 0;
    std::unique_ptr<QGraphicsScene> scene_;
    std::unique_ptr<graphics::ResizableGraphicsView> view_;
    QGraphicsRectItem* border_;  // Scene boundary rectangle

    entity::FieldParams field_params_;  // Parameters of the simulation field
    std::unique_ptr<entity::SceneManager> entities_collection_;  // Manages entities
    int const cats_size_ = 50;                                   // Size of the cat image

    std::unique_ptr<mover::Mover> current_mover_;  // Current movement algorithm
    std::unique_ptr<algo::GridLookupAlgorithm>
            grid_lookup_;  // Algorithm for checking entity states

    graphics::widgets::settings::SettingsWidget* settings_widget_;
    std::unique_ptr<QLabel> fps_label_;
    std::unique_ptr<graphics::widgets::FPSCounter> fps_counter_;

    std::vector<std::unique_ptr<graphics::models::Cats>>
            cats_;  // Graphical representations of cats
    QPixmap calm_image_;
    QPixmap angry_image_;
    QPixmap fighting_image_;
    QPixmap sleep_image_;

    QTimer point_timer_;   // Timer for game logic updates
    QTimer update_timer_;  // Timer for graphical updates
};
}  // namespace graphics
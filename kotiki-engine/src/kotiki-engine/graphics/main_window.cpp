#include "kotiki-engine/graphics/main_window.hpp"

#include <algorithm>
#include <string>

#include "iostream"

namespace graphics {
// Main window constructor: Initializes entire scene, entities, and core functionality
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("kotiki-engine");
    resize(1440, 1024);

    // Setup core components of the application
    InitializeScene();
    InitializeEntities();
    InitializeWidgets();
    InitializeTimers();
    ConnectSignals();

    // Start update and point timers for animation and game logic
    update_timer_.start(10);
    point_timer_.start(500);  // Initial tau value

    show();
}

void MainWindow::InitializeScene() {
    // Create scene with grass background and custom view
    scene_ = std::make_unique<QGraphicsScene>(this);
    QPixmap grass_texture("assets/textures/grass.png");
    scene_->setBackgroundBrush(QBrush(grass_texture));

    // Setup resizable graphics view as central widget
    view_ = std::make_unique<graphics::ResizableGraphicsView>(scene_.get());
    setCentralWidget(view_.get());

    UpdateSceneRect(3000, 2000);
}

void MainWindow::InitializeEntities() {
    // Complex initialization of scene entities and movement logic
    field_params_ = {0, 0, 3000, 2000};
    entities_collection_ = std::make_unique<entity::SceneManager>(cats_size_, field_params_, 20);

    // Load different cat state images
    calm_image_ = QPixmap("assets/textures/pushin.png");
    angry_image_ = QPixmap("assets/textures/angry_pusheen.png");
    fighting_image_ = QPixmap("assets/textures/draka_pusheen.png");
    sleep_image_ = QPixmap("assets/textures/sleep_pusheen.png");

    CreateCats();

    // Initialize movement and interaction algorithms
    current_mover_ = std::make_unique<mover::RandomMover>(10, 100);
    grid_lookup_ = std::make_unique<algo::GridLookupAlgorithm>(
            200.0, 500.0, std::make_unique<algo::EuclideanMetric>());
}

// Initialize widgets: settings, status bar, and FPS counter
void MainWindow::InitializeWidgets() {
    // Create settings widget with scene and entity parameters
    settings_widget_ = new graphics::widgets::settings::SettingsWidget(
            this, entities_collection_->GetNumberOfEntities(), field_params_.w, field_params_.h,
            entities_collection_->GetMaxMoving());
    addDockWidget(Qt::RightDockWidgetArea, settings_widget_);

    // Create label for displaying FPS
    fps_label_ = std::make_unique<QLabel>(this);
    statusBar()->addPermanentWidget(fps_label_.get());

    // Initialize frame counter
    fps_counter_ = std::make_unique<graphics::widgets::FPSCounter>();
}

// Set default timer intervals
void MainWindow::InitializeTimers() {
    point_timer_.setInterval(500);  // Base point update interval
    update_timer_.setInterval(10);  // Quick position update
}

// Create cats on the scene
void MainWindow::CreateCats() {
    // Generate cats based on entity collection parameters
    for (int i = 0; i < entities_collection_->GetNumberOfEntities(); ++i) {
        auto cat = std::make_unique<graphics::models::Cats>(
                calm_image_, entities_collection_->GetEntites()[i].x,
                entities_collection_->GetEntites()[i].y);
        cats_.push_back(std::move(cat));
        scene_->addItem(cats_.back().get());
    }
}

// Update scene rectangle with border addition
void MainWindow::UpdateSceneRect(int width, int height) {
    static bool first_call = true;
    scene_->setSceneRect(0, 0, width, height);

    // Remove old border on subsequent calls
    if (!first_call) {
        scene_->removeItem(border_);
    }

    // Create new border with padding
    QRectF scene_rect = scene_->sceneRect();
    QRectF border_rect(scene_rect.x() + 30, scene_rect.y() + 40, scene_rect.width() + 150,
                       scene_rect.height() + 100);
    border_ = scene_->addRect(border_rect, QPen(QColor(110, 69, 19), 10));
    border_->setZValue(1);
    first_call = false;
}

// Completely refresh cats on the scene
void MainWindow::UpdateCats() {
    // Clear existing cats and create new ones
    for (auto& cat : cats_) {
        scene_->removeItem(cat.get());
    }
    cats_.clear();
    CreateCats();
}

// Connect signals for interactive control
void MainWindow::ConnectSignals() {
    // Bind settings widget signals to corresponding slots
    connect(settings_widget_, &graphics::widgets::settings::SettingsWidget::NumberOfCatsChanged,
            this, &MainWindow::OnNumberOfCatsChanged);

    // Connect various settings change signals
    connect(settings_widget_, &graphics::widgets::settings::SettingsWidget::SceneDimensionsChanged,
            this, &MainWindow::OnSceneDimensionsChanged);
    connect(settings_widget_, &graphics::widgets::settings::SettingsWidget::MetricChanged, this,
            &MainWindow::OnMetricChanged);
    connect(settings_widget_, &graphics::widgets::settings::SettingsWidget::R0Changed, this,
            &MainWindow::OnR0Changed);
    connect(settings_widget_, &graphics::widgets::settings::SettingsWidget::R1Changed, this,
            &MainWindow::OnR1Changed);
    connect(settings_widget_, &graphics::widgets::settings::SettingsWidget::MaxMovingCatsChanged,
            this, &MainWindow::OnMaxMovingCatsChanged);
    connect(settings_widget_, &graphics::widgets::settings::SettingsWidget::MoverChanged, this,
            &MainWindow::OnMoverChanged);
    connect(settings_widget_, &graphics::widgets::settings::SettingsWidget::TauChanged, this,
            &MainWindow::OnTauChanged);

    // Connect timers to update handlers
    connect(&update_timer_, &QTimer::timeout, this, &MainWindow::OnUpdateTimer);
    connect(&point_timer_, &QTimer::timeout, this, &MainWindow::OnPointTimer);

    // Connect button to logging
    connect(settings_widget_, &graphics::widgets::settings::SettingsWidget::LoggingToggled, this,
            &MainWindow::OnLoggingToggled);
}

// Handler for changing number of cats
void MainWindow::OnNumberOfCatsChanged(int new_count) {
    // Update number of entities and redraw cats
    entities_collection_->SetNumberOfEntities(new_count);
    UpdateCats();
}

// Handler for changing scene dimensions
void MainWindow::OnSceneDimensionsChanged(int new_width, int new_height) {
    // Update scene size, field parameters, and reset initial coordinates
    UpdateSceneRect(new_width, new_height);
    field_params_ = {0, 0, new_width, new_height};
    entities_collection_->SetFieldParams(field_params_);
    entities_collection_->FixateStartCoordinates();
}

// Handler for changing distance metric
void MainWindow::OnMetricChanged(std::unique_ptr<algo::Metric>& new_metric) {
    // Update grid lookup algorithm with new metric
    grid_lookup_->SetMetric(std::move(new_metric));
}

// Handler for changing R0 parameter
void MainWindow::OnR0Changed(coord_t new_R0) {
    grid_lookup_->SetR0(new_R0);
}

// Handler for changing R1 parameter
void MainWindow::OnR1Changed(coord_t new_R1) {
    grid_lookup_->SetR1(new_R1);
}

// Handler for changing max moving cats
void MainWindow::OnMaxMovingCatsChanged(int new_max_moving_cats) {
    entities_collection_->SetMaxMoving(new_max_moving_cats);
}

// Handler for changing movement algorithm
void MainWindow::OnMoverChanged(std::unique_ptr<mover::Mover>& new_mover) {
    // Reset start coordinates and update mover
    entities_collection_->FixateStartCoordinates();
    current_mover_ = std::move(new_mover);
}

// Handler for changing update interval (tau)
void MainWindow::OnTauChanged(int new_tau) {
    point_timer_.setInterval(new_tau);
}

// Handler for toggling logging
void MainWindow::OnLoggingToggled(bool enabled) {
    logging_enabled_ = enabled;
}

// Handler for update timer
void MainWindow::OnUpdateTimer() {
    // Update positions of all cats
    for (auto i : entities_collection_->GetIndices()) {
        cats_[i]->UpdatePosition();
    }
    fps_counter_->FrameRendered();

    view_->ShowNightFilter(entities_collection_->GetDayTime() == entity::DayTime::Night);
    fps_label_->setText(QString("FPS: %1").arg(fps_counter_->GetCurrentFps()));
}

void LogCoordinates(std::vector<entity::EntityState> states,
                    std::unique_ptr<entity::SceneManager>& entities_collection_,
                    uint64_t iterations) {
    std::cout << "\nIteration #" << iterations << "\n";
    if (entities_collection_->GetDayTime() == entity::DayTime::Night) {
        std::cout << "Night !\n";
    }
    if (entities_collection_->GetIndices().empty()) {
        return;
    }
    for (auto idx : entities_collection_->GetIndices()) {
        std::string state;
        switch (states[idx]) {
            case entity::EntityState::Calm:
                state = "calm";
                break;
            case entity::EntityState::Angry:
                state = "angry";
                break;
            case entity::EntityState::Fighting:
                state = "fighting";
                break;
        }
        auto coordinates = "(" + std::to_string(entities_collection_->GetEntites()[idx].x) + ", " +
                           std::to_string(entities_collection_->GetEntites()[idx].y) + ")";
        auto log_string = "Cat №" + std::to_string(idx) + " moved to " + coordinates +
                          " and has state " + state + "\n";
        std::cout << log_string;
    }
}

void MainWindow::OnPointTimer() {
    // Complex logic for cat movement and state updates
    iterations_++;
    current_mover_->Move(*entities_collection_);
    auto set_of_fixed_entities = current_mover_->FixEntityCoordinates(*entities_collection_);
    auto states = grid_lookup_->GetStates(*entities_collection_);

    if (logging_enabled_) {
        LogCoordinates(states, entities_collection_, iterations_);
    }

    // Detailed state and image management for each cat
    for (int i = 0; i < entities_collection_->GetNumberOfEntities(); ++i) {
        cats_[i]->MoveTo(entities_collection_->GetEntites()[i].x,
                         entities_collection_->GetEntites()[i].y, set_of_fixed_entities.count(i));

        // Complex image selection based on cat state and day/night cycle
        QPixmap const* image = &calm_image_;
        switch (states[i]) {
            case entity::EntityState::Calm:
                image = (entities_collection_->GetDayTime() == entity::DayTime::Day)
                                ? &calm_image_
                                : &sleep_image_;
                break;
            case entity::EntityState::Angry:
                image = &angry_image_;
                break;
            case entity::EntityState::Fighting:
                image = &fighting_image_;
                break;
        }
        cats_[i]->UpdatePixmap(*image);
    }
}

}  // namespace graphics

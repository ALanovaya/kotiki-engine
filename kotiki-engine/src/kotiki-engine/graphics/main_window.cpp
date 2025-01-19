#include "kotiki-engine/graphics/main_window.hpp"

namespace graphics {
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("kotiki-engine");
    resize(1440, 1024);

    InitializeScene();
    InitializeEntities();
    InitializeWidgets();
    InitializeTimers();
    ConnectSignals();

    update_timer_.start(10);
    point_timer_.start(500);  // Initial tau value

    show();
}

void MainWindow::InitializeScene() {
    scene_ = std::make_unique<QGraphicsScene>(this);
    QPixmap grass_texture("assets/textures/grass.png");
    scene_->setBackgroundBrush(QBrush(grass_texture));

    view_ = std::make_unique<graphics::ResizableGraphicsView>(scene_.get());
    setCentralWidget(view_.get());

    UpdateSceneRect(3000, 2000);
}

void MainWindow::InitializeEntities() {
    field_params_ = {0, 0, 3000, 2000};
    entities_collection_ = std::make_unique<entity::SceneManager>(cats_size_, field_params_, 20);

    calm_image_ = QPixmap("assets/textures/pushin.png");
    angry_image_ = QPixmap("assets/textures/angry_pusheen.png");
    fighting_image_ = QPixmap("assets/textures/draka_pusheen.png");
    sleep_image_ = QPixmap("assets/textures/sleep_pusheen.png");
    CreateCats();

    current_mover_ = std::make_unique<mover::RandomMover>(10, 100);
    grid_lookup_ = std::make_unique<algo::GridLookupAlgorithm>(
            200.0, 500.0, std::make_unique<algo::EuclideanMetric>());
}

void MainWindow::InitializeWidgets() {
    settings_widget_ = new graphics::widgets::settings::SettingsWidget(
            this, entities_collection_->GetNumberOfEntities(), field_params_.w, field_params_.h,
            entities_collection_->GetMaxMoving());
    addDockWidget(Qt::RightDockWidgetArea, settings_widget_);

    fps_label_ = std::make_unique<QLabel>(this);
    statusBar()->addPermanentWidget(fps_label_.get());

    fps_counter_ = std::make_unique<graphics::widgets::FPSCounter>();
}

void MainWindow::InitializeTimers() {
    point_timer_.setInterval(500);  // Default tau
    update_timer_.setInterval(10);
}

void MainWindow::CreateCats() {
    for (int i = 0; i < entities_collection_->GetNumberOfEntities(); ++i) {
        auto cat = std::make_unique<graphics::models::Cats>(
                calm_image_, entities_collection_->GetEntites()[i].x,
                entities_collection_->GetEntites()[i].y);
        cats_.push_back(std::move(cat));
        scene_->addItem(cats_.back().get());
    }
}

void MainWindow::UpdateSceneRect(int width, int height) {
    static bool first_call = true;
    scene_->setSceneRect(0, 0, width, height);

    if (!first_call) {
        scene_->removeItem(border_);  // Remove old border
    }

    QRectF scene_rect = scene_->sceneRect();
    QRectF border_rect(scene_rect.x() + 30, scene_rect.y() + 40, scene_rect.width() + 150,
                       scene_rect.height() + 100);
    border_ = scene_->addRect(border_rect, QPen(QColor(110, 69, 19), 10));
    border_->setZValue(1);
    first_call = false;
}

void MainWindow::UpdateCats() {
    for (auto& cat : cats_) {
        scene_->removeItem(cat.get());
    }
    cats_.clear();
    CreateCats();
}

void MainWindow::ConnectSignals() {
    connect(settings_widget_, &graphics::widgets::settings::SettingsWidget::NumberOfCatsChanged,
            this, &MainWindow::OnNumberOfCatsChanged);
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

    connect(&update_timer_, &QTimer::timeout, this, &MainWindow::OnUpdateTimer);
    connect(&point_timer_, &QTimer::timeout, this, &MainWindow::OnPointTimer);
}

}  // namespace graphics

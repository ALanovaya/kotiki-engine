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
    void InitializeScene();
    void InitializeEntities();
    void InitializeWidgets();
    void InitializeTimers();

    void CreateCats();
    void UpdateSceneRect(int width, int height);
    void UpdateCats();

    void ConnectSignals();

private slots:

    void OnNumberOfCatsChanged(int new_count) {
        entities_collection_->SetNumberOfEntities(new_count);
        UpdateCats();
    }

    void OnSceneDimensionsChanged(int new_width, int new_height) {
        UpdateSceneRect(new_width, new_height);
        field_params_ = {0, 0, new_width, new_height};
        entities_collection_->SetFieldParams(field_params_);
        entities_collection_->FixateStartCoordinates();
    }

    void OnMetricChanged(std::unique_ptr<algo::Metric>& new_metric) {
        grid_lookup_->SetMetric(std::move(new_metric));
    }

    void OnR0Changed(coord_t new_R0) {
        grid_lookup_->SetR0(new_R0);
    }

    void OnR1Changed(coord_t new_R1) {
        grid_lookup_->SetR1(new_R1);
    }

    void OnMaxMovingCatsChanged(int new_max_moving_cats) {
        entities_collection_->SetMaxMoving(new_max_moving_cats);
    }

    void OnMoverChanged(std::unique_ptr<mover::Mover>& new_mover) {
        entities_collection_->FixateStartCoordinates();
        current_mover_ = std::move(new_mover);
    }

    void OnTauChanged(int new_tau) {
        point_timer_.setInterval(new_tau);
    }

    void OnUpdateTimer() {
        for (auto i : entities_collection_->GetIndices()) {
            cats_[i]->UpdatePosition();
        }
        fps_counter_->FrameRendered();

        view_->ShowNightFilter(entities_collection_->GetDayTime() == entity::DayTime::Night);
        fps_label_->setText(QString("FPS: %1").arg(fps_counter_->GetCurrentFps()));
    }

    void OnPointTimer() {
        current_mover_->Move(*entities_collection_);
        auto set_of_fixed_entities = current_mover_->FixEntityCoordinates(*entities_collection_);
        auto states = grid_lookup_->GetStates(*entities_collection_);

        for (int i = 0; i < entities_collection_->GetNumberOfEntities(); ++i) {
            cats_[i]->MoveTo(entities_collection_->GetEntites()[i].x,
                             entities_collection_->GetEntites()[i].y,
                             set_of_fixed_entities.count(i));
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

private:
    std::unique_ptr<QGraphicsScene> scene_;
    std::unique_ptr<graphics::ResizableGraphicsView> view_;
    QGraphicsRectItem* border_ = nullptr;

    entity::FieldParams field_params_;
    std::unique_ptr<entity::SceneManager> entities_collection_;
    int const cats_size_ = 50;

    std::unique_ptr<mover::Mover> current_mover_;
    std::unique_ptr<algo::GridLookupAlgorithm> grid_lookup_;

    graphics::widgets::settings::SettingsWidget* settings_widget_;
    std::unique_ptr<QLabel> fps_label_;
    std::unique_ptr<graphics::widgets::FPSCounter> fps_counter_;

    std::vector<std::unique_ptr<graphics::models::Cats>> cats_;
    QPixmap calm_image_;
    QPixmap angry_image_;
    QPixmap fighting_image_;
    QPixmap sleep_image_;

    QTimer point_timer_;
    QTimer update_timer_;
};
}  // namespace graphics
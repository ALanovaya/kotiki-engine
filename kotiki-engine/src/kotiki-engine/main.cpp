#include <QApplication>
#include <QComboBox>
#include <QDockWidget>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPen>
#include <memory>
#include <qdockwidget.h>
#include <vector>

#include "kotiki-engine/entities/field.h"
#include "kotiki-engine/graphics/cats_models.hpp"
#include "kotiki-engine/graphics/fps_counter.hpp"
#include "kotiki-engine/graphics/palette.hpp"
#include "kotiki-engine/graphics/settings.hpp"
#include "kotiki-engine/graphics/view.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    graphics::theme::SetPalette(app);

    QMainWindow main_window;
    main_window.setWindowTitle("kotiki-engine");
    main_window.resize(1440, 1024);

    auto scene = std::make_unique<QGraphicsScene>(&main_window);

    QPixmap grass_texture("assets/textures/grass.png");
    scene->setBackgroundBrush(QBrush(grass_texture));

    auto view = std::make_unique<graphics::ResizableGraphicsView>(scene.get());
    main_window.setCentralWidget(view.get());

    scene->setSceneRect(0, 0, 3000, 2000);
    FieldParams field_params = {0, 0, 3000, 2000};

    QRectF scene_rect = scene->sceneRect();
    QRectF border_rect(scene_rect.x() + 30, scene_rect.y() + 40, scene_rect.width() + 150,
                       scene_rect.height() + 100);
    QGraphicsRectItem* border = scene->addRect(border_rect, QPen(QColor(110, 69, 19), 10));
    border->setZValue(1);

    QPixmap calm_image("assets/textures/pushin.png");
    QPixmap angry_image("assets/textures/angry_pusheen.png");
    QPixmap fighting_image("assets/textures/draka_pusheen.png");

    int const cats_size = 50;

    std::vector<std::unique_ptr<graphics::models::Cats>> cats;
    entity::EntitiesCollection entities_collection(cats_size, 20, field_params);

    for (int i = 0; i < entities_collection.GetNumberOfEntities(); ++i) {
        auto cat = std::make_unique<graphics::models::Cats>(calm_image,
                                                            entities_collection.GetEntites()[i].x,
                                                            entities_collection.GetEntites()[i].y);
        cats.push_back(std::move(cat));
        scene->addItem(cats.back().get());
    }

    auto random_mover = std::make_unique<mover::RandomMover>(10, 100);
    std::unique_ptr<mover::Mover> current_mover = std::move(random_mover);
    algo::GridLookupAlgorithm grid_lookup(200.0, 500.0, std::make_unique<algo::EuclideanMetric>());

    QTimer point_timer;
    QTimer update_timer;

    graphics::widgets::settings::SettingsWidget* settings_widget =
            new graphics::widgets::settings::SettingsWidget(
                    &main_window, entities_collection.GetNumberOfEntities(), field_params.w,
                    field_params.h, entities_collection.GetMaxMoving());
    main_window.addDockWidget(Qt::RightDockWidgetArea, settings_widget);

    QObject::connect(settings_widget,
                     &graphics::widgets::settings::SettingsWidget::NumberOfCatsChanged,
                     [&](int new_count) {
                         for (auto& cat : cats) {
                             scene->removeItem(cat.get());
                         }
                         cats.clear();

                         entities_collection.SetNumberOfEntities(new_count);

                         for (int i = 0; i < new_count; ++i) {
                             auto cat = std::make_unique<graphics::models::Cats>(
                                     calm_image, entities_collection.GetEntites()[i].x,
                                     entities_collection.GetEntites()[i].y);
                             cats.push_back(std::move(cat));
                             scene->addItem(cats.back().get());
                         }
                     });

    QObject::connect(settings_widget,
                     &graphics::widgets::settings::SettingsWidget::SceneDimensionsChanged,
                     [&](int new_width, int new_height) {
                         scene->setSceneRect(0, 0, new_width, new_height);
                         FieldParams field_params = {0, 0, new_width, new_height};
                         entities_collection.SetFieldParams(field_params);
                         entities_collection.FixateStartCoordinates();

                         scene->removeItem(border);

                         QRectF scene_rect = scene->sceneRect();
                         QRectF border_rect(scene_rect.x() + 30, scene_rect.y() + 40,
                                            scene_rect.width() + 150, scene_rect.height() + 100);
                         border = scene->addRect(border_rect, QPen(QColor(110, 69, 19), 10));
                         border->setZValue(1);
                     });

    QObject::connect(settings_widget, &graphics::widgets::settings::SettingsWidget::MetricChanged,
                     [&](std::unique_ptr<algo::Metric>& new_metric) {
                         grid_lookup.SetMetric(std::move(new_metric));
                     });

    QObject::connect(settings_widget, &graphics::widgets::settings::SettingsWidget::R0Changed,
                     [&](coord_t new_R0) { grid_lookup.SetR0(new_R0); });

    QObject::connect(settings_widget, &graphics::widgets::settings::SettingsWidget::R1Changed,
                     [&](coord_t new_R1) { grid_lookup.SetR1(new_R1); });

    QObject::connect(settings_widget,
                     &graphics::widgets::settings::SettingsWidget::MaxMovingCatsChanged,
                     [&](int new_max_moving_cats) {
                         entities_collection.SetMaxMoving(new_max_moving_cats);
                     });
    QObject::connect(settings_widget, &graphics::widgets::settings::SettingsWidget::MoverChanged,
                     [&](std::unique_ptr<mover::Mover>& new_mover) {
                         entities_collection.FixateStartCoordinates();
                         current_mover = std::move(new_mover);
                     });

    graphics::widgets::FPSCounter fps_counter;
    auto fps_label = std::make_unique<QLabel>(&main_window);
    main_window.statusBar()->addPermanentWidget(fps_label.get());

    QObject::connect(&update_timer, &QTimer::timeout, [&]() {
        for (auto i : entities_collection.GetIndices()) {
            cats[i]->UpdatePosition();
        }
        fps_counter.FrameRendered();
    });

    QObject::connect(&point_timer, &QTimer::timeout, [&]() {
        current_mover->Move(entities_collection);
        auto set_of_fixed_entities = current_mover->FixEntityCoordinates(entities_collection);
        auto states = grid_lookup.GetStates(entities_collection);
        for (int i = 0; i < entities_collection.GetNumberOfEntities(); ++i) {
            cats[i]->MoveTo(entities_collection.GetEntites()[i].x,
                            entities_collection.GetEntites()[i].y, set_of_fixed_entities.count(i));
            switch (states[i]) {
                case entity::EntityState::Calm:
                    cats[i]->UpdatePixmap(calm_image);
                    break;
                case entity::EntityState::Angry:
                    cats[i]->UpdatePixmap(angry_image);
                    break;
                case entity::EntityState::Fighting:
                    cats[i]->UpdatePixmap(fighting_image);
                    break;
            }
        }
        fps_label->setText(QString("FPS: %1").arg(fps_counter.GetCurrentFps()));
    });

    bool is_tau_set = false;

    if (!is_tau_set) {
        point_timer.start(500);
    }

    QObject::connect(settings_widget, &graphics::widgets::settings::SettingsWidget::TauChanged,
                     [&](int new_tau) {
                         if (point_timer.isActive()) {
                             point_timer.stop();
                         }
                         point_timer.start(new_tau);
                         is_tau_set = true;
                     });

    update_timer.start(10);

    main_window.show();

    return app.exec();
}
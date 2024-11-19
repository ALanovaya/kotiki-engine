#include <QApplication>
#include <QDockWidget>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QLabel>
#include <QMainWindow>
#include <QPen>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>
#include <iostream>
#include <memory>
#include <qdockwidget.h>
#include <vector>

#include "kotiki-engine/core/algorithms/naive.hpp"
#include "kotiki-engine/core/metrics/euclidean.hpp"
#include "kotiki-engine/core/movers/random_mover.hpp"
#include "kotiki-engine/entities/field.h"
#include "kotiki-engine/graphics/cats_models.hpp"
#include "kotiki-engine/graphics/fps_counter.hpp"
#include "kotiki-engine/graphics/palette.hpp"
#include "kotiki-engine/graphics/view.hpp"

class SettingsWidget : public QDockWidget {
    Q_OBJECT

public:
    SettingsWidget(QWidget* parent = nullptr, int current_val = 20)
        : QDockWidget("Settings", parent) {
        QWidget* widget = new QWidget(this);
        QVBoxLayout* layout = new QVBoxLayout(widget);

        QLabel* label = new QLabel("Number of Cats:", this);
        spinBox_ = new QSpinBox(this);
        spinBox_->setRange(1, 50000);
        spinBox_->setValue(current_val);

        QPushButton* apply_button = new QPushButton("Apply", this);

        layout->addWidget(label);
        layout->addWidget(spinBox_);
        layout->addWidget(apply_button);
        setWidget(widget);

        connect(apply_button, &QPushButton::clicked, this, &SettingsWidget::OnApply);
    }

signals:
    void NumberOfCatsChanged(int new_count);

private slots:

    void OnApply() {
        emit NumberOfCatsChanged(spinBox_->value());
    }

private:
    QSpinBox* spinBox_;
};

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

    mover::RandomMover random_mover(10, 100);
    algo::NaiveAlgorithm naive_algorithm(200.0, 500.0, std::make_unique<algo::EuclideanMetric>());

    QTimer point_timer;
    QTimer update_timer;

    SettingsWidget* settings_widget =
            new SettingsWidget(&main_window, entities_collection.GetNumberOfEntities());
    main_window.addDockWidget(Qt::RightDockWidgetArea, settings_widget);

    QObject::connect(settings_widget, &SettingsWidget::NumberOfCatsChanged, [&](int new_count) {
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

    graphics::widgets::FPSCounter fps_counter;
    auto fps_label = std::make_unique<QLabel>(&main_window);
    main_window.statusBar()->addPermanentWidget(fps_label.get());

    QObject::connect(&update_timer, &QTimer::timeout, [&]() {
        for (int i = 0; i < entities_collection.GetNumberOfEntities(); ++i) {
            cats[i]->UpdatePosition();
        }
        fps_counter.FrameRendered();
    });

    QObject::connect(&point_timer, &QTimer::timeout, [&]() {
        random_mover.Move(entities_collection);
        auto states = naive_algorithm.GetStates(entities_collection);
        auto set_of_fixed_entities = random_mover.FixEntityCoordinates(entities_collection);
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

    point_timer.start(500);
    update_timer.start(10);

    main_window.show();

    return app.exec();
}

#include "main.moc"
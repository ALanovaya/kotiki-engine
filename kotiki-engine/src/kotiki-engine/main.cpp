#include <QApplication>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QMainWindow>
#include <QPixmap>
#include <QStatusBar>
#include <QTimer>
#include <memory>
#include <random>
#include <vector>

#include "kotiki-engine/core/algorithms/naive.hpp"
#include "kotiki-engine/core/metrics/euclidean.hpp"
#include "kotiki-engine/core/movers/random_mover.hpp"
#include "kotiki-engine/graphics/fps_counter.hpp"
#include "kotiki-engine/graphics/view.hpp"

class Cats : public QGraphicsPixmapItem {
public:
    Cats(QPixmap const& pixmap, qreal x, qreal y)
        : QGraphicsPixmapItem(pixmap), target_x_(x), target_y_(y) {
        setPos(x, y);
    }

    void MoveTo(double x, double y) {
        target_x_ = x;
        target_y_ = y;
    }

    void UpdatePosition() {
        qreal current_x = pos().x();
        qreal current_y = pos().y();

        qreal dx = target_x_ - current_x;
        qreal dy = target_y_ - current_y;

        qreal step_x = dx / 30;
        qreal step_y = dy / 30;

        setPos(current_x + step_x, current_y + step_y);
    }

    void UpdatePixmap(QPixmap const& pixmap) {
        setPixmap(pixmap);
    }

private:
    qreal target_x_;
    qreal target_y_;
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QMainWindow main_window;
    main_window.setWindowTitle("Random Moving Cats");
    main_window.resize(1440, 1024);

    QPixmap grass_texture("assets/textures/grass.png");

    auto scene = std::make_unique<QGraphicsScene>(&main_window);
    scene->setSceneRect(-1000, -1000, 2000, 2000);
    scene->setBackgroundBrush(QBrush(grass_texture));

    auto view = std::make_unique<graphics::ResizableGraphicsView>(scene.get());
    main_window.setCentralWidget(view.get());

    QPixmap calm_image("assets/textures/pushin.png");
    QPixmap angry_image("assets/textures/angry_pusheen.png");
    QPixmap fighting_image("assets/textures/draka_pusheen.png");

    const int cats_size = 50;

    std::vector<entity::Entity> entities(cats_size);
    std::vector<std::unique_ptr<Cats>> cats;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-1000, 1000);

    for (int i = 0; i < cats_size; ++i) {
        entities[i] = {dis(gen), dis(gen)};
        auto cat = std::make_unique<Cats>(calm_image, entities[i].x, entities[i].y);
        cats.push_back(std::move(cat));
        scene->addItem(cats.back().get());
    }

    mover::RandomMover random_mover(10, 100);
    algo::NaiveAlgorithm naive_algorithm(200.0, 500.0, new algo::EuclideanMetric);

    QTimer point_timer;
    QTimer update_timer;

    graphics::widgets::FPSCounter fps_counter;
    auto fps_label = std::make_unique<QLabel>(&main_window);
    main_window.statusBar()->addPermanentWidget(fps_label.get());

    QObject::connect(&update_timer, &QTimer::timeout, [&]() {
        for (size_t i = 0; i < entities.size(); ++i) {
            cats[i]->UpdatePosition();
        }
        fps_counter.FrameRendered();
    });

    QObject::connect(&point_timer, &QTimer::timeout, [&]() {
        random_mover.Move(entities);
        auto states = naive_algorithm.GetStates(entities);
        for (size_t i = 0; i < entities.size(); ++i) {
            cats[i]->MoveTo(entities[i].x, entities[i].y);
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
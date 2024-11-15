#include <QApplication>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QMainWindow>
#include <QPixmap>
#include <QStatusBar>
#include <QTimer>
#include <QWheelEvent>
#include <cmath>

#include "kotiki-engine/graphics/fps_counter.hpp"
#include "kotiki-engine/graphics/view.hpp"

class MovingPixmap : public QGraphicsPixmapItem {
public:
    MovingPixmap(QPixmap const& pixmap, qreal orbitRadius, qreal speed)
        : QGraphicsPixmapItem(pixmap), m_orbitRadius_(orbitRadius), m_speed_(speed), m_angle_(0) {
        setTransformOriginPoint(pixmap.width() / 2.0, pixmap.height() / 2.0);
    }

    void advance(int phase) {
        if (!phase) return;
        m_angle_ += m_speed_;
        setPos(m_orbitRadius_ * cos(m_angle_) - pixmap().width() / 2.0,
               m_orbitRadius_ * sin(m_angle_) - pixmap().height() / 2.0);
    }

private:
    qreal m_orbitRadius_;
    qreal m_speed_;
    qreal m_angle_;
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QMainWindow main_window;
    main_window.setWindowTitle("Two Cats Orbiting");
    main_window.resize(800, 600);

    QPixmap pixmap("asserts/textures/grass.png");

    QGraphicsScene* scene = new QGraphicsScene(&main_window);
    scene->setSceneRect(-300, -300, 600, 600);
    scene->setBackgroundBrush(QBrush(pixmap));

    graphics::ResizableGraphicsView* view = new graphics::ResizableGraphicsView(scene);
    main_window.setCentralWidget(view);

    // Load images
    QPixmap image1("asserts/textures/pushin.png");
    QPixmap image2("asserts/textures/pushin.png");

    // Create two images
    MovingPixmap* image_item1 = new MovingPixmap(image1, 100, 0.05);
    MovingPixmap* image_item2 = new MovingPixmap(image2, 200, 0.03);

    scene->addItem(image_item1);
    scene->addItem(image_item2);

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    timer.start(10);

    graphics::widgets::FPSCounter fps_counter;
    QLabel* fps_label = new QLabel(&main_window);
    main_window.statusBar()->addPermanentWidget(fps_label);

    QObject::connect(&fps_counter, &graphics::widgets::FPSCounter::FpsUpdated,
                     [fps_label](int fps) { fps_label->setText(QString("FPS: %1").arg(fps)); });

    QObject::connect(&timer, &QTimer::timeout, &fps_counter,
                     &graphics::widgets::FPSCounter::FrameRendered);

    main_window.show();

    return app.exec();
}
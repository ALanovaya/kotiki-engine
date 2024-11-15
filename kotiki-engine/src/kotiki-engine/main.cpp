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
        : QGraphicsPixmapItem(pixmap), m_orbitRadius(orbitRadius), m_speed(speed), m_angle(0) {
        setTransformOriginPoint(pixmap.width() / 2.0, pixmap.height() / 2.0);
    }

    void advance(int phase) {
        if (!phase) return;
        m_angle += m_speed;
        setPos(m_orbitRadius * cos(m_angle) - pixmap().width() / 2.0,
               m_orbitRadius * sin(m_angle) - pixmap().height() / 2.0);
    }

private:
    qreal m_orbitRadius;
    qreal m_speed;
    qreal m_angle;
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Two Cats Orbiting");
    mainWindow.resize(800, 600);

    QPixmap pixmap("asserts/textures/grass.png");

    QGraphicsScene* scene = new QGraphicsScene(&mainWindow);
    scene->setSceneRect(-300, -300, 600, 600);
    scene->setBackgroundBrush(QBrush(pixmap));

    graphics::ResizableGraphicsView* view = new graphics::ResizableGraphicsView(scene);
    mainWindow.setCentralWidget(view);

    // Load images
    QPixmap image1("asserts/textures/pushin.png");
    QPixmap image2("asserts/textures/pushin.png");

    // Create two images
    MovingPixmap* imageItem1 = new MovingPixmap(image1, 100, 0.05);
    MovingPixmap* imageItem2 = new MovingPixmap(image2, 200, 0.03);

    scene->addItem(imageItem1);
    scene->addItem(imageItem2);

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    timer.start(10);

    graphics::widgets::FPSCounter fpsCounter;
    QLabel* fpsLabel = new QLabel(&mainWindow);
    mainWindow.statusBar()->addPermanentWidget(fpsLabel);

    QObject::connect(&fpsCounter, &graphics::widgets::FPSCounter::fpsUpdated,
                     [fpsLabel](int fps) { fpsLabel->setText(QString("FPS: %1").arg(fps)); });

    QObject::connect(&timer, &QTimer::timeout, &fpsCounter,
                     &graphics::widgets::FPSCounter::frameRendered);

    mainWindow.show();

    return app.exec();
}
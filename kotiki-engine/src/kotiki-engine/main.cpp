#include <QApplication>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QMainWindow>
#include <QStatusBar>
#include <QTimer>
#include <QWheelEvent>
#include <cmath>

#include "kotiki-engine/graphics/fps_counter.hpp"
#include "kotiki-engine/graphics/view.hpp"

class MovingCircle : public QGraphicsEllipseItem {
public:
    MovingCircle(qreal radius, qreal orbitRadius, qreal speed)
        : m_radius(radius), m_orbitRadius(orbitRadius), m_speed(speed), m_angle(0) {
        setRect(-radius, -radius, radius * 2, radius * 2);
        setBrush(QBrush(Qt::red));
    }

    void advance(int phase) {
        if (!phase) return;
        m_angle += m_speed;
        setPos(m_orbitRadius * cos(m_angle), m_orbitRadius * sin(m_angle));
    }

private:
    qreal m_radius;
    qreal m_orbitRadius;
    qreal m_speed;
    qreal m_angle;
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Two Circles Orbiting");
    mainWindow.resize(800, 600);

    QGraphicsScene* scene = new QGraphicsScene(&mainWindow);
    scene->setSceneRect(-300, -300, 600, 600);

    ResizableGraphicsView* view = new ResizableGraphicsView(scene);
    mainWindow.setCentralWidget(view);

    // Create two circles
    MovingCircle* circle1 = new MovingCircle(20, 100, 0.05);
    MovingCircle* circle2 = new MovingCircle(15, 200, 0.03);

    scene->addItem(circle1);
    scene->addItem(circle2);

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    timer.start(10);

    FPSCounter fpsCounter;
    QLabel* fpsLabel = new QLabel(&mainWindow);
    mainWindow.statusBar()->addPermanentWidget(fpsLabel);

    QObject::connect(&fpsCounter, &FPSCounter::fpsUpdated,
                     [fpsLabel](int fps) { fpsLabel->setText(QString("FPS: %1").arg(fps)); });

    QObject::connect(&timer, &QTimer::timeout, &fpsCounter, &FPSCounter::frameRendered);

    mainWindow.show();

    return app.exec();
}
#include <QApplication>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>
#include <QWheelEvent>

class CustomGraphicsView : public QGraphicsView {
public:
    CustomGraphicsView(QWidget* parent = nullptr) : QGraphicsView(parent) {
        setRenderHint(QPainter::Antialiasing);
        setDragMode(QGraphicsView::ScrollHandDrag);
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        setResizeAnchor(QGraphicsView::AnchorUnderMouse);
    }

protected:
    void wheelEvent(QWheelEvent* event) override {
        double scaleFactor = 1.15;
        if (event->angleDelta().y() > 0) {
            scale(scaleFactor, scaleFactor);
        } else {
            scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        }
    }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Graphics Scene with Circle");
    mainWindow.resize(800, 600);

    QGraphicsScene* scene = new QGraphicsScene(&mainWindow);
    scene->setBackgroundBrush(QColor(100, 150, 255));

    CustomGraphicsView* view = new CustomGraphicsView();
    view->setScene(scene);

    QGraphicsEllipseItem* circle =
            scene->addEllipse(0, 0, 100, 100, QPen(Qt::black), QBrush(Qt::red));

    mainWindow.setCentralWidget(view);

    mainWindow.show();

    return app.exec();
}
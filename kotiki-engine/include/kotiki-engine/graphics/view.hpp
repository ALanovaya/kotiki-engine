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

namespace graphics {
class ResizableGraphicsView : public QGraphicsView {
    Q_OBJECT

public:
    ResizableGraphicsView(QGraphicsScene* scene, QWidget* parent = nullptr);

protected:
    void resizeEvent(QResizeEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    bool is_dragging_;
    QPoint last_mouse_pos_;
};
}  // namespace graphics

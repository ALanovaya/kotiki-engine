#include <QApplication>
#include <QGraphicsEllipseItem>
#include <QGraphicsOpacityEffect>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QMainWindow>
#include <QPropertyAnimation>
#include <QStatusBar>
#include <QTimer>
#include <QWheelEvent>
#include <cmath>

namespace graphics {
class ResizableGraphicsView : public QGraphicsView {
    Q_OBJECT

public:
    ResizableGraphicsView(QGraphicsScene* scene, QWidget* parent = nullptr);
    void ShowNightFilter(bool enable);

protected:
    void resizeEvent(QResizeEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    void UpdateNightFilterSize();

    bool is_dragging_;
    QPoint last_mouse_pos_;
    QGraphicsRectItem* night_filter_;
    int const filter_margin_ = 500;
    QGraphicsOpacityEffect* opacity_effect_;
    QPropertyAnimation* fade_animation_;
    bool is_night_filter_visible_;
};
}  // namespace graphics

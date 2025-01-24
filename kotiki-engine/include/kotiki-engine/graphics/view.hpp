#pragma once

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
// Custom graphics view with advanced interaction and night filter capabilities
class ResizableGraphicsView : public QGraphicsView {
    Q_OBJECT

public:
    // Constructor with scene and optional parent widget
    ResizableGraphicsView(QGraphicsScene* scene, QWidget* parent = nullptr);

    // Toggle night filter overlay
    void ShowNightFilter(bool enable);

protected:
    // Override default event handlers for custom interactions
    void resizeEvent(QResizeEvent* event) override;  // Handles view resizing
    void wheelEvent(QWheelEvent* event) override;    // Custom zoom/scroll behavior

    void mousePressEvent(QMouseEvent* event) override;    // Start dragging
    void mouseMoveEvent(QMouseEvent* event) override;     // Dragging logic
    void mouseReleaseEvent(QMouseEvent* event) override;  // End dragging

private:
    // Resize night filter to match view dimensions
    void UpdateNightFilterSize();

    // Interaction and visual effect tracking
    bool is_dragging_;       // Track if user is dragging view
    QPoint last_mouse_pos_;  // Store last mouse position for dragging

    QGraphicsRectItem* night_filter_;  // Dark overlay for night mode
    int const filter_margin_ = 500;    // Extra margin for filter

    QGraphicsOpacityEffect* opacity_effect_;  // Fade effect for night filter
    QPropertyAnimation* fade_animation_;      // Animate filter opacity
    bool is_night_filter_visible_;            // Night filter state
};
}  // namespace graphics

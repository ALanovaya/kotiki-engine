#include "kotiki-engine/graphics/view.hpp"

namespace graphics {
// Constructor: Initialize graphics view with scene and parent
ResizableGraphicsView::ResizableGraphicsView(QGraphicsScene* scene, QWidget* parent)
    : QGraphicsView(scene, parent), is_dragging_(false) {
    // Set rendering and view behavior for smooth graphics
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorUnderMouse);

    // Disable scrollbars
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setDragMode(QGraphicsView::NoDrag);

    // Create night filter overlay with semi-transparent dark blue color
    night_filter_ = new QGraphicsRectItem();
    night_filter_->setBrush(QBrush(QColor(0, 0, 139, 128)));
    night_filter_->setZValue(2);
    scene->addItem(night_filter_);
    night_filter_->hide();

    // Setup opacity effect for smooth fade animation
    opacity_effect_ = new QGraphicsOpacityEffect();
    night_filter_->setGraphicsEffect(opacity_effect_);

    // Configure fade animation for night filter
    fade_animation_ = new QPropertyAnimation(opacity_effect_, "opacity");
    fade_animation_->setDuration(1000);
    fade_animation_->setStartValue(0.0);
    fade_animation_->setEndValue(1.0);
}

// Update night filter size to match view dimensions
void ResizableGraphicsView::UpdateNightFilterSize() {
    if (night_filter_) {
        // Create an expanded rect to cover view with margins
        QRectF view_rect = mapToScene(viewport()->rect()).boundingRect();
        QRectF expanded_rect(view_rect.x() - filter_margin_, view_rect.y() - filter_margin_,
                             view_rect.width() + 2 * filter_margin_,
                             view_rect.height() + 2 * filter_margin_);
        night_filter_->setRect(expanded_rect);
    }
}

// Handle view resize while maintaining view center and aspect ratio
void ResizableGraphicsView::resizeEvent(QResizeEvent* event) {
    QGraphicsView::resizeEvent(event);

    QPointF center = mapToScene(viewport()->rect().center());
    fitInView(sceneRect(), Qt::KeepAspectRatio);

    QPointF new_center = mapToScene(viewport()->rect().center());
    QPointF delta = center - new_center;
    translate(delta.x(), delta.y());

    UpdateNightFilterSize();
}

// Animate and toggle night filter with fade effect
void ResizableGraphicsView::ShowNightFilter(bool enable) {
    if (night_filter_) {
        UpdateNightFilterSize();

        // Show night filter with forward fade animation
        if (enable && !is_night_filter_visible_) {
            night_filter_->show();
            fade_animation_->setDirection(QPropertyAnimation::Forward);
            fade_animation_->start();
            is_night_filter_visible_ = true;
        }
        // Hide night filter with backward fade animation
        else if (!enable && is_night_filter_visible_) {
            fade_animation_->setDirection(QPropertyAnimation::Backward);
            fade_animation_->start();

            // Hide filter after fade-out animation completes
            QObject::connect(fade_animation_, &QPropertyAnimation::finished, [this]() {
                if (fade_animation_->direction() == QPropertyAnimation::Backward) {
                    night_filter_->hide();
                    is_night_filter_visible_ = false;
                }
            });
        }
    }
}

// Implement zoom functionality with mouse wheel
void ResizableGraphicsView::wheelEvent(QWheelEvent* event) {
    // Calculate scale factor based on wheel direction
    double const scale_factor = (event->angleDelta().y() > 0) ? 1.15 : 1.0 / 1.15;

    // Map mouse position to scene coordinates for precise zooming
    QPoint global_pos = event->globalPosition().toPoint();
    QPoint widget_pos = mapFromGlobal(global_pos);
    QPointF scene_pos = mapToScene(widget_pos);

    scale(scale_factor, scale_factor);

    // Adjust view to keep mouse position stable during zoom
    QPointF new_pos = mapToScene(widget_pos);
    QPointF delta = new_pos - scene_pos;
    translate(delta.x(), delta.y());

    event->accept();
}

// Handle mouse press for dragging
void ResizableGraphicsView::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        is_dragging_ = true;
        last_mouse_pos_ = event->pos();
        setCursor(Qt::ClosedHandCursor);
        event->accept();
    } else {
        QGraphicsView::mousePressEvent(event);
    }
}

// Implement view dragging
void ResizableGraphicsView::mouseMoveEvent(QMouseEvent* event) {
    if (is_dragging_) {
        QPointF delta = mapToScene(last_mouse_pos_) - mapToScene(event->pos());
        QRectF new_scene_rect = sceneRect();
        new_scene_rect.translate(delta.x(), delta.y());
        setSceneRect(new_scene_rect);
        last_mouse_pos_ = event->pos();
        event->accept();
        viewport()->update();
    } else {
        QGraphicsView::mouseMoveEvent(event);
    }
}

// Reset cursor and dragging state on mouse release
void ResizableGraphicsView::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton && is_dragging_) {
        is_dragging_ = false;
        setCursor(Qt::ArrowCursor);
        event->accept();
    } else {
        QGraphicsView::mouseReleaseEvent(event);
    }
}
}  // namespace graphics
#include "kotiki-engine/graphics/view.hpp"

namespace graphics {
ResizableGraphicsView::ResizableGraphicsView(QGraphicsScene* scene, QWidget* parent)
    : QGraphicsView(scene, parent), is_dragging_(false) {
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorUnderMouse);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setDragMode(QGraphicsView::NoDrag);
}

void ResizableGraphicsView::resizeEvent(QResizeEvent* event) {
    QGraphicsView::resizeEvent(event);

    QPointF center = mapToScene(viewport()->rect().center());
    fitInView(sceneRect(), Qt::KeepAspectRatio);

    QPointF new_center = mapToScene(viewport()->rect().center());
    QPointF delta = center - new_center;
    translate(delta.x(), delta.y());
}

void ResizableGraphicsView::wheelEvent(QWheelEvent* event) {
    double const scale_factor = (event->angleDelta().y() > 0) ? 1.15 : 1.0 / 1.15;
    QPoint global_pos = event->globalPosition().toPoint();
    QPoint widget_pos = mapFromGlobal(global_pos);
    QPointF scene_pos = mapToScene(widget_pos);

    scale(scale_factor, scale_factor);

    QPointF new_pos = mapToScene(widget_pos);
    QPointF delta = new_pos - scene_pos;
    translate(delta.x(), delta.y());

    event->accept();
}

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
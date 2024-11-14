#include "kotiki-engine/graphics/view.hpp"

ResizableGraphicsView::ResizableGraphicsView(QGraphicsScene* scene, QWidget* parent)
    : QGraphicsView(scene, parent), isDragging(false) {
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

    QPointF newCenter = mapToScene(viewport()->rect().center());
    QPointF delta = center - newCenter;
    translate(delta.x(), delta.y());
}

void ResizableGraphicsView::wheelEvent(QWheelEvent* event) {
    double const scaleFactor = (event->angleDelta().y() > 0) ? 1.15 : 1.0 / 1.15;
    QPoint globalPos = event->globalPosition().toPoint();
    QPoint widgetPos = mapFromGlobal(globalPos);
    QPointF scenePos = mapToScene(widgetPos);

    scale(scaleFactor, scaleFactor);

    QPointF newPos = mapToScene(widgetPos);
    QPointF delta = newPos - scenePos;
    translate(delta.x(), delta.y());

    event->accept();
}

void ResizableGraphicsView::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        isDragging = true;
        lastMousePos = event->pos();
        setCursor(Qt::ClosedHandCursor);
        event->accept();
    } else {
        QGraphicsView::mousePressEvent(event);
    }
}

void ResizableGraphicsView::mouseMoveEvent(QMouseEvent* event) {
    if (isDragging) {
        QPointF delta = mapToScene(lastMousePos) - mapToScene(event->pos());
        QRectF newSceneRect = sceneRect();
        newSceneRect.translate(delta.x(), delta.y());
        setSceneRect(newSceneRect);
        lastMousePos = event->pos();
        event->accept();
        viewport()->update();
    } else {
        QGraphicsView::mouseMoveEvent(event);
    }
}

void ResizableGraphicsView::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton && isDragging) {
        isDragging = false;
        setCursor(Qt::ArrowCursor);
        event->accept();
    } else {
        QGraphicsView::mouseReleaseEvent(event);
    }
}

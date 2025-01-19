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

    night_filter_ = new QGraphicsRectItem();
    night_filter_->setBrush(QBrush(QColor(0, 0, 139, 128)));
    night_filter_->setZValue(2);
    scene->addItem(night_filter_);
    night_filter_->hide();

    opacity_effect_ = new QGraphicsOpacityEffect();
    night_filter_->setGraphicsEffect(opacity_effect_);

    fade_animation_ = new QPropertyAnimation(opacity_effect_, "opacity");
    fade_animation_->setDuration(1000);
    fade_animation_->setStartValue(0.0);
    fade_animation_->setEndValue(1.0);
}

void ResizableGraphicsView::UpdateNightFilterSize() {
    if (night_filter_) {
        QRectF view_rect = mapToScene(viewport()->rect()).boundingRect();
        QRectF expanded_rect(
            view_rect.x() - filter_margin_,
            view_rect.y() - filter_margin_,
            view_rect.width() + 2 * filter_margin_,
            view_rect.height() + 2 * filter_margin_
        );
        night_filter_->setRect(expanded_rect);
    }
}

void ResizableGraphicsView::resizeEvent(QResizeEvent* event) {
    QGraphicsView::resizeEvent(event);

    QPointF center = mapToScene(viewport()->rect().center());
    fitInView(sceneRect(), Qt::KeepAspectRatio);

    QPointF new_center = mapToScene(viewport()->rect().center());
    QPointF delta = center - new_center;
    translate(delta.x(), delta.y());

    UpdateNightFilterSize();
}

void ResizableGraphicsView::ShowNightFilter(bool enable)  {
    if (night_filter_) {
        UpdateNightFilterSize();

        if (enable && !is_night_filter_visible_) {
            night_filter_->show();

            fade_animation_->setDirection(QPropertyAnimation::Forward);
            fade_animation_->start();

            is_night_filter_visible_ = true; 
        } else if (!enable && is_night_filter_visible_) {
            fade_animation_->setDirection(QPropertyAnimation::Backward);
            fade_animation_->start();

            QObject::connect(fade_animation_, &QPropertyAnimation::finished, [this]() {
                if (fade_animation_->direction() == QPropertyAnimation::Backward) {
                    night_filter_->hide();
                    is_night_filter_visible_ = false;
                }
            });
        }
    }
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
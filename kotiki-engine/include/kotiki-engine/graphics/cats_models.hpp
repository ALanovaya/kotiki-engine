#pragma once

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>
#include <QStatusBar>
#include <QTimer>

namespace graphics::models {
class Cats : public QGraphicsPixmapItem {
public:
    Cats(QPixmap const& pixmap, qreal x, qreal y)
        : QGraphicsPixmapItem(pixmap), target_x_(x), target_y_(y) {
        setPos(x, y);
    }

    void MoveTo(double x, double y) {
        target_x_ = x;
        target_y_ = y;
    }

    void UpdatePosition() {
        qreal current_x = pos().x();
        qreal current_y = pos().y();

        qreal dx = target_x_ - current_x;
        qreal dy = target_y_ - current_y;

        qreal step_x = dx / 30;
        qreal step_y = dy / 30;

        qreal new_x = current_x + step_x;
        qreal new_y = current_y + step_y;

        setPos(new_x, new_y);
    }

    void UpdatePixmap(QPixmap const& pixmap) {
        setPixmap(pixmap);
    }

private:
    qreal target_x_;
    qreal target_y_;
};

}  // namespace graphics::models
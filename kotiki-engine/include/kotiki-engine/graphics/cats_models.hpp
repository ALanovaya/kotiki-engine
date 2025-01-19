#pragma once

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>
#include <QStatusBar>
#include <QTimer>

namespace graphics::models {
class Cats : public QGraphicsPixmapItem {
public:
    // Initialize cat with image and position
    Cats(QPixmap const& pixmap, qreal x, qreal y)
        : QGraphicsPixmapItem(pixmap), target_x_(x), target_y_(y) {
        setPos(x, y);
    }

    // Set movement target and teleportation mode
    void MoveTo(double x, double y, bool teleport_flag) {
        target_x_ = x;
        target_y_ = y;
        to_teleport_ = teleport_flag;
    }

    // Smooth movement or instant teleport
    void UpdatePosition() {
        if (to_teleport_) {
            setPos(target_x_, target_y_);
            return;
        }

        qreal current_x = pos().x();
        qreal current_y = pos().y();

        qreal dx = target_x_ - current_x;
        qreal dy = target_y_ - current_y;

        // Divide movement into 30 steps for smooth animation
        qreal step_x = dx / 30;
        qreal step_y = dy / 30;

        qreal new_x = current_x + step_x;
        qreal new_y = current_y + step_y;

        setPos(new_x, new_y);
    }

    // Update cat's image
    void UpdatePixmap(QPixmap const& pixmap) {
        setPixmap(pixmap);
    }

private:
    qreal target_x_;  // Target position x-coordinate
    qreal target_y_;  // Target position y-coordinate

    bool to_teleport_ = false;  // Teleportation flag: if cat is near border then teleport
};

}  // namespace graphics::models
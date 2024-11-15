#pragma once

#include <QObject>
#include <QTimer>

namespace graphics::widgets {
class FPSCounter : public QObject {
    Q_OBJECT
public:
    explicit FPSCounter(QObject* parent = nullptr);
    void frameRendered();
    virtual ~FPSCounter(){};

private slots:
    void updateFPS();

signals:
    void fpsUpdated(int fps);

private:
    QTimer m_timer;
    int m_frameCount;
};
}  // namespace graphics::widgets
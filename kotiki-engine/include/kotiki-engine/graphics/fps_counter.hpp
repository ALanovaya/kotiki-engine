#pragma once

#include <QObject>
#include <QTimer>

namespace graphics::widgets {
class FPSCounter : public QObject {
    Q_OBJECT
public:
    explicit FPSCounter(QObject* parent = nullptr);
    void FrameRendered();
    virtual ~FPSCounter(){};

private slots:
    void UpdateFps();

signals:
    void FpsUpdated(int fps);

private:
    QTimer timer_;
    int frameCount_;
};
}  // namespace graphics::widgets
#pragma once

#include <QObject>
#include <QTimer>

namespace graphics::widgets {
class FPSCounter : public QObject {
    Q_OBJECT
public:
    explicit FPSCounter(QObject* parent = nullptr);
    void FrameRendered();

    int GetCurrentFps() const;

private slots:
    void UpdateFps();

signals:
    void FpsUpdated(int fps);

private:
    QTimer timer_;
    int frame_count_;
    int current_fps_;
};
}  // namespace graphics::widgets
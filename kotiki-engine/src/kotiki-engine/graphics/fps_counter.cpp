#include "kotiki-engine/graphics/fps_counter.hpp"

namespace graphics::widgets {
// Initialize FPS counter with 1-second timer
FPSCounter::FPSCounter(QObject* parent) : QObject(parent), frame_count_(0) {
    connect(&timer_, &QTimer::timeout, this, &FPSCounter::UpdateFps);
    timer_.start(1000);
}

// Track each rendered frame
void FPSCounter::FrameRendered() {
    frame_count_++;
}

// Calculate FPS every second
void FPSCounter::UpdateFps() {
    current_fps_ = frame_count_;
    emit FpsUpdated(frame_count_);
    frame_count_ = 0;
}

int FPSCounter::GetCurrentFps() const {
    return current_fps_;
}
}  // namespace graphics::widgets
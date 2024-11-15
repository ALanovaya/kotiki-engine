#include "kotiki-engine/graphics/fps_counter.hpp"

namespace graphics::widgets {
FPSCounter::FPSCounter(QObject* parent) : QObject(parent), frame_count_(0) {
    connect(&timer_, &QTimer::timeout, this, &FPSCounter::UpdateFps);
    timer_.start(1000);
}

void FPSCounter::FrameRendered() {
    frame_count_++;
}

void FPSCounter::UpdateFps() {
    emit FpsUpdated(frame_count_);
    frame_count_ = 0;
}
}  // namespace graphics::widgets
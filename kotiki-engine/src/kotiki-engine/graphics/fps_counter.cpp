#include "kotiki-engine/graphics/fps_counter.hpp"

namespace graphics::widgets {
FPSCounter::FPSCounter(QObject* parent) : QObject(parent), frameCount_(0) {
    connect(&timer_, &QTimer::timeout, this, &FPSCounter::UpdateFps);
    timer_.start(1000);
}

void FPSCounter::FrameRendered() {
    frameCount_++;
}

void FPSCounter::UpdateFps() {
    emit FpsUpdated(frameCount_);
    frameCount_ = 0;
}
}  // namespace graphics::widgets
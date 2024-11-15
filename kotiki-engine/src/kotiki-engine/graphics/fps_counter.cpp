#include "kotiki-engine/graphics/fps_counter.hpp"

graphics::widgets::FPSCounter::FPSCounter(QObject* parent) : QObject(parent), frameCount_(0) {
    connect(&timer_, &QTimer::timeout, this, &FPSCounter::UpdateFps);
    timer_.start(1000);
}

void graphics::widgets::FPSCounter::FrameRendered() {
    frameCount_++;
}

void graphics::widgets::FPSCounter::UpdateFps() {
    emit FpsUpdated(frameCount_);
    frameCount_ = 0;
}

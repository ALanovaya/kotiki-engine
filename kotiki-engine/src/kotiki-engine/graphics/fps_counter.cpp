#include "kotiki-engine/graphics/fps_counter.hpp"

graphics::widgets::FPSCounter::FPSCounter(QObject* parent) : QObject(parent), m_frameCount(0) {
    connect(&m_timer, &QTimer::timeout, this, &FPSCounter::updateFPS);
    m_timer.start(1000);
}

void graphics::widgets::FPSCounter::frameRendered() {
    m_frameCount++;
}

void graphics::widgets::FPSCounter::updateFPS() {
    emit fpsUpdated(m_frameCount);
    m_frameCount = 0;
}

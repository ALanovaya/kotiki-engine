#include "kotiki-engine/graphics/fps_counter.hpp"

FPSCounter::FPSCounter(QObject* parent) : QObject(parent), m_frameCount(0) {
    connect(&m_timer, &QTimer::timeout, this, &FPSCounter::updateFPS);
    m_timer.start(1000);
}

void FPSCounter::frameRendered() {
    m_frameCount++;
}

void FPSCounter::updateFPS() {
    emit fpsUpdated(m_frameCount);
    m_frameCount = 0;
}

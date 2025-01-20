#pragma once

#include <QApplication>
#include <QComboBox>
#include <QDockWidget>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMessageBox>
#include <QPen>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>
#include <kotiki-engine/utils/types.h>

#include "kotiki-engine/core/algorithms/algorithms.hpp"
#include "kotiki-engine/core/metrics/metrics.hpp"
#include "kotiki-engine/core/movers/movers.hpp"

namespace graphics::widgets::settings {
class SettingsWidget : public QDockWidget {
    Q_OBJECT

public:
    // Constructor with simulation configuration parameters
    SettingsWidget(QWidget* parent, int cats_count, int width, int height, int max_moving_cats,
                   coord_t R0 = 200.0, coord_t R1 = 500.0);

signals:
    // Signals to notify parameter changes
    void NumberOfCatsChanged(int new_count);
    void SceneDimensionsChanged(int new_width, int new_height);
    void MetricChanged(std::unique_ptr<algo::Metric>& new_metric);
    void R0Changed(coord_t new_R0);
    void R1Changed(coord_t new_R1);
    void MaxMovingCatsChanged(int new_max_moving_cats);
    void TauChanged(int new_tau);
    void MoverChanged(std::unique_ptr<mover::Mover>& new_mover);

private slots:
    void OnApply();

private:
    // UI elements for simulation configuration
    // Number of cats in the simulation
    QSpinBox* spinBox_;

    // Width and height of the simulation scene
    QSpinBox* width_spinBox_;
    QSpinBox* height_spinBox_;

    // Dropdown for selecting metric calculation method
    QComboBox* metricComboBox_;

    // Probability-related spin box and label
    QDoubleSpinBox* pSpinBox_;
    QLabel* p_label_;

    // Radius parameters for simulation angriness of cats
    QDoubleSpinBox* R0_spinBox_;
    QDoubleSpinBox* R1_spinBox_;

    // Maximum number of moving cats and time step
    QSpinBox* max_moving_cats_spinBox_;
    QSpinBox* tau_spinBox_;

    // Dropdown for selecting movement algorithm
    QComboBox* moverComboBox_;

    // Step size range for movement
    QSpinBox* min_step_spinBox_;
    QSpinBox* max_step_spinBox_;

    // Custom movement expressions for x and y coordinates
    QLineEdit* x_expression_edit_;
    QLineEdit* y_expression_edit_;

    // Labels for step size and expression inputs
    QLabel* min_step_label_;
    QLabel* max_step_label_;
    QLabel* x_expression_label_;
    QLabel* y_expression_label_;
};
}  // namespace graphics::widgets::settings
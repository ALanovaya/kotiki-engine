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
    SettingsWidget(QWidget* parent, int cats_count, int width, int height, int max_moving_cats,
                   coord_t R0 = 200.0, coord_t R1 = 500.0);

signals:
    void NumberOfCatsChanged(int new_count);
    void SceneDimensionsChanged(int new_width, int new_height);
    void MetricChanged(std::unique_ptr<algo::Metric>& new_metric);
    void R0Changed(coord_t new_R0);
    void R1Changed(coord_t new_R1);
    void MaxMovingCatsChanged(int new_max_moving_cats);
    void TauChanged(int new_tau);
    void MoverChanged(std::unique_ptr<mover::Mover>& new_mover);

private slots:

    void OnApply() {
        emit NumberOfCatsChanged(spinBox_->value());
        emit SceneDimensionsChanged(width_spinBox_->value(), height_spinBox_->value());
        emit R0Changed(R0_spinBox_->value());
        emit R1Changed(R1_spinBox_->value());
        emit MaxMovingCatsChanged(max_moving_cats_spinBox_->value());
        emit TauChanged(tau_spinBox_->value());

        std::unique_ptr<algo::Metric> new_metric;
        switch (metricComboBox_->currentIndex()) {
            case 0:  // Euclidean
                new_metric = std::make_unique<algo::EuclideanMetric>();
                break;
            case 1:  // Minkowski
                new_metric = std::make_unique<algo::MinkowskiMetric>(pSpinBox_->value());
                break;
            case 2:  // Manhattan
                new_metric = std::make_unique<algo::ManhattanMetric>();
                break;
            case 3:  // Chebyshev
                new_metric = std::make_unique<algo::ChebyshevMetric>();
                break;
        }
        emit MetricChanged(new_metric);

        std::unique_ptr<mover::Mover> new_mover;
        if (moverComboBox_->currentIndex() == 0) {  // Random
            new_mover = std::make_unique<mover::RandomMover>(min_step_spinBox_->value(),
                                                             max_step_spinBox_->value());
        } else {  // Trajectory
            std::string x_expression = x_expression_edit_->text().toStdString();
            std::string y_expression = y_expression_edit_->text().toStdString();

            if (x_expression.empty() || y_expression.empty()) {
                QMessageBox::warning(this, "Input Error", "Expression is invalid.");
                return;
            }

            try {
                new_mover = std::make_unique<mover::TrajectoryMover>(
                        x_expression, y_expression, tau_spinBox_->value() / 1000.0);
            } catch (std::exception const& e) {
                QMessageBox::warning(this, "Input Error", e.what());
                return;
            }
        }
        emit MoverChanged(new_mover);
    }

private:
    QSpinBox* spinBox_;
    QSpinBox* width_spinBox_;
    QSpinBox* height_spinBox_;
    QComboBox* metricComboBox_;
    QDoubleSpinBox* pSpinBox_;
    QLabel* p_label_;
    QDoubleSpinBox* R0_spinBox_;
    QDoubleSpinBox* R1_spinBox_;
    QSpinBox* max_moving_cats_spinBox_;
    QSpinBox* tau_spinBox_;
    QComboBox* moverComboBox_;
    QSpinBox* min_step_spinBox_;
    QSpinBox* max_step_spinBox_;
    QLineEdit* x_expression_edit_;
    QLineEdit* y_expression_edit_;
    QLabel* min_step_label_;
    QLabel* max_step_label_;
    QLabel* x_expression_label_;
    QLabel* y_expression_label_;
};
}  // namespace graphics::widgets::settings
#pragma once

#include <QApplication>
#include <QComboBox>
#include <QDockWidget>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPen>
#include <QPushButton>
#include <QMessageBox>
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
                   coord_t R0 = 200.0, coord_t R1 = 500.0)
        : QDockWidget("Settings", parent) {
        QWidget* widget = new QWidget(this);
        QVBoxLayout* layout = new QVBoxLayout(widget);

        QLabel* label = new QLabel("Number of Cats:", this);
        spinBox_ = new QSpinBox(this);
        spinBox_->setRange(1, 50000);
        spinBox_->setValue(cats_count);

        QLabel* width_label = new QLabel("Scene Width:", this);
        width_spinBox_ = new QSpinBox(this);
        width_spinBox_->setRange(100, 40000);
        width_spinBox_->setValue(width);

        QLabel* height_label = new QLabel("Scene Height:", this);
        height_spinBox_ = new QSpinBox(this);
        height_spinBox_->setRange(100, 30000);
        height_spinBox_->setValue(height);

        QLabel* metric_label = new QLabel("Select Metric:", this);
        metricComboBox_ = new QComboBox(this);
        metricComboBox_->addItem("Euclidean");
        metricComboBox_->addItem("Minkowski");
        metricComboBox_->addItem("Manhattan");
        metricComboBox_->addItem("Chebyshev");

        // Поле ввода для параметра p
        p_label_ = new QLabel("Minkowski p:", this);
        pSpinBox_ = new QDoubleSpinBox(this);
        pSpinBox_->setRange(0.0, 10);
        pSpinBox_->setValue(0.5);
        pSpinBox_->setVisible(false);
        p_label_->setVisible(false);

        QLabel* r0_label = new QLabel("R0:", this);
        R0_spinBox_ = new QDoubleSpinBox(this);
        R0_spinBox_->setRange(0.1, 2000.0);
        R0_spinBox_->setValue(R0);

        QLabel* r1_label = new QLabel("R1:", this);
        R1_spinBox_ = new QDoubleSpinBox(this);
        R1_spinBox_->setRange(0.1, 2000.0);
        R1_spinBox_->setValue(R1);

        QLabel* max_moving_cats_label = new QLabel("Max Moving Cats:", this);
        max_moving_cats_spinBox_ = new QSpinBox(this);
        max_moving_cats_spinBox_->setRange(1, 10000);
        max_moving_cats_spinBox_->setValue(max_moving_cats);

        QLabel* tau_label = new QLabel("Tau (ms):", this);
        tau_spinBox_ = new QSpinBox(this);
        tau_spinBox_->setRange(500, 10000);
        tau_spinBox_->setValue(500);

        QLabel* mover_label = new QLabel("Select Mover Type:", this);
        moverComboBox_ = new QComboBox(this);
        moverComboBox_->addItem("Random");
        moverComboBox_->addItem("Trajectory");

        min_step_label_ = new QLabel("Min Step:", this);
        min_step_spinBox_ = new QSpinBox(this);
        min_step_spinBox_->setRange(1, 1000);
        min_step_spinBox_->setValue(10);

        max_step_label_ = new QLabel("Max Step:", this);
        max_step_spinBox_ = new QSpinBox(this);
        max_step_spinBox_->setRange(1, 1000);
        max_step_spinBox_->setValue(100);

        x_expression_label_ = new QLabel("X Expression:", this);
        x_expression_edit_ = new QLineEdit(this);
        x_expression_edit_->setPlaceholderText("Enter X expression");

        y_expression_label_ = new QLabel("Y Expression:", this);
        y_expression_edit_ = new QLineEdit(this);
        y_expression_edit_->setPlaceholderText("Enter Y expression");

        x_expression_label_->setVisible(false);
        x_expression_edit_->setVisible(false);
        y_expression_label_->setVisible(false);
        y_expression_edit_->setVisible(false);

        QPushButton* apply_button = new QPushButton("Apply", this);

        layout->addWidget(label);
        layout->addWidget(spinBox_);
        layout->addWidget(width_label);
        layout->addWidget(width_spinBox_);
        layout->addWidget(height_label);
        layout->addWidget(height_spinBox_);
        layout->addWidget(metric_label);
        layout->addWidget(metricComboBox_);
        layout->addWidget(p_label_);
        layout->addWidget(pSpinBox_);
        layout->addWidget(r0_label);
        layout->addWidget(R0_spinBox_);
        layout->addWidget(r1_label);
        layout->addWidget(R1_spinBox_);
        layout->addWidget(max_moving_cats_label);
        layout->addWidget(max_moving_cats_spinBox_);
        layout->addWidget(tau_label);
        layout->addWidget(tau_spinBox_);
        layout->addWidget(mover_label);
        layout->addWidget(moverComboBox_);
        layout->addWidget(min_step_label_);
        layout->addWidget(min_step_spinBox_);
        layout->addWidget(max_step_label_);
        layout->addWidget(max_step_spinBox_);
        layout->addWidget(x_expression_label_);
        layout->addWidget(x_expression_edit_);
        layout->addWidget(y_expression_label_);
        layout->addWidget(y_expression_edit_);

        layout->addWidget(apply_button);
        setWidget(widget);

        connect(apply_button, &QPushButton::clicked, this, &SettingsWidget::OnApply);

        connect(metricComboBox_, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [&]() {
            std::unique_ptr<algo::Metric> new_metric;
            switch (metricComboBox_->currentIndex()) {
                case 0:  // Euclidean
                    new_metric = std::make_unique<algo::EuclideanMetric>();
                    pSpinBox_->setVisible(false);
                    p_label_->setVisible(false);
                    break;
                case 1:  // Minkowski
                    pSpinBox_->setVisible(true);
                    p_label_->setVisible(true);
                    new_metric = std::make_unique<algo::MinkowskiMetric>(pSpinBox_->value());
                    break;
                case 2:  // Manhattan
                    new_metric = std::make_unique<algo::ManhattanMetric>();
                    pSpinBox_->setVisible(false);
                    p_label_->setVisible(false);
                    break;
                case 3:  // Chebyshev
                    new_metric = std::make_unique<algo::ChebyshevMetric>();
                    pSpinBox_->setVisible(false);
                    p_label_->setVisible(false);
                    break;
            }
            emit MetricChanged(new_metric);
        });

        connect(moverComboBox_, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [&]() {
            bool is_random = moverComboBox_->currentIndex() == 0;
            min_step_label_->setVisible(is_random);
            min_step_spinBox_->setVisible(is_random);
            max_step_label_->setVisible(is_random);
            max_step_spinBox_->setVisible(is_random);
            x_expression_label_->setVisible(!is_random);
            x_expression_edit_->setVisible(!is_random);
            y_expression_label_->setVisible(!is_random);
            y_expression_edit_->setVisible(!is_random);
        });
    }

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

            new_mover = std::make_unique<mover::TrajectoryMover>(
                    x_expression,
                    y_expression, tau_spinBox_->value() / 1000.0);
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
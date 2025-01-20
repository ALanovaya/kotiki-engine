#include "kotiki-engine/graphics/settings.hpp"

namespace graphics::widgets::settings {
SettingsWidget::SettingsWidget(QWidget* parent, int cats_count, int width, int height,
                               int max_moving_cats, coord_t R0, coord_t R1)
    : QDockWidget("Settings", parent) {
    QWidget* widget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(widget);

    // Number of cats input
    QLabel* label = new QLabel("Number of Cats:", this);
    spinBox_ = new QSpinBox(this);
    spinBox_->setRange(1, 50000);
    spinBox_->setValue(cats_count);

    // Scene width input
    QLabel* width_label = new QLabel("Scene Width:", this);
    width_spinBox_ = new QSpinBox(this);
    width_spinBox_->setRange(100, 40000);
    width_spinBox_->setValue(width);

    // Scene height input
    QLabel* height_label = new QLabel("Scene Height:", this);
    height_spinBox_ = new QSpinBox(this);
    height_spinBox_->setRange(100, 30000);
    height_spinBox_->setValue(height);

    // Metric selection dropdown
    QLabel* metric_label = new QLabel("Select Metric:", this);
    metricComboBox_ = new QComboBox(this);
    metricComboBox_->addItem("Euclidean");
    metricComboBox_->addItem("Minkowski");
    metricComboBox_->addItem("Manhattan");
    metricComboBox_->addItem("Chebyshev");

    // Minkowski p-parameter input
    p_label_ = new QLabel("Minkowski p:", this);
    pSpinBox_ = new QDoubleSpinBox(this);
    pSpinBox_->setRange(0.0, 10);
    pSpinBox_->setValue(0.5);
    pSpinBox_->setVisible(false);
    p_label_->setVisible(false);

    // R0 parameter input
    QLabel* r0_label = new QLabel("R0:", this);
    R0_spinBox_ = new QDoubleSpinBox(this);
    R0_spinBox_->setRange(0.1, static_cast<double>(height + width));
    R0_spinBox_->setValue(R0);

    // R1 parameter input
    QLabel* r1_label = new QLabel("R1:", this);
    R1_spinBox_ = new QDoubleSpinBox(this);
    R1_spinBox_->setRange(0.1, static_cast<double>(height + width));
    R1_spinBox_->setValue(R1);

    // Maximum moving cats input
    QLabel* max_moving_cats_label = new QLabel("Max Moving Cats:", this);
    max_moving_cats_spinBox_ = new QSpinBox(this);
    max_moving_cats_spinBox_->setRange(1, 10000);
    max_moving_cats_spinBox_->setValue(max_moving_cats);

    // Tau (time step) input
    QLabel* tau_label = new QLabel("Tau (ms):", this);
    tau_spinBox_ = new QSpinBox(this);
    tau_spinBox_->setRange(500, 10000);
    tau_spinBox_->setValue(500);

    // Mover type selection
    QLabel* mover_label = new QLabel("Select Mover Type:", this);
    moverComboBox_ = new QComboBox(this);
    moverComboBox_->addItem("Random");
    moverComboBox_->addItem("Trajectory");

    // Minimum step for random movement
    min_step_label_ = new QLabel("Min Step:", this);
    min_step_spinBox_ = new QSpinBox(this);
    min_step_spinBox_->setRange(1, 1000);
    min_step_spinBox_->setValue(10);

    // Maximum step for random movement
    max_step_label_ = new QLabel("Max Step:", this);
    max_step_spinBox_ = new QSpinBox(this);
    max_step_spinBox_->setRange(1, 1000);
    max_step_spinBox_->setValue(100);

    // X-coordinate expression for trajectory movement
    x_expression_label_ = new QLabel("X Expression:", this);
    x_expression_edit_ = new QLineEdit(this);
    x_expression_edit_->setPlaceholderText("Enter X expression");

    // Y-coordinate expression for trajectory movement
    y_expression_label_ = new QLabel("Y Expression:", this);
    y_expression_edit_ = new QLineEdit(this);
    y_expression_edit_->setPlaceholderText("Enter Y expression");

    // Initially hide trajectory-related inputs
    x_expression_label_->setVisible(false);
    x_expression_edit_->setVisible(false);
    y_expression_label_->setVisible(false);
    y_expression_edit_->setVisible(false);

    // Apply button
    QPushButton* apply_button = new QPushButton("Apply", this);

    // Add widgets to layout
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

    // Connect apply button
    connect(apply_button, &QPushButton::clicked, this, &SettingsWidget::OnApply);

    // Metric selection handler
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

    // Mover type handler
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

// Apply configurations and emit corresponding signals
void SettingsWidget::OnApply() {
    emit NumberOfCatsChanged(spinBox_->value());
    emit SceneDimensionsChanged(width_spinBox_->value(), height_spinBox_->value());
    emit R0Changed(R0_spinBox_->value());
    emit R1Changed(R1_spinBox_->value());
    emit MaxMovingCatsChanged(max_moving_cats_spinBox_->value());
    emit TauChanged(tau_spinBox_->value());

    // Create metric based on current selection
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

    // Create mover based on selected type
    std::unique_ptr<mover::Mover> new_mover;
    if (moverComboBox_->currentIndex() == 0) {  // Random mover
        new_mover = std::make_unique<mover::RandomMover>(min_step_spinBox_->value(),
                                                         max_step_spinBox_->value());
    } else {  // Trajectory mover
        try {
            std::string x_expression = x_expression_edit_->text().toStdString();
            std::string y_expression = y_expression_edit_->text().toStdString();

            // Validate and create trajectory mover
            if (x_expression.empty() || y_expression.empty()) {
                QMessageBox::warning(this, "Input Error", "Expression is invalid.");
                return;
            }

            new_mover = std::make_unique<mover::TrajectoryMover>(x_expression, y_expression,
                                                                 tau_spinBox_->value() / 1000.0);
        } catch (std::exception const& e) {
            QMessageBox::warning(this, "Input Error", e.what());
            return;
        }
    }
    emit MoverChanged(new_mover);
}
}  // namespace graphics::widgets::settings
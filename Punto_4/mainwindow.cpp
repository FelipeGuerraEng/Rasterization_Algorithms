#include "mainwindow.h"
#include "bresenham_circle.h"
#include "ddaline.h"
#include "basic_line_rasterization.h"
#include "bresenhamline.h"
#include "midpointcircle.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QApplication>
#include <QScreen>

MainWindow::MainWindow() {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    QHBoxLayout *glWidgetsLayout = new QHBoxLayout();

    QHBoxLayout *viewLayout = new QHBoxLayout;
    viewLayout->addWidget(&openglWidget);
    viewLayout->addWidget(&openglWidget3D);
    mainLayout.addLayout(viewLayout);

    centralWidget->setLayout(&mainLayout);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    this->setGeometry(x, y, this->width(), this->height());

    widthInput.setRange(300, 700);
    widthInput.setValue(300);
    heightInput.setRange(300, 700);
    heightInput.setValue(300);

    opengl2DTitle.setText("2D");
    opengl3DTitle.setText("3D");

    layout->addWidget(new QLabel("Width of coordinate space. Range: 300-700"));
    layout->addWidget(&widthInput);
    layout->addWidget(new QLabel("Height of coordinate space. Range: 300-700:"));
    layout->addWidget(&heightInput);

    applyButton.setText("Apply");
    layout->addWidget(&applyButton);

    layout->addWidget(new QLabel("Algorithm:"));
    layout->addWidget(&algorithmSelector);

    algorithmSelector.addItem("Bresenham Circle");
    algorithmSelector.addItem("DDA Line");
    algorithmSelector.addItem("Basic Line");
    algorithmSelector.addItem("Bresenham Line");
    algorithmSelector.addItem("Midpoint Circle");

    centerXInput.setRange(0, 80);
    centerYInput.setRange(0, 80);
    radiusInput.setRange(10, 60);
    x2Input.setRange(0, 80);
    y2Input.setRange(0, 80);

    layout->addWidget(&centerXLabel);
    layout->addWidget(&centerXInput);
    layout->addWidget(&centerYLabel);
    layout->addWidget(&centerYInput);
    layout->addWidget(&radiusLabel);
    layout->addWidget(&radiusInput);
    layout->addWidget(&x2Label);
    layout->addWidget(&x2Input);
    layout->addWidget(&y2Label);
    layout->addWidget(&y2Input);



    QPushButton *runButton = new QPushButton("RUN");
    layout->addWidget(runButton);

    connect(runButton, &QPushButton::clicked, this, &MainWindow::onRunButtonClicked);
    connect(&algorithmSelector, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onAlgorithmChanged);

    connect(&widthInput, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::adjustMainWindowSize);
    connect(&heightInput, QOverload<int>::of(&QSpinBox::valueChanged),this, &MainWindow::adjustMainWindowSize);

    connect(&applyButton, &QPushButton::clicked, this, &MainWindow::updateVisualizationSize);

    glWidgetsLayout->addWidget(&opengl2DTitle);
    glWidgetsLayout->addWidget(&openglWidget);
    glWidgetsLayout->addWidget(&opengl3DTitle);
    glWidgetsLayout->addWidget(&openglWidget3D);
    layout->addLayout(glWidgetsLayout);

    setCentralWidget(centralWidget);

    updateInterface();
}

MainWindow::~MainWindow() {
}

void MainWindow::onAlgorithmChanged(int index) {
    updateInterface();
}
void MainWindow::updateVisualizationSize() {
    int width = widthInput.value();
    int height = heightInput.value();

    openglWidget.setFixedSize(width, height);
    openglWidget3D.setFixedSize(width, height);

    widthInput.setDisabled(true);
    heightInput.setDisabled(true);
}

void MainWindow::adjustMainWindowSize() {
    this->adjustSize();
}
void MainWindow::updateInterface() {
    int index = algorithmSelector.currentIndex();

    bool isBresenhamCircleAlgorithm = index == 0; // Bresenham Circle
    bool isDDALineAlgorithm = index == 1; // DDA Line
    bool isBasicLineAlgorithm = index == 2; // Algoritmo básico de rasterización de líneas
    bool isBresenhamLineAlgorithm = index == 3; // Bresenham para líneas
    bool isMidPointCircleAlgorithm = index == 4; // Mid Point Circle Algorithm

    bool isLineAlgorithm = isDDALineAlgorithm || isBasicLineAlgorithm || isBresenhamLineAlgorithm;
    bool isCircleAlgorithm = isBresenhamCircleAlgorithm || isMidPointCircleAlgorithm;

    radiusLabel.setText("Radius. Range 10-60:");
    x2Label.setText("X2. Range 0-80:");
    y2Label.setText("Y2. Range 0-80:");
    centerXLabel.setText(isCircleAlgorithm ? "Center X. Range 0-80:" : "X1. Range 0-80:");
    centerYLabel.setText(isCircleAlgorithm ? "Center Y. Range 0-80:" : "Y1. Range 0-80:");
    radiusLabel.setVisible(isCircleAlgorithm);
    radiusInput.setVisible(isCircleAlgorithm);
    x2Label.setVisible(isLineAlgorithm);
    x2Input.setVisible(isLineAlgorithm);
    y2Label.setVisible(isLineAlgorithm);
    y2Input.setVisible(isLineAlgorithm);
}
void MainWindow::onRunButtonClicked() {
    int index = algorithmSelector.currentIndex();
    std::vector<std::tuple<int, int>> points;

    switch (index) {
        case 0: { // Bresenham Circle
            int centerX = centerXInput.value();
            int centerY = centerYInput.value();
            int radius = radiusInput.value();

            BresenhamCircle circle(centerX, centerY, radius);
            points = circle.calculatePoints();
            break;
        }
        case 1: { // DDA Line
            int x1 = centerXInput.value();
            int y1 = centerYInput.value();
            int x2 = x2Input.value();
            int y2 = y2Input.value();

            DDALine line(x1, y1, x2, y2);
            points = line.calculatePoints();
            break;
        }
        case 2: { // Basic Line
            int x1 = centerXInput.value();
            int y1 = centerYInput.value();
            int x2 = x2Input.value();
            int y2 = y2Input.value();

            BasicLineRasterization line(x1, y1, x2, y2);
            points = line.calculatePoints();
            break;
        }
        case 3: { // Bresenham Line
            int x1 = centerXInput.value();
            int y1 = centerYInput.value();
            int x2 = x2Input.value();
            int y2 = y2Input.value();

            BresenhamLine line(x1, y1, x2, y2);
            points = line.calculatePoints();
            break;
        }
        case 4: { // Midpoint Circle
            int centerX = centerXInput.value();
            int centerY = centerYInput.value();
            int radius = radiusInput.value();

            MidpointCircle circle(centerX, centerY, radius);
            points = circle.calculatePoints();
            break;
        }
        default:
            break;
    }

    openglWidget.setPoints(points);
    openglWidget3D.setPoints(points);
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include "openglwidget.h"
#include "openglwidget3d.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private slots:
    void onRunButtonClicked();
    void onAlgorithmChanged(int index);
    void updateVisualizationSize();
    void adjustMainWindowSize();

private:
    QComboBox algorithmSelector;
    QLabel centerXLabel;
    QSpinBox centerXInput;
    QLabel centerYLabel;
    QSpinBox centerYInput;
    QLabel radiusLabel;
    QSpinBox radiusInput;
    QLabel x2Label;
    QSpinBox x2Input;
    QLabel y2Label;
    QSpinBox y2Input;
    QPushButton runButton;
    QSpinBox widthInput;
    QSpinBox heightInput;
    QVBoxLayout mainLayout;
    QPushButton applyButton;
    QLabel opengl2DTitle;
    QLabel opengl3DTitle;
    OpenGLWidget openglWidget;
    OpenGLWidget3D openglWidget3D;

    void updateInterface();
};

#endif // MAINWINDOW_H

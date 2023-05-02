#ifndef OPENGLWIDGET3D_H
#define OPENGLWIDGET3D_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QKeyEvent>
#include <vector>
#include <tuple>

class OpenGLWidget3D : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    OpenGLWidget3D(QWidget *parent = nullptr);

    void setPoints(const std::vector<std::tuple<int, int>> &newPoints);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    void drawAxes();
    void drawCircle();

    QMatrix4x4 modelViewMatrix;
    std::vector<std::tuple<int, int>> points;
    float xRot = 0.0f;
    float yRot = 0.0f;
};

#endif // OPENGLWIDGET3D_H

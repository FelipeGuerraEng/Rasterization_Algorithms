#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <vector>
#include <tuple>

class OpenGLWidget : public QOpenGLWidget {
    Q_OBJECT

public:
    OpenGLWidget(QWidget *parent = nullptr);

    void setPoints(const std::vector<std::tuple<int, int>> &newPoints);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    std::vector<std::tuple<int, int>> points;
};

#endif // OPENGLWIDGET_H

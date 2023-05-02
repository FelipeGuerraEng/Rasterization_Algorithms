#include "openglwidget.h"
#include <GL/glut.h>

OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent) {
    setMinimumSize(300, 300);
}

void OpenGLWidget::setPoints(const std::vector<std::tuple<int, int>> &newPoints) {
    points = newPoints;
    update();
}

void OpenGLWidget::initializeGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void OpenGLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void OpenGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_POINTS);
    for (const auto &[x, y] : points) {
        glVertex2i(x, y);
    }
    glEnd();

    glFlush();
}

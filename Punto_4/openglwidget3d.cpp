#include "openglwidget3d.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QKeyEvent>
#include <cmath>

OpenGLWidget3D::OpenGLWidget3D(QWidget *parent)
    : QOpenGLWidget(parent) {
    setMinimumSize(300, 300);
    setFocusPolicy(Qt::StrongFocus); // Habilita el foco de entrada para recibir eventos de teclado
}

void OpenGLWidget3D::setPoints(const std::vector<std::tuple<int, int>> &newPoints) {
    points = newPoints;
    update();
}

void OpenGLWidget3D::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar) {
    const GLdouble pi = 3.1415926535897932384626433832795;
    GLdouble fW, fH;

    fH = tan(fovY / 360 * pi) * zNear;
    fW = fH * aspect;

    glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}

void OpenGLWidget3D::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    perspectiveGL(60.0, (float)w / h, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

void lookAt(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ,
            GLdouble centerX, GLdouble centerY, GLdouble centerZ,
            GLdouble upX, GLdouble upY, GLdouble upZ) {
    GLdouble forward[3], side[3], up[3];
    GLfloat matrix[16];

    forward[0] = centerX - eyeX;
    forward[1] = centerY - eyeY;
    forward[2] = centerZ - eyeZ;

    up[0] = upX;
    up[1] = upY;
    up[2] = upZ;

    GLfloat norm = sqrt(forward[0] * forward[0] + forward[1] * forward[1] + forward[2] * forward[2]);
    forward[0] /= norm;
    forward[1] /= norm;
    forward[2] /= norm;

    side[0] = forward[1] * up[2] - forward[2] * up[1];
    side[1] = forward[2] * up[0] - forward[0] * up[2];
    side[2] = forward[0] * up[1] - forward[1] * up[0];

    norm = sqrt(side[0] * side[0] + side[1] * side[1] + side[2] * side[2]);
    side[0] /= norm;
    side[1] /= norm;
    side[2] /= norm;

    up[0] = side[1] * forward[2] - side[2] * forward[1];
    up[1] = side[2] * forward[0] - side[0] * forward[2];
    up[2] = side[0] * forward[1] - side[1] * forward[0];

    matrix[0] = side[0];
    matrix[1] = up[0];
    matrix[2] = -forward[0];
    matrix[3] = 0.0;

    matrix[4] = side[1];
    matrix[5] = up[1];
    matrix[6] = -forward[1];
    matrix[7] = 0.0;

    matrix[8] = side[2];
    matrix[9] = up[2];
    matrix[10] = -forward[2];
    matrix[11] = 0.0;

    matrix[12] = 0.0;
    matrix[13] = 0.0;
    matrix[14] = 0.0;
    matrix[15] = 1.0;

    glMultMatrixf(matrix);
    glTranslated(-eyeX, -eyeY, -eyeZ);
}

void OpenGLWidget3D::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glLoadIdentity();
    lookAt(1, 1, 1, 0, 0, 0, 0, 1, 0);

    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);

    drawAxes();
    drawCircle();
}

void OpenGLWidget3D::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_W:
            xRot += 5;
            break;
        case Qt::Key_S:
            xRot -= 5;
            break;
        case Qt::Key_A:
            yRot += 5;
            break;
        case Qt::Key_D:
            yRot -= 5;
            break;
       default:
           QOpenGLWidget::keyPressEvent(event);
           return;
   }
   update();
}

void OpenGLWidget3D::drawAxes() {
   glBegin(GL_LINES);
   // Eje X (Rojo)
   glColor3f(1.0f, 0.0f, 0.0f);
   glVertex3f(0.0f, 0.0f, 0.0f);
   glVertex3f(1.0f, 0.0f, 0.0f);
   // Eje Y (Verde)
   glColor3f(0.0f, 1.0f, 0.0f);
   glVertex3f(0.0f, 0.0f, 0.0f);
   glVertex3f(0.0f, 1.0f, 0.0f);
   // Eje Z (Azul)
   glColor3f(0.0f, 0.0f, 1.0f);
   glVertex3f(0.0f, 0.0f, 0.0f);
   glVertex3f(0.0f, 0.0f, 1.0f);
   glEnd();
}

void OpenGLWidget3D::drawCircle() {
   glColor3f(0.0f, 0.0f, 0.0f);
   glBegin(GL_LINE_LOOP);
   for (const auto &[x, y] : points) {
       glVertex3f(x / 100.0f, y / 100.0f, 0.0f);
   }
   glEnd();
}

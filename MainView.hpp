#pragma once
#include <GL/glew.h>

#include <QOpenGLWidget>
#include <QTimer>

#include "Scene.hpp"

class MainView : public QOpenGLWidget
{
    Q_OBJECT

private:
    Scene scene;
    double alpha;
    double beta;
    double distance;
    QPoint lastMousePosition;

public:
    MainView(QWidget *parent = 0 );

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

public slots:
    void setCone();
};

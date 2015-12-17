#include "MainView.hpp"
#include "Scene.hpp"
#include <QMouseEvent>
#include <QWheelEvent>

MainView::MainView(QWidget *parent) :
    QOpenGLWidget(parent),
    scene()
{
    this->setFocusPolicy(Qt::ClickFocus);

    alpha = 0.0; //25;
    beta = 0.0; //-25;
    distance = 2.5;

    this->setMinimumSize(800,600);
}

void MainView::initializeGL()
{
    glewExperimental = GL_TRUE;
    GLenum result = glewInit();
    if(result != GLEW_OK)
        throw std::runtime_error("Error initializing GLEW");

    glClearColor(0.0f,0.0f,0.0f,1.0f);

    Cone cone;

    scene.create(cone);
}

void MainView::paintGL() {
    scene.render(alpha,beta,distance);
}

void MainView::resizeGL(int w, int h ) {
    scene.resize(w,h);
}

void MainView::setCone()
{

}

void MainView::mousePressEvent(QMouseEvent *event)
{
    lastMousePosition = event->pos();

    event->accept();
}

void MainView::mouseMoveEvent(QMouseEvent *event)
{
    int deltaX = event->x() - lastMousePosition.x();
    int deltaY = event->y() - lastMousePosition.y();

    if (event->buttons() & Qt::LeftButton) {
        alpha -= deltaX;
        while (alpha < 0) {
            alpha += 360;
        }
        while (alpha >= 360) {
            alpha -= 360;
        }

        beta -= deltaY;
        while (beta < 0) {
            beta += 360;
        }
        while (beta >= 360) {
            beta -= 360;
        }
    }

    lastMousePosition = event->pos();

    event->accept();
    update();
}

void MainView::wheelEvent(QWheelEvent *event)
{
    int delta = event->delta();

    if (event->orientation() == Qt::Vertical) {
        if (delta < 0) {
            distance *= 1.1;
        } else if (delta > 0) {
            distance *= 0.9;
        }
    }

    event->accept();
    update();
}

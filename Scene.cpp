#include "Scene.hpp"
#include "Cone.hpp"

#include <QVector3D>
#include <QVector4D>
#include <QMatrix3x3>

Scene::Scene():
    m_width(800), m_height(600)
{
}

void Scene::create(const Surface& surface)
{
    compileAndLinkShader();

    glEnable(GL_DEPTH_TEST);

    int tessLev = 2;
    int numPatch = 100;
    m_surfacePatch.create(surface,tessLev, numPatch);

    m_program.enableAttributeArray(0);
    m_program.setAttributeBuffer(0, GL_FLOAT, 0, 3);

    m_program.setUniformValue("TessLevel", tessLev);
    m_program.setUniformValue("LineWidth", 0.5f);
    m_program.setUniformValue("LineColor", QVector4D(0.007, 0.450, 0.552, 1.0));
    m_program.setUniformValue("LightPosition", QVector4D(100.0f,0.0f,0.0f,1.0f));
    m_program.setUniformValue("LightIntensity", QVector3D(1.0, 0.0, 0.0));
    m_program.setUniformValue("Kd", QVector3D(1.0f, 1.0f, 1.0f));
    m_program.setUniformValue("Ks", QVector3D(1.0f, 1.0f, 1.0f));
    m_program.setUniformValue("Ka", QVector3D(1.0f, 1.0f, 1.0f));
}


void Scene::render(float alpha, float beta, float distance)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    setMatrices(alpha,beta,distance);
    m_surfacePatch.render();
    glFinish();
}

void Scene::setMatrices(float alpha, float beta, float distance)
{
    m_model.setToIdentity();
    m_model.translate(QVector3D(0.0f,-1.5f,0.0f));
    m_model.rotate(static_cast<float>(M_PI_2), QVector3D(1.0f,0.0f,0.0f));

    QMatrix4x4 m1, m2;
    m1.rotate(alpha, QVector3D(0.0f,1.0f,0.0f));
    m2.rotate(beta,QVector3D(1.0f,0.0f,0.0f));
    auto cameraTransformation = m2*m1;

    QVector4D cameraPosition = cameraTransformation * QVector4D(0, 0, distance, 1);
    QVector4D cameraUpDirection = cameraTransformation * QVector4D(0, 1, 0, 1);
    QVector3D v1(cameraPosition);
    QVector3D v2(cameraUpDirection);

    m_view.setToIdentity();
    m_view.lookAt(v1, QVector3D(0.0f,0.0f,0.0f), v2);

    auto mv = m_view * m_model;

    m_program.setUniformValue("ModelViewMatrix", mv);
    m_program.setUniformValue("NormalMatrix", mv.normalMatrix());
    m_program.setUniformValue("MVP", m_projection * mv);
    m_program.setUniformValue("ViewportMatrix", m_viewport);
}

void Scene::resize(int w, int h)
{
    glViewport(0,0,w,h);
    m_width = w;
    m_height = h;

    float w2 = w / 2.0f;
    float h2 = h / 2.0f;
    m_viewport = QMatrix4x4(w2,0.0f,0.0f,0.0f,
                          0.0f,h2,0.0f,0.0f,
                          0.0f,0.0f,1.0f,0.0f,
                          w2+0, h2+0, 0.0f, 1.0f);
    m_projection.setToIdentity();
    m_projection.perspective(40.0f, (float)w/h, 0.3f, 10000.0f);
}

void Scene::compileAndLinkShader()
{
    if(!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, "shader/vertex.vert") ||
       !m_program.addShaderFromSourceFile(QOpenGLShader::Geometry, "shader/geometry.geom") ||
       !m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, "shader/fragment.frag") ||
       !m_program.addShaderFromSourceFile(QOpenGLShader::TessellationEvaluation, "shader/tess_evaluation.tes") ||
       !m_program.addShaderFromSourceFile(QOpenGLShader::TessellationControl, "shader/tess_control.tes") ||
       !m_program.link() ||
       !m_program.bind())
        throw std::runtime_error(m_program.log().toStdString());
}

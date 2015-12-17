#pragma once
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <QOpenGLShaderProgram>
#include "SurfacePatch.hpp"
#include "Cone.hpp"

#include <QMatrix4x4>

class Scene
{
public:
    Scene();

    void create(const Surface &surface);
    void render(float alpha, float beta, float distance);
    void resize(int, int);
private:
    QOpenGLShaderProgram m_program;
    int m_width, m_height;

    SurfacePatch m_surfacePatch;

    QMatrix4x4 m_model, m_view, m_viewport, m_projection;

    void setMatrices(float alpha, float beta, float distance);
    void compileAndLinkShader();
};

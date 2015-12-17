#pragma once
#include "Cone.hpp"
#include <GL/glew.h>

#include <QOpenGLBuffer>

class SurfacePatch
{
public:
    SurfacePatch();

    void create(const Surface &s, int level, int num_patch);
    void render();

private:
    int m_tesselationLevel, m_numberOfPatches, m_numberOfVertices;
    QOpenGLBuffer m_buffer;

    std::vector<QVector3D> generatePatches(const Surface &surface);
};

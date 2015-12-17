#include "SurfacePatch.hpp"
#include "Cone.hpp"

#include <GL/gl.h>
#include <vector>


SurfacePatch::SurfacePatch():
    m_buffer(QOpenGLBuffer::VertexBuffer)
{    

}

void SurfacePatch::create(const Surface& s, int level, int num_patch)
{
    m_tesselationLevel = level;
    m_numberOfPatches = num_patch;

    auto vertices = generatePatches(s);

    m_numberOfVertices = vertices.size();

    m_buffer.create();
    m_buffer.bind();
    m_buffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_buffer.allocate(vertices.data(), vertices.size()*sizeof(QVector3D));
}

std::vector<QVector3D> SurfacePatch::generatePatches(const Surface& surface)
{
    float lu = surface.GetLeftLimitU();
    float uu = surface.GetRightLimitU();

    float lv = surface.GetLeftLimitV();
    float uv = surface.GetRightLimitV();

    float stepu = (uu-lu)/m_numberOfPatches;
    float stepv = (uv-lv)/m_numberOfPatches;

    float stepuu = stepu/m_tesselationLevel;
    float stepvv = stepv/m_tesselationLevel;

    std::vector<QVector3D> toReturn;

    for (int i=0; i<m_numberOfPatches; ++i) {
        float uglobal = lu + i*stepu;
        for (int j=0; j<m_numberOfPatches; ++j) {
            float vglobal = lv + j*stepv;
            for (int k=0; k<m_tesselationLevel+1; ++k) {
                float ulocal = uglobal + k*stepuu;
                for (int l=0; l<m_tesselationLevel+1; ++l) {
                    float vlocal = vglobal + l*stepvv;
                    QVector3D pt(surface(ulocal,vlocal));
                    QVector3D vn(surface.Normal(ulocal,vlocal));
                    toReturn.push_back(pt);
                    toReturn.push_back(vn);
                }
            }
        }
    }
    return toReturn;
}


void SurfacePatch::render() {
    glPatchParameteri(GL_PATCH_VERTICES, 2*std::pow(m_tesselationLevel+1,2));

    m_buffer.bind();

    glDrawArrays(GL_PATCHES, 0, m_numberOfVertices);
    m_buffer.release();
}

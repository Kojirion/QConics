#include "Cone.hpp"

Cone::Cone():
    h(120.f),
    r(40.f)
{

}

QVector3D Cone::operator()(float u, float v) const
{
    float angle = v*M_PI/180.f;

    return QVector3D(((h - u) / h) * r * std::cos(angle),
                   h - u,
                   ((h - u) / h) * r * std::sin(angle));
}

QVector3D Cone::DeriveU(float, float v) const
{
    float angle = v*M_PI/180.f;

    return QVector3D((-1/h)*r*std::cos(angle),
                   -1,
                   (-1/h)*r*std::sin(angle));
}

QVector3D Cone::DeriveV(float u, float v) const
{
    float angle = v*M_PI/180.f;

    return QVector3D(-((h - u) / h) * r *std::sin(angle),
                   0.f,
                   ((h - u) / h) * r * std::cos(angle));
}

QVector3D Cone::Normal(float u, float v) const
{
    auto crs = QVector3D::crossProduct(DeriveU(u,v), DeriveV(u,v));

    return crs.normalized();
}

float Cone::GetLeftLimitU() const
{
    return 0;
}

float Cone::GetRightLimitU() const
{
    return 240.f;
}

float Cone::GetLeftLimitV() const
{
    return 0;
}

float Cone::GetRightLimitV() const
{
    return 360;
}

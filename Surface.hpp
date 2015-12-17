#pragma once
#include <QVector3D>

class Surface {
public:
    virtual QVector3D operator()(float, float) const = 0;
    virtual QVector3D DeriveU(float, float) const = 0;
    virtual QVector3D DeriveV(float, float) const = 0;
    virtual QVector3D Normal(float, float) const = 0;
    virtual float GetLeftLimitU() const = 0;
    virtual float GetRightLimitU() const = 0;
    virtual float GetLeftLimitV() const = 0;
    virtual float GetRightLimitV() const = 0;
};

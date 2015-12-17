#pragma once
#include "Surface.hpp"

class Cone : public Surface {
public:
    Cone();
    virtual QVector3D operator()(float u, float v) const override;
    virtual QVector3D DeriveU(float u,float v) const override;
    virtual QVector3D DeriveV(float u,float v) const override;
    virtual QVector3D Normal(float u, float v) const override;
    virtual float GetLeftLimitU() const override;
    virtual float GetRightLimitU() const override;
    virtual float GetLeftLimitV() const override;
    virtual float GetRightLimitV() const override;

private:
    float h, r;
};

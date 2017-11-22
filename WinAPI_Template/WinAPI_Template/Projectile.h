#pragma once
#include "SpritesObject.h"
class Projectile : public SpritesObject
{
private:
    float       m_fGenTime;
public:
    Projectile();
    ~Projectile();

    void Start();
    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    void SetGenTime(float GenTime) { m_fGenTime = GenTime; }
};


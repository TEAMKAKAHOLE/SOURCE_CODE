#pragma once
#include "SpritesObject.h"
class Projectile : public SpritesObject
{
private:
    float       m_fGenTime;
    float       m_fExistTime;
public:
    Projectile();
    ~Projectile();

    void Start();
    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    void SetGenTime(float GenTime) { m_fGenTime = GenTime; }
    void SetExistTime(float ExistTime) { m_fExistTime = ExistTime; }
};


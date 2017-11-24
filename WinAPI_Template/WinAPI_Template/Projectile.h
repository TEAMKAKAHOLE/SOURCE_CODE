#pragma once
#include "SpritesObject.h"
class Projectile : public SpritesObject
{
private:
    float       m_fActivateTime;
    float       m_fGenTime;
    float       m_fExistTime;

    int         m_nDamage;
public:
    Projectile();
    ~Projectile();

    void Start();
    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    int GetDamage() { return m_nDamage; }
    void SetDamage(int Damage) { m_nDamage = Damage; }
    void SetGenTime(float GenTime) { m_fGenTime = GenTime; }
    void SetExistTime(float ExistTime) { m_fExistTime = ExistTime; }
};


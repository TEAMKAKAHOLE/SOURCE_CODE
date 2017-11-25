#pragma once
#include "SpritesObject.h"
class Projectile : public SpritesObject
{
private:
    float       m_fActivateTime;
    float       m_fGenTime;
    float       m_fExistTime;

    int         m_nDamage;

    bool        m_isActivate;
public:
    Projectile();
    ~Projectile();

    void Start();
    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    int GetDamage() { return m_nDamage; }
    void SetDamage(int Damage) { m_nDamage = Damage; }
    void SetActiveTime(float ActTime) { m_fActivateTime = ActTime; }
    void SetGenTime(float GenTime) { m_fGenTime = GenTime; }
    void SetExistTime(float ExistTime) { m_fExistTime = ExistTime; }
    float GetExistTime() { return m_fExistTime; }
    float GetGenTime() { return m_fGenTime; }
    float GetActiveTime() { return m_fActivateTime; }

    bool IsActivate() { return m_isActivate; }
    void Activate() { m_isActivate = true; }
    void Deactivate() { m_isActivate = false; }
};


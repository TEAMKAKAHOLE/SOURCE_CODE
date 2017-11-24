#pragma once
#include "SpritesObject.h"
#include "Projectile.h"

#define MAX_HP_BOSS     100

class Chief : public SpritesObject
{
private:
    ImageObject*    m_imgTerrainBuffer;
    SpritesObject*  m_sprBullet;
    bool    m_isHostile;
    float   m_fBulletCooltime;
    float   m_fNovaCooltime;

    int     m_nPhase;

public:
    Chief();
    ~Chief();

    void Start();
    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    void SetTerrainBuffer(ImageObject* ImgTerrain) { m_imgTerrainBuffer = ImgTerrain; }

    bool IsHostile() { return m_isHostile; }
    void SetHostile();
    void MakeBullet(vector<Projectile>& VecBullets, UnitPos Pos);

    void Phase(vector<Projectile>& VecBullets, UnitPos Pos);
    void PhaseUpdate();
};
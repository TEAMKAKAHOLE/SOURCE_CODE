#pragma once
#include "SpritesObject.h"
#include "Projectile.h"

class Chief : public SpritesObject
{
private:
    ImageObject*    m_imgTerrainBuffer;
    SpritesObject*  m_sprBullet;
    bool    m_isHostile;
    float   m_fBulletCooltime;

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
};
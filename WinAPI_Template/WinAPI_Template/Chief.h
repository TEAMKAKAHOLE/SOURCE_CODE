#pragma once
#include "SpritesObject.h"
#include "Projectile.h"

#define MAX_HP_BOSS     100

class Chief : public SpritesObject
{
private:
    ImageObject*    m_imgTerrainBuffer;
    SpritesObject*  m_sprBullet;

    bool        m_isHostile;
    float       m_fNormalAtkCooldown;
    float       m_fBarrageCooldown;

    int         m_nPhase;
    vector<Projectile>*     m_pVecBullets;
    UnitPos*    m_pPlayerPos;

public:
    Chief();
    ~Chief();

    void Start();
    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    void SetTerrainBuffer(ImageObject* ImgTerrain) { m_imgTerrainBuffer = ImgTerrain; }
    void SetVecBullets(vector<Projectile>* VecBullets) { m_pVecBullets = VecBullets; }
    void SetPlayerPos(UnitPos* Pos) { m_pPlayerPos = Pos; }

    bool IsHostile() { return m_isHostile; }
    void SetHostile();

    void PhaseAction();
    void PhaseUpdate();

    void NormalAttack(float Cooltime);
    void BarrageAttack(float Cooltime);
};
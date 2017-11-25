#pragma once
#include "SpritesObject.h"
#include "Projectile.h"

#define PLAYER_RUN_MAX_FRAME 6
#define PLAYER_ATK_MAX_FRAME 5

#define DIR_LEFT    4
#define DIR_UP      6
#define DIR_RIGHT   2
#define DIR_DOWN    0

class Player : public SpritesObject
{
private:
    ImageObject*    m_imgTerrainBuffer;
    ImageObject*    m_imgUiBuffer;
    ImageObject*    m_imgHud;
    SpritesObject*  m_sprHudLife;
    SpritesObject*  m_sprHudNumber;
    SpritesObject*  m_sprMoonSlash;
    SpritesObject*  m_sprSwordIcon;

    GridVector      m_playerHeadDir;
    E_PLAYER_STATUS m_playerStatus;
    E_WEAPON_TYPE   m_weaponType;
    int             m_currFrameY;

    int             m_nAtkDamage;
    int             m_nHealPotion;

    float           m_fMeleeAtkCooltime;
    float           m_fRangeAtkCooltime;

    bool            m_isStun;
    bool            m_isMoveImpair;
public:
    Player();
    ~Player();

    void Start();
    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    void SetTerrainBuffer(ImageObject* ImgTerrain) { m_imgTerrainBuffer = ImgTerrain; }
    void SetUiBuffer(ImageObject* ImgUi) { m_imgUiBuffer = ImgUi; }

    void PlayerController();

    void SetIdle();

    int GetAtkDamage() { return m_nAtkDamage; }
    int GetHealPotion() { return m_nHealPotion; }

    void UseHealPotion();
    void SumHealPotion(int Amount = 1);

    void CheckCollision();
    void MakeBullet(vector<Projectile>& VecBullets, UnitPos Pos);
    Projectile MakeSword();
    Projectile MakeArrow();

    void PlayerValidate();

    void TestController();
};
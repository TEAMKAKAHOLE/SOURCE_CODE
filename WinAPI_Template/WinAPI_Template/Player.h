#pragma once
#include "SpritesObject.h"

#define PLAYER_RUN_MAX_FRAME 6
#define PLAYER_ATK_MAX_FRAME 5

#define DIR_LEFT    4
#define DIR_UP      6
#define DIR_RIGHT   2
#define DIR_DOWN    0

#define ATK_SWORD_BOX {50, 50}

class Player : public SpritesObject
{
private:
    ImageObject*    m_imgTerrainBuffer;

    E_PLAYER_STATUS m_playerStatus;
    E_WEAPON_TYPE   m_weaponType;
    int             m_currFrameY;
    RECT            m_rtAtkArea;

    int             m_nHealPotion;

public:
    Player();
    ~Player();

    void Start();
    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    void SetTerrainBuffer(ImageObject* ImgTerrain) { m_imgTerrainBuffer = ImgTerrain; }
    void PlayerController();

    void SetIdle();
    void SetAtkArea();

    RECT GetAtkArea() { return m_rtAtkArea; }
    int GetHealPotion() { return m_nHealPotion; }

    void CheckCollision();
};


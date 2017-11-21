#pragma once
#include "SpritesObject.h"

#define PLAYER_RUN_MAX_FRAME 6
#define PLAYER_ATK_MAX_FRAME 5

class Player : public SpritesObject
{
private:
    E_PLAYER_STATUS m_playerStatus;
    E_WEAPON_TYPE   m_weaponType;
    int             m_currFrameY;

public:
    Player();
    ~Player();

    void Start();
    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    void PlayerController();
};


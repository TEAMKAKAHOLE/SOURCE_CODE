#include "stdafx.h"
#include "Player.h"


Player::Player()
{
    m_playerStatus = PLAYER_IDLE;
    m_weaponType = WEAPON_SWORD;
}

Player::~Player()
{
}

void Player::Start()
{

}

void Player::Update()
{
    PlayerController();

    switch (m_playerStatus)
    {
    case PLAYER_IDLE:
    {
        SetFrameX(0);
        isAnimate = false;
        break;
    }
    case PLAYER_RUN:
    {
        frameDelay = 6;
        isAnimate = true;
        break;
    }
    case PLAYER_ATTACK:
    {
        frameDelay = 3;
        maxFrameX = PLAYER_ATK_MAX_FRAME;
        frameY = m_currFrameY + 1;
        isAnimate = true;
        break;
    }
    }

    SpritesObject::Update();
}

void Player::Render(HDC hdc)
{
    SpritesObject::Render(hdc);
}

void Player::PlayerController()
{
    UnitSpeed speed = { 0.0f, 0.0f };
    if (g_pKeyManager->isStayKeyDown(VK_LEFT))
    {
        m_currFrameY = 4;
        speed.x -= 5.0f;
        m_playerStatus = PLAYER_RUN;
    }
    else if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
    {
        m_currFrameY = 2;
        speed.x += 5.0f;
        m_playerStatus = PLAYER_RUN;
    }
    else if (g_pKeyManager->isStayKeyDown(VK_UP))
    {
        m_currFrameY = 6;
        speed.y -= 5.0f;
        m_playerStatus = PLAYER_RUN;
    }
    else if (g_pKeyManager->isStayKeyDown(VK_DOWN))
    {
        m_currFrameY = 0;
        speed.y += 5.0f;
        m_playerStatus = PLAYER_RUN;
    }
    else if (g_pKeyManager->isStayKeyDown(VK_SPACE))
    {
        if (m_playerStatus == PLAYER_RUN)
            frameX = 0;

        m_playerStatus = PLAYER_ATTACK;
        isAnimate = true;
    }
    else
    {
        m_playerStatus = PLAYER_IDLE;
    }

    frameY = m_currFrameY;
    m_dSpeed = speed;
}
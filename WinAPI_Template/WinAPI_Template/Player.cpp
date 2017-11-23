#include "stdafx.h"
#include "Player.h"


Player::Player()
{
    m_playerStatus = PLAYER_IDLE;
    m_weaponType = WEAPON_SWORD;
    m_rtAtkArea = { 0, 0, 0, 0 };
    m_nLife = 5;
    m_currFrameY = 0;
    m_nHealPotion = 0;
    m_nAtkDamage = 1;
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
        SetIdle();
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
        SetAtkArea();
        frameDelay = 3;
        maxFrameX = PLAYER_ATK_MAX_FRAME;
        frameY = m_currFrameY + 1;
        isAnimate = true;
        break;
    }
    }
    CheckCollision();
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
        m_currFrameY = DIR_LEFT;
        speed.x -= 5.0f;
        m_playerStatus = PLAYER_RUN;
    }
    else if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
    {
        m_currFrameY = DIR_RIGHT;
        speed.x += 5.0f;
        m_playerStatus = PLAYER_RUN;
    }
    else if (g_pKeyManager->isStayKeyDown(VK_UP))
    {
        m_currFrameY = DIR_UP;
        speed.y -= 5.0f;
        m_playerStatus = PLAYER_RUN;
    }
    else if (g_pKeyManager->isStayKeyDown(VK_DOWN))
    {
        m_currFrameY = DIR_DOWN;
        speed.y += 5.0f;
        m_playerStatus = PLAYER_RUN;
    }
    else if (g_pKeyManager->isStayKeyDown(VK_SPACE))
    {
        if (m_playerStatus == PLAYER_RUN)
            frameX = 0;

        m_playerStatus = PLAYER_ATTACK;
    }
    else
    {
        m_playerStatus = PLAYER_IDLE;
    }

    if (g_pKeyManager->isOnceKeyDown('1'))
        UseHealPotion();

    frameY = m_currFrameY;
    m_dSpeed = speed;
}

void Player::SetIdle()
{
    SetFrameX(0);
    m_rtAtkArea = { 0, 0, 0, 0 };
    isAnimate = false;
}

void Player::SetAtkArea()
{
    UnitPos atkAreaPos = m_dPos;
    switch (m_currFrameY)
    {
    case DIR_LEFT:
    {
        atkAreaPos.x -= 40;
        break;
    }
    case DIR_UP:
    {
        atkAreaPos.y -= 40;
        break;
    }
    case DIR_RIGHT:
    {
        atkAreaPos.x += 40;
        break;
    }
    case DIR_DOWN:
    {
        atkAreaPos.y += 40;
        break;
    }
    }

    m_rtAtkArea = g_pDrawHelper->MakeRect(atkAreaPos, ATK_SWORD_BOX);
}

void Player::UseHealPotion()
{
    if (m_nHealPotion > 0)
    {
        --m_nHealPotion;
        ++m_nLife;
    }
}

void Player::SumHealPotion(int Amount)
{
    m_nHealPotion += Amount;
}

void Player::CheckCollision()
{
    UnitPos ProbePos = m_dPos;
    ProbePos.x += m_dSpeed.x;
    ProbePos.y += m_dSpeed.y;
    if (g_pPixelManager->CheckPixelMagenta(m_imgTerrainBuffer, ProbePos))
        m_dSpeed = { 0.0f, 0.0f };
}
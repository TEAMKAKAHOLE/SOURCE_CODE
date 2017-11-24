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
    json playerData = g_pFileManager->JsonFind("player");
    m_nLife = playerData["player"]["hp"];
    m_nHealPotion = playerData["player"]["potion"];
    g_pFileManager->JsonUpdate("player", playerData);

    m_imgHud = g_pImgManager->FindImage("hud");
    m_sprHudNumber = new SpritesObject;
    m_sprHudNumber->SetBodyImg(g_pImgManager->FindImage("hud-number"));
    m_sprHudNumber->SetupForSprites(10, 1);
    m_sprHudLife = new SpritesObject;
    m_sprHudLife->SetBodyImg(g_pImgManager->FindImage("hud-life"));
    m_sprHudLife->SetupForSprites(3, 1);
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
    //  ui render
    m_imgHud->FastRender(m_imgUiBuffer->GetMemDC(), 0, 0);
    //  life
    int marginX = 180;
    int marginY = 25;
    for (int i = 0; i < GetLife(); i++)
    {
        m_sprHudLife->GetBodyImg()->SpritesRender(m_imgUiBuffer->GetMemDC()
            , marginX + i * 10, marginY
            , 7, 7
            , 0, 0
            , 255.0f);
    }

    //  number
    m_sprHudNumber->GetBodyImg()->SpritesRender(m_imgUiBuffer->GetMemDC()
        , { 85, 28 }
        , { 7, 7 }
        , GetHealPotion()
        , 255.0f);
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

void Player::MakeBullet(vector<Projectile>& VecBullets, UnitPos Pos)
{
    if (m_fMeleeAtkCooltime < g_pTimerManager->GetWorldTime())
    {
        if (m_playerStatus == PLAYER_ATTACK)
        {
            Projectile genBullet;
            genBullet.SetTagName("player");
            genBullet.SetBodySize({ 100, 100 });
            genBullet.SetHBoxMargin({ 0, 0, 0, 0 });
            genBullet.SetBodySpeed({ 0.0f, 0.0f });
            genBullet.SetGenTime(g_pTimerManager->GetWorldTime());
            genBullet.SetExistTime(0.3f);
            genBullet.SetBodyPos(m_dPos);
            genBullet.SetBodyImg(NULL);
            VecBullets.push_back(genBullet);

            m_fMeleeAtkCooltime = g_pTimerManager->GetWorldTime() + 0.4f;
        }
    }
}
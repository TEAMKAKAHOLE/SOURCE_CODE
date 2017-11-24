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
    m_playerHeadDir = V2_DOWN;
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
    m_sprMoonSlash = new SpritesObject;
    m_sprMoonSlash->SetBodyImg(g_pImgManager->FindImage("moon-slash"));
    m_sprMoonSlash->SetupForSprites(4, 1);
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
#ifdef _DEBUG
    string szWeaponType = to_string(m_weaponType);
    TextOut(hdc, m_rtBody.left, m_rtBody.top, szWeaponType.c_str(), (int)strlen(szWeaponType.c_str()));
#endif // _DEBUG

}

void Player::PlayerController()
{
    UnitSpeed speed = { 0.0f, 0.0f };
    if (g_pKeyManager->isStayKeyDown(VK_LEFT))
    {
        m_playerHeadDir = V2_LEFT;
        m_currFrameY = DIR_LEFT;
        speed.x -= 5.0f;
        m_playerStatus = PLAYER_RUN;
    }
    else if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
    {
        m_playerHeadDir = V2_RIGHT;
        m_currFrameY = DIR_RIGHT;
        speed.x += 5.0f;
        m_playerStatus = PLAYER_RUN;
    }
    else if (g_pKeyManager->isStayKeyDown(VK_UP))
    {
        m_playerHeadDir = V2_UP;
        m_currFrameY = DIR_UP;
        speed.y -= 5.0f;
        m_playerStatus = PLAYER_RUN;
    }
    else if (g_pKeyManager->isStayKeyDown(VK_DOWN))
    {
        m_playerHeadDir = V2_DOWN;
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
    else if (g_pKeyManager->isOnceKeyDown(VK_TAB))
    {
        m_weaponType = (E_WEAPON_TYPE)(m_weaponType + 1);
        m_weaponType = m_weaponType >= WEAPON_END ? WEAPON_SWORD : m_weaponType;
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
    if (m_playerStatus == PLAYER_ATTACK)
    {
        switch (m_weaponType)
        {
        case WEAPON_SWORD:
        {
            if (m_fMeleeAtkCooltime < g_pTimerManager->GetWorldTime())
            {
                Projectile genBullet;
                genBullet = MakeSword();
                VecBullets.push_back(genBullet);

                m_fMeleeAtkCooltime = g_pTimerManager->GetWorldTime() + 0.4f;
            }
            break;
        }
        case WEAPON_BOW:
        {
            if (m_fRangeAtkCooltime < g_pTimerManager->GetWorldTime())
            {
                Projectile genBullet;
                genBullet = MakeArrow();
                VecBullets.push_back(genBullet);

                m_fRangeAtkCooltime = g_pTimerManager->GetWorldTime() + 0.4f;
            }
            break;
        }
        }
        
    }
}

Projectile Player::MakeSword()
{
    UnitPos swordPos;
    swordPos.x = (double)m_playerHeadDir.x * 20.0f;
    swordPos.y = (double)m_playerHeadDir.y * 20.0f;
    swordPos.x += m_dPos.x;
    swordPos.y += m_dPos.y;

    Projectile sword;
    sword.SetTagName("player");
    sword.SetBodySize({ 50, 50 });
    sword.SetHBoxMargin({ 0, 0, 0, 0 });
    sword.SetBodySpeed({ 0.0f, 0.0f });
    sword.SetGenTime(g_pTimerManager->GetWorldTime());
    sword.SetExistTime(0.3f);
    sword.SetBodyPos(swordPos);
    sword.SetBodyImg(NULL);

    return sword;
}

Projectile Player::MakeArrow()
{
    UnitPos moonSlashPos;
    moonSlashPos.x = (double)m_playerHeadDir.x * 5.0f;
    moonSlashPos.y = (double)m_playerHeadDir.y * 5.0f;
    UnitSpeed arrowSpeed = { moonSlashPos.x, moonSlashPos.y };
    moonSlashPos.x += m_dPos.x;
    moonSlashPos.y += m_dPos.y;

    Projectile moonSlash;
    moonSlash.SetTagName("player");
    moonSlash.SetBodySize({ 100, 100 });
    moonSlash.SetHBoxMargin({ 0, 0, 0, 0 });
    moonSlash.SetBodySpeed(arrowSpeed);
    moonSlash.SetGenTime(g_pTimerManager->GetWorldTime());
    moonSlash.SetExistTime(5.0f);
    moonSlash.SetBodyPos(m_dPos);
    moonSlash.SetBodyImg(m_sprMoonSlash->GetBodyImg());
    moonSlash.SetFrameX(m_currFrameY / 2);

    return moonSlash;
}

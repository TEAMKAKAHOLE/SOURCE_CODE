#include "stdafx.h"
#include "Chief.h"


Chief::Chief()
{
    m_sprBullet = NULL;
    m_isHostile = false;
    m_nPhase = 0;
	m_nSoundPlayCount = 1;
}


Chief::~Chief()
{
    if(m_sprBullet != NULL)
        SAFE_DELETE(m_sprBullet);
}

void Chief::Start()
{
    if (m_isHostile)
        SetHostile();
    else
        m_imgBody = g_pImgManager->FindImage("chief");

    SetupForSprites(1, 1);
    m_nSize = { 64, 64 };
    m_nMarginHBox = { 6, 6, 6, 6 };
    m_dPos = { 256, 340 };

    m_nLife = MAX_HP_BOSS;

    m_sprBullet = new SpritesObject;
    m_sprBullet->SetBodyImg(g_pImgManager->FindImage("agahnim-bullet"));
    m_sprBullet->SetupForSprites(3, 6);
    
    m_fNormalAtkCooldown = g_pTimerManager->GetWorldTime();
}

void Chief::Update()
{
    if (IsAlive() == false)
        return;

    if (m_isHostile)    //  적대적 관계
    {
        PhaseAction();
        PhaseUpdate();
    }

    SpritesObject::Update();

#ifdef _DEBUG
    if (g_pKeyManager->isOnceKeyDown('T'))
        SetHostile();
#endif // _DEBUG
}

void Chief::Render(HDC hdc)
{
    if (IsAlive())
        SpritesObject::Render(hdc);

#ifdef _DEBUG
    string szLife = to_string(m_nLife);
    TextOut(hdc, m_rtBody.left, m_rtBody.top, szLife.c_str(), (int)strlen(szLife.c_str()));
#endif // _DEBUG
}

void Chief::SetHostile()
{
    m_imgBody = g_pImgManager->FindImage("agahnim");
    SetupForSprites(1, 3);
    m_isHostile = true;
}

void Chief::PhaseAction()
{
    switch (m_nPhase)
    {
    case 1:
    {
        NormalAttack(3.0f);
        break;
    }
    case 2:
    {
        NormalAttack(2.0f);
        BarrageAttack(6.5f);
        break;
    }
    case 3:
    {
        NormalAttack(2.0f);
        FireWave(3.7f);
        break;
    }
    case 4:
    {
        NormalAttack(2.0f);
        FireWave(3.7f);
        BarrageAttack(7.5f);
        break;
    }
    case 5:
    {
        NormalAttack(1.5f);
        FireWave(3.5f);
        TimeBomb(6.0f);
        break;
    }
    }
}

void Chief::PhaseUpdate()
{
    if (m_nLife > 90)
    {
        //  phase 1
        m_nPhase = 1;
    }
    else if (m_nLife > 75)
    {
        //  phase 2
        m_nPhase = 2;
    }
    else if (m_nLife > 55)
    {
        //  phase 3
        m_nPhase = 3;
    }
    else if (m_nLife > 5)
    {
        //  phase 4
        m_nPhase = 4;
    }
    else
    {
        //  phase 5
        m_nPhase = 5;
    }
}

void Chief::NormalAttack(float Cooltime)
{
    if (m_fNormalAtkCooldown < g_pTimerManager->GetWorldTime())
        m_fNormalAtkCooldown = g_pTimerManager->GetWorldTime() + Cooltime;
    else
        return;

    double angle = g_pGeoHelper->GetAngleFromCoord(m_dPos, *m_pPlayerPos);
    UnitSpeed bulletSpeed = g_pGeoHelper->GetCoordFromAngle(-angle, 1.0f);

    Projectile genBullet;
    int margin = 20;
    genBullet.SetTagName("enemy");
    genBullet.SetBodySize({ 48, 48 });
    genBullet.SetHBoxMargin({ margin, margin, margin, margin });
    genBullet.SetExistTime(5.0f);
    genBullet.SetBodySpeed(bulletSpeed);
    genBullet.SetBodyPos(m_dPos);
    genBullet.SetBodyImg(m_sprBullet->GetBodyImg());
    genBullet.SetActiveTime(g_pTimerManager->GetWorldTime());
    genBullet.SetGenTime(g_pTimerManager->GetWorldTime());

    m_pVecBullets->push_back(genBullet);
}

void Chief::BarrageAttack(float Cooltime)
{
    if (m_fBarrageCooldown < g_pTimerManager->GetWorldTime())
        m_fBarrageCooldown = g_pTimerManager->GetWorldTime() + Cooltime;
    else
        return;

    int margin = 20;
    for (int i = 0; i < 12; i++)
    {
        UnitSpeed bulletSpeed = g_pGeoHelper->GetCoordFromAngle(i * 30.0f, 1.0f);

        Projectile genBullet;
        genBullet.SetTagName("enemy");
        genBullet.SetBodySize({ 48, 48 });
        genBullet.SetHBoxMargin({ margin, margin, margin, margin });
        genBullet.SetExistTime(5.0f);
        genBullet.SetBodySpeed(bulletSpeed);
        genBullet.SetBodyPos(m_dPos);
        genBullet.SetBodyImg(m_sprBullet->GetBodyImg());
        genBullet.SetActiveTime(g_pTimerManager->GetWorldTime());
        genBullet.SetGenTime(g_pTimerManager->GetWorldTime());

        m_pVecBullets->push_back(genBullet);
    }
}

void Chief::FireWave(float Cooltime)
{
    if (m_fFireWaveCooldown < g_pTimerManager->GetWorldTime())
        m_fFireWaveCooldown = g_pTimerManager->GetWorldTime() + Cooltime;
    else
        return;

    UnitPos bulletPos = *m_pPlayerPos;
    double term = 48.0f;
    int margin = 52;
    bulletPos.x = 0.0f;
    bulletPos.y -= term;
    for (int i = 0; i < 3; i++)
    {
        Projectile genBullet;
        genBullet.SetTagName("enemy");
        genBullet.SetDamage(3);
        genBullet.SetBodySize({ 128, 128 });
        genBullet.SetHBoxMargin({ margin, margin, margin, margin });
        genBullet.SetExistTime(20.0f);
        genBullet.SetBodySpeed({ 2.0f, 0.0f });
        genBullet.SetBodyPos(bulletPos);
        genBullet.SetBodyImg(m_sprBullet->GetBodyImg());
        genBullet.SetActiveTime(g_pTimerManager->GetWorldTime());
        genBullet.SetGenTime(g_pTimerManager->GetWorldTime());

        m_pVecBullets->push_back(genBullet);
        bulletPos.y += term;
    }
}

void Chief::TimeBomb(float Cooltime)
{
    if (m_fTimeBombCooldown < g_pTimerManager->GetWorldTime())
        m_fTimeBombCooldown = g_pTimerManager->GetWorldTime() + Cooltime;
    else
        return;

    UnitPos bulletPos = *m_pPlayerPos;
    int margin = 52;
    bulletPos.x += (double)((rand() % 3) - 1);
    bulletPos.y += (double)((rand() % 3) - 1);

    Projectile genBullet;
    genBullet.SetTagName("enemy");
    genBullet.SetDamage(5);
    genBullet.SetBodySize({ 128, 128 });
    genBullet.SetHBoxMargin({ margin, margin, margin, margin });
    genBullet.SetBodySpeed({ 0.0f, 0.0f });
    genBullet.SetBodyPos(bulletPos);
    genBullet.SetBodyImg(m_sprBullet->GetBodyImg());
    genBullet.SetActiveTime(g_pTimerManager->GetWorldTime() + 2.0f);
    genBullet.SetGenTime(g_pTimerManager->GetWorldTime());
    genBullet.SetExistTime(2.5f);
    genBullet.Deactivate();
    m_pVecBullets->push_back(genBullet);
}
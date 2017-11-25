#include "stdafx.h"
#include "Chief.h"


Chief::Chief()
{
    m_sprBullet = NULL;
    m_isHostile = false;
    m_nPhase = 0;
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
        break;
    case 4:
        break;
    case 5:
        break;
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
    genBullet.SetTagName("enemy");
    genBullet.SetBodySize({ 48, 48 });
    genBullet.SetHBoxMargin({ 12, 12, 12, 12 });
    genBullet.SetExistTime(5.0f);
    genBullet.SetBodySpeed(bulletSpeed);
    genBullet.SetBodyPos(m_dPos);
    genBullet.SetBodyImg(m_sprBullet->GetBodyImg());
    genBullet.SetGenTime(g_pTimerManager->GetWorldTime());

    m_pVecBullets->push_back(genBullet);
}

void Chief::BarrageAttack(float Cooltime)
{
    if (m_fBarrageCooldown < g_pTimerManager->GetWorldTime())
        m_fBarrageCooldown = g_pTimerManager->GetWorldTime() + Cooltime;
    else
        return;

    for (int i = 0; i < 12; i++)
    {
        UnitSpeed bulletSpeed = g_pGeoHelper->GetCoordFromAngle(i * 30.0f, 1.0f);

        Projectile genBullet;
        genBullet.SetTagName("enemy");
        genBullet.SetBodySize({ 48, 48 });
        genBullet.SetHBoxMargin({ 12, 12, 12, 12 });
        genBullet.SetExistTime(5.0f);
        genBullet.SetBodySpeed(bulletSpeed);
        genBullet.SetBodyPos(m_dPos);
        genBullet.SetBodyImg(m_sprBullet->GetBodyImg());
        genBullet.SetGenTime(g_pTimerManager->GetWorldTime());

        m_pVecBullets->push_back(genBullet);
    }
}

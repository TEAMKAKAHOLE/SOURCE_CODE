#include "stdafx.h"
#include "Chief.h"


Chief::Chief()
{
	m_sprBullet = NULL;
    m_isHostile = false;
}


Chief::~Chief()
{
	if(m_sprBullet != NULL)
		SAFE_DELETE(m_sprBullet);
}

void Chief::Start()
{
    m_imgBody = g_pImgManager->FindImage("chief");
    SetupForSprites(1, 1);
    m_nSize = { 64, 64 };
    m_nMarginHBox = { 6, 6, 6, 6 };
    m_dPos = { 256, 340 };

    m_nLife = 20;

    m_sprBullet = new SpritesObject;
    m_sprBullet->SetBodyImg(g_pImgManager->FindImage("agahnim-bullet"));
    m_sprBullet->SetupForSprites(3, 6);
    
    m_fBulletCooltime = g_pTimerManager->GetWorldTime();
}

void Chief::Update()
{
    if (IsAlive() == false)
        return;

    if (m_isHostile)
    {
        //  적대적 관계
    }
    else
    {
        //  우호적 관계
    }

    SpritesObject::Update();
}

void Chief::Render(HDC hdc)
{
    if (IsAlive())
        SpritesObject::Render(hdc);

    string szLife = to_string(m_nLife);
    TextOut(hdc, m_rtBody.left, m_rtBody.top, szLife.c_str(), (int)strlen(szLife.c_str()));
}

void Chief::SetHostile()
{
    m_imgBody = g_pImgManager->FindImage("agahnim");
    SetupForSprites(1, 3);
    m_isHostile = true;
}

void Chief::MakeBullet(vector<Projectile>& VecBullets, UnitPos Pos)
{
    if (IsAlive() == false)
        return;

    if (m_isHostile)
    {
        if (m_fBulletCooltime < g_pTimerManager->GetWorldTime())
        {
            Projectile genBullet;
            genBullet.SetTagName("enemy");
            double angle = g_pGeoHelper->GetAngleFromCoord(m_dPos, Pos);
            UnitSpeed bulletSpeed = g_pGeoHelper->GetCoordFromAngle(-angle, 1.0f);
            genBullet.SetBodySize({ 48, 48 });
            genBullet.SetHBoxMargin({ 12, 12, 12, 12 });
            genBullet.SetExistTime(5.0f);
            genBullet.SetBodySpeed(bulletSpeed);
            genBullet.SetBodyPos(m_dPos);
            genBullet.SetBodyImg(m_sprBullet->GetBodyImg());
            genBullet.SetGenTime(g_pTimerManager->GetWorldTime());
            VecBullets.push_back(genBullet);

            m_fBulletCooltime = g_pTimerManager->GetWorldTime() + 2.0f;
        }
    }
}

#include "stdafx.h"
#include "Projectile.h"


Projectile::Projectile()
{
    m_fGenTime = 0.0f;
    m_fExistTime = 0.1f;
    m_nDamage = 1;
}


Projectile::~Projectile()
{
}

void Projectile::Start()
{
    //  
}

void Projectile::Update()
{
    if (m_fGenTime + m_fExistTime < g_pTimerManager->GetWorldTime())
        SetDead();
    
    SpritesObject::Update();
}

void Projectile::Render(HDC hdc)
{
    SpritesObject::Render(hdc);
}
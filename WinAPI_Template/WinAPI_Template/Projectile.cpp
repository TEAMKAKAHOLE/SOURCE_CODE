#include "stdafx.h"
#include "Projectile.h"


Projectile::Projectile()
{
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
    if (m_fGenTime + 3.0f < g_pTimerManager->GetWorldTime())
        SetDead();
    
    SpritesObject::Update();
}

void Projectile::Render(HDC hdc)
{
    SpritesObject::Render(hdc);
}

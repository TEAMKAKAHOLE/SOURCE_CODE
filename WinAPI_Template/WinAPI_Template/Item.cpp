#include "stdafx.h"
#include "Item.h"


Item::Item()
{
    m_imgBody = g_pImgManager->FindImage("item-potion");
    SetupForSprites(1, 1);

    m_fActiveTime = -1.0f;
    m_fExpireTime = -1.0f;
    m_onField = false;
    m_isActive = false;
}


Item::~Item()
{
}

void Item::Start()
{
    Deactivate();
    
    StartAnimation();
    m_nSize = { 15, 15 };
}

void Item::Update()
{
    if (m_isActive == false &&
        m_fActiveTime > 0.0f)
        if (m_fActiveTime < g_pTimerManager->GetWorldTime())
            Activate();

    if (m_onField &&
        m_fExpireTime > 0.0f)
        if (m_fExpireTime < g_pTimerManager->GetWorldTime())
            SetDead();

    SpritesObject::Update();
}

void Item::Render(HDC hdc)
{
    SpritesObject::Render(hdc);
}
#include "stdafx.h"
#include "Ghost.h"



Ghost::Ghost()
{
    m_egDirection = E_LEFT;

    m_isCheck = false;
}


Ghost::~Ghost()
{
}

void Ghost::Update()
{
    m_rtAwareness = g_pDrawHelper->MakeRect(m_dPos, { 500,500 });

    SpritesObject::Update();
}

void Ghost::Render(HDC hdc)
{
    //g_pDrawHelper->DrawRect(hdc, m_rtAwareness);

    SpritesObject::Render(hdc);
}

void Ghost::GhostMove()
{
    UnitSpeed  speed = { 0.0f,0.0f };

    switch (m_egDirection)
    {
    case E_LEFT:
        speed.x -= 1.5f;
        SetFrameY(3);
        SetMaxFrameX(1);

        break;
    case E_TOP:
        speed.y -= 1.5f;
        SetFrameY(1);
        SetMaxFrameX(1);

        break;
    case E_RIGHT:
        speed.x += 1.5f;
        SetFrameY(2);
        SetMaxFrameX(1);

        break;
    case E_BOTTOM:
        speed.y += 1.5f;
        SetFrameY(0);
        SetMaxFrameX(1);

        break;
    }
    m_dSpeed.x = speed.x;
    m_dSpeed.y = speed.y;
}

int Ghost::GetRandom(int min, int max)
{
    // 0 ~ 5 : 5 - 0 + 1 => 0 ~ 5
    // 5 ~ 9 : 9 - 5 + 1 => 0 ~ 4 + 5 => 5 ~ 9
    return rand() % (max - min + 1) + min;
}

void Ghost::CheckCollision()
{
    UnitPos ProbePos = m_dPos;
    ProbePos.x += m_dSpeed.x;
    ProbePos.y += m_dSpeed.y;
    if (g_pPixelManager->CheckPixelMagenta(m_imgTerrainBuffer, ProbePos))
    {
        m_dSpeed = { 0.0f, 0.0f };
        m_isCheck = true;
    }
}

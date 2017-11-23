#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
	m_eDirection = LEFT;

	m_fGoalsTime = 3.0f;

	m_nLife = 5;

	m_eDirection = (E_DIRECTION)GetRandom(LEFT, MAX);

	m_isCheck = false;
}


Enemy::~Enemy()
{

}

void Enemy::Update()
{
    if (m_nLife <= 0)
        SetDead();

	EnemyMove();

	CheckCollision();

	m_rtAwareness = g_pDrawHelper->MakeRect(m_dPos, { 100,100 });

	SpritesObject::Update();

}

void Enemy::Render(HDC hdc)
{
	g_pDrawHelper->DrawRect(hdc, m_rtAwareness);

	SpritesObject::Render(hdc);

}

void Enemy::EnemyMove()
{
	UnitSpeed  speed = { 0.0f,0.0f };

	switch (m_eDirection)
	{
	case LEFT:
		speed.x -= 1.5f;
		SetFrameY(2);
		SetMaxFrameX(3);

		if (g_pTimerManager->GetWorldTime()> m_fGoalsTime)
		{
			m_fGoalsTime = g_pTimerManager->GetWorldTime() + 3;
			m_eDirection = RIGHT;
		}
		break;
	case TOP:
		speed.y -= 1.5f;
		SetFrameY(3);
		SetMaxFrameX(3);

		if (g_pTimerManager->GetWorldTime() > m_fGoalsTime)
		{
			m_fGoalsTime = g_pTimerManager->GetWorldTime() + 3;
			m_eDirection = BOTTOM;
		}		
		break;
	case RIGHT:
		speed.x += 1.5f;
		SetFrameY(1);
		SetMaxFrameX(3);

		if (g_pTimerManager->GetWorldTime() > m_fGoalsTime)
		{
			m_fGoalsTime = g_pTimerManager->GetWorldTime() + 3;
			m_eDirection = LEFT;
		}			
		break;
	case BOTTOM:
		speed.y += 1.5f;
		SetFrameY(0);
		SetMaxFrameX(2);

		if (g_pTimerManager->GetWorldTime() > m_fGoalsTime)
		{
			m_fGoalsTime = g_pTimerManager->GetWorldTime() + 3;
			m_eDirection = TOP;
		}			
		break;
	}
	m_dSpeed.x = speed.x;
	m_dSpeed.y = speed.y;
}

int Enemy::GetRandom(int min, int max)
{

	// 0 ~ 5 : 5 - 0 + 1 => 0 ~ 5
	// 5 ~ 9 : 9 - 5 + 1 => 0 ~ 4 + 5 => 5 ~ 9
	return rand() % (max - min + 1) + min;

}

void Enemy::CheckCollision()
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

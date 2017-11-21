#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::Update()
{
	SpritesObject::Update();

	EnemyMove();
}

void Enemy::Render(HDC hdc)
{
	SpritesObject::Render(hdc);
}

void Enemy::EnemyMove()
{
	
	UnitSpeed  speed = { 0.0f,0.0f };
	static int count = 0;

	if (count > 50)
	{
		count = 0;

		m_eDirection = (E_DIRECTION)GetRandom(LEFT, BOTTOM);

	}
	else
	{
		count++;
	}


	switch (m_eDirection)
	{
	case LEFT:
		m_dPos.x -= 5;
		SetFrameY(2);
		SetMaxFrameX(3);
		break;
	case TOP:
		m_dPos.y -= 5;
		SetFrameY(3);
		SetMaxFrameX(3);
		break;
	case RIGHT:
		m_dPos.x += 5;
		SetFrameY(1);
		SetMaxFrameX(3);
		break;
	case BOTTOM:
		m_dPos.y += 5;
		SetFrameY(0);
		SetMaxFrameX(2);
		break;

	}
	
}

int Enemy::GetRandom(int min, int max)
{
	
	// 0 ~ 5 : 5 - 0 + 1 => 0 ~ 5
	// 5 ~ 9 : 9 - 5 + 1 => 0 ~ 4 + 5 => 5 ~ 9
	return rand() % (max - min + 1) + min;
	
}

#pragma once
#include "SpritesObject.h"

enum E_DIRECTION{LEFT,TOP,RIGHT,BOTTOM};


class Enemy : public SpritesObject
{
private:
	int m_currStatus;
	E_DIRECTION m_eDirection;

public:
	Enemy();
	~Enemy();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void EnemyMove();
	int GetRandom(int min, int max);
	
};


#pragma once
#include "SpritesObject.h"


class EnemyFollow:public SpritesObject
{
private:



public:
	EnemyFollow();
	~EnemyFollow();

	virtual void Update();
	void Start();
	virtual void Render(HDC hdc);
	void EnemyController();
};


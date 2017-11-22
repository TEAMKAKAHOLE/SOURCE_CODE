#include "stdafx.h"
#include "EnemyFollow.h"


EnemyFollow::EnemyFollow()
{
}


EnemyFollow::~EnemyFollow()
{
}

void EnemyFollow::Update()
{
	isAnimate = false;

	if (isAnimate == false)
		SetFrameX(0);
	SpritesObject::Update();

}

void EnemyFollow::Start()
{
}

void EnemyFollow::Render(HDC hdc)
{
	SpritesObject::Render(hdc);
}

void EnemyFollow::EnemyController()
{


}

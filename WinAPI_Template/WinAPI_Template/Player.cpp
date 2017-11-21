#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
}

void Player::Update()
{
	isAnimate = false;
	PlayerController();
	if (isAnimate == false)
		SetFrameX(0);

	//부모의 업데이트도 실행함.
	SpritesObject::Update();
}

void Player::Render(HDC hdc)
{
	SpritesObject::Render(hdc);
}

void Player::PlayerController()
{
	UnitSpeed speed = { 0, 0 };

	if (g_pKeyManager->isStayKeyDown(VK_LEFT))
	{
		speed.x -= 5.0f;
		SetFrameY(4);
		isAnimate = true;
	}
	else if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
	{
		speed.x += 5.0f;
		SetFrameY(2);
		isAnimate = true;
	}
	else if (g_pKeyManager->isStayKeyDown(VK_UP))
	{
		speed.y -= 5.0f;
		SetFrameY(6);
		isAnimate = true;
	}
	else if (g_pKeyManager->isStayKeyDown(VK_DOWN))
	{
		speed.y += 5.0f;
		SetFrameY(0);
		isAnimate = true;
	}

	m_dSpeed = speed;
}
